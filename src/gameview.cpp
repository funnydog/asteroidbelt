#include "gameview.hpp"

#include "rendertarget.hpp"
#include "resources.hpp"
#include "resourceholder.hpp"
#include "texture.hpp"
#include "window.hpp"

GameView::GameView(ViewStack &stack, const Context &context)
	: mStack(stack)
	, mWindow(*context.window)
	, mAsteroidManager(context.window->getSize().x,
			   context.window->getSize().y,
			   10,
			   context.textures->get(TextureID::SpriteSheet),
			   {{0.f, 0.f}, {50.f, 50.f}},
			   20)
	, mStarField(context.window->getSize().x,
		     context.window->getSize().y,
		     200,
		     {0.f, 30.f},
		     context.textures->get(TextureID::SpriteSheet),
		     {{0, 450.f}, {2.f, 2.f}})
	, mPlayerManager({{0.f, 0.f}, context.window->getSize()},
			 context.textures->get(TextureID::SpriteSheet),
			 {{0.f, 150.f}, {50.f, 50.f}},
			 3)
{
}

bool
GameView::update(float dt)
{
	mAsteroidManager.update(dt);
	mPlayerManager.update(dt, mWindow);
	mStarField.update(dt);
	return true;
}

bool
GameView::handleEvent(const Event &)
{
	return false;
}

void
GameView::render(RenderTarget &target)
{
	target.clear(Color::Black);
	mStarField.draw(target);
	mAsteroidManager.draw(target);
	mPlayerManager.draw(target);
	target.draw();
}
