#include "starfield.hpp"

#include "utility.hpp"
#include "rendertarget.hpp"
#include "sprite.hpp"

namespace
{
static const std::vector<Color> Colors = {
	Color::White,
	Color::Yellow,
	Color(0xF5, 0xDE, 0xB3),
	Color(0xF5, 0xF5, 0xF5),
	Color(0x70, 0x80, 0x90),
};
}

StarField::StarField(int width, int height, std::size_t count, glm::vec2 velocity,
		     const Texture &texture, const FloatRect &textureRect)
	: mTexture(texture)
	, mUVFrame(textureRect / texture.getSize())
	, mScreenWidth(width)
	, mScreenHeight(height)
{
	while (count-->0)
	{
		glm::vec2 pos(Utility::randomInt(width), Utility::randomInt(height));
		auto star = std::make_unique<Sprite>(textureRect.size, pos, velocity);
		auto color = Colors[Utility::randomInt(Colors.size())];
		color *= 0.3f + Utility::randomFloat(0.5f);
		star->tintColor = color;
		auto *uv = &mUVFrame;
		star->frames = std::span(uv, uv+1);
		mStars.push_back(std::move(star));
	}
}

void
StarField::update(float dt)
{
	for (auto &starPtr: mStars)
	{
		starPtr->update(dt);
		auto pos = starPtr->location;
		if (pos.y > mScreenHeight)
		{
			pos.x = Utility::randomInt(mScreenWidth);
			pos.y = 0;
			starPtr->location = pos;
		}
	}
}

void
StarField::draw(RenderTarget &target)
{
	for (auto &starPtr: mStars)
	{
		target.draw(*starPtr, mTexture);
	}
}
