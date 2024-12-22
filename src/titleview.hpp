#pragma once

#include <glm/glm.hpp>

#include "view.hpp"
#include "viewstack.hpp"

class TitleView: public View
{
public:
	TitleView(ViewStack &stack, const Context &context);
	~TitleView() override = default;

	bool update(float dt) override;
	bool handleEvent(const Event &event) override;
	void render(RenderTarget &target) override;

private:
	ViewStack &mViewStack;
	Texture &mTexture;
	glm::vec2 mTextureSize;
};
