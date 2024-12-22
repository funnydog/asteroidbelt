#pragma once

#include <glm/glm.hpp>

#include "view.hpp"
#include "viewstack.hpp"

class GameOverView: public View
{
public:
	GameOverView(ViewStack &stack, const Context &context);
	~GameOverView() override = default;

	bool update(float dt) override;
	bool handleEvent(const Event &event) override;
	void render(RenderTarget &target) override;

private:
	ViewStack &mStack;
	Font &mFont;
	glm::vec2 mPosition;
	float mTimer;
};
