#include "gameoverview.hpp"

#include <glm/glm.hpp>

#include "color.hpp"
#include "font.hpp"
#include "rendertarget.hpp"
#include "resourceholder.hpp"
#include "window.hpp"

namespace
{
const char *Message = "G A M E   O V E R !";
}

GameOverView::GameOverView(ViewStack &stack, const Context &context)
	: mStack(stack)
	, mFont(context.fonts->get(FontID::Pericles14))
	, mPosition()
	, mTimer(10.f)
{
	mPosition = (glm::vec2(context.window->getSize()) - mFont.getSize(Message)) * 0.5f;
}

bool
GameOverView::update(float dt)
{
	mTimer -= dt;
	if (mTimer < 0.f)
	{
		mStack.clearStack();
		mStack.pushView(ViewID::Title);
	}
	return false;
}

bool
GameOverView::handleEvent(const Event &event)
{
	if (const auto ep(std::get_if<KeyPressed>(&event)); ep)
	{
		mStack.clearStack();
		mStack.pushView(ViewID::Title);
		return true;
	}
	return false;
}

void
GameOverView::render(RenderTarget &target)
{
	mFont.draw(target, mPosition, Message, Color::White);
	target.draw();
}
