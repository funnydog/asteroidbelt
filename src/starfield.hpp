#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "rect.hpp"
#include "sprite.hpp"

class RenderTarget;
class Texture;

class StarField
{
public:
	StarField(int width, int height, std::size_t count, glm::vec2 velocity,
		  const Texture &texture, const FloatRect &textureRect);

	void update(float dt);
	void draw(RenderTarget &target);

private:
	std::vector<std::unique_ptr<Sprite>> mStars;
	int mScreenWidth;
	int mScreenHeight;
};
