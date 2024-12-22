#include "gameview.hpp"

#include "rendertarget.hpp"
#include "resources.hpp"
#include "resourceholder.hpp"
#include "texture.hpp"
#include "window.hpp"

namespace
{
const float PlayerDeathDelay = 5.f;

const glm::vec2 ScoreLocation(20.f, 10.f);
const glm::vec2 LivesLocation(20.f, 25.f);
}

GameView::GameView(ViewStack &stack, const Context &context)
	: mStack(stack)
	, mWindow(*context.window)
	, mFont(context.fonts->get(FontID::Pericles14))
	, mDeathTimer(0.f)
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
			 {{0.f, 150.f}, {50.f, 50.f}}, 3,
			 *context.player)
	, mEnemyManager({{0.f, 0.f}, context.window->getSize()},
			context.textures->get(TextureID::SpriteSheet),
			{{0, 200}, {50, 50}}, 6,
			mPlayerManager.getPlayer(),
			*context.player)
	, mExplosionManager({{0.f, 450.f}, {2.f, 2.f}},
			    context.textures->get(TextureID::SpriteSheet),
			    {{0.f, 100.f}, {50.f, 50.f}}, 3,
			    *context.player)
	, mCollisionManager(
		mAsteroidManager,
		mPlayerManager,
		mEnemyManager,
		mExplosionManager)
{
}

void
GameView::resetGame()
{
	mEnemyManager.mEnemies.clear();
	mEnemyManager.mShots.mShots.clear();
	mEnemyManager.setActive(true);
	mPlayerManager.reset();
}

bool
GameView::update(float dt)
{
	mStarField.update(dt);
	mAsteroidManager.update(dt);
	mPlayerManager.update(dt, mWindow);
	mEnemyManager.update(dt);
	mExplosionManager.update(dt);
	mCollisionManager.checkCollisions();

	if (mPlayerManager.getLives() < 0)
	{
		// GAME OVER, do not respawn
	}
	else if (mDeathTimer > 0.f)
	{
		mDeathTimer -= dt;
		if (mDeathTimer <= 0.f)
		{
			mDeathTimer = 0.f;
			resetGame();
		}
	}
	else if (mPlayerManager.isDestroyed())
	{
		mDeathTimer = PlayerDeathDelay;
		mEnemyManager.setActive(false);
		mPlayerManager.loseLife();
		if (mPlayerManager.getLives() < 0)
		{
			mStack.pushView(ViewID::GameOver);
		}
	}
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
	mEnemyManager.draw(target);
	mExplosionManager.draw(target);

	target.draw("Score: " + std::to_string(mPlayerManager.getScore()),
	            ScoreLocation, mFont, Color::White);

	if (mPlayerManager.getLives() >= 0)
	{
		target.draw("Ships Remaining: "
		            + std::to_string(mPlayerManager.getLives()),
		            LivesLocation, mFont, Color::White);
	}

	target.draw();
}
