#include "sprite.hpp"

#include "texture.hpp"
#include "rendertarget.hpp"

Sprite::Sprite(glm::vec2 frameSize, glm::vec2 location, glm::vec2 velocity)
	: location(location)
	, velocity(velocity)
	, rotation(0.f)
	, frameSize(frameSize)
	, tintColor(Color::White)
	, frameIndex(0)
	, frameElapsed(0.f)
	, frameDelay(0.1f)
	, collisionRadius(0.f)
	, boundingPadding(0.f)
{
}

glm::vec2
Sprite::getCenter() const
{
	return frameSize * 0.5f + location;
}

const FloatRect&
Sprite::getSource() const
{
	return frames[frameIndex];
}

FloatRect
Sprite::getDestination() const
{
	return { location, frameSize };
}

FloatRect
Sprite::getBoundingBox() const
{
	return {
		location + boundingPadding,
		frameSize - boundingPadding * 2.f
	};
}

bool
Sprite::isBoxColliding(const FloatRect &other) const
{
	return getBoundingBox().intersect(other);
}

bool
Sprite::isCircleColliding(glm::vec2 otherCenter, float otherRadius) const
{
	auto radiusSum = collisionRadius+otherRadius;
	otherCenter -= getCenter();
	return otherCenter.x * otherCenter.x + otherCenter.y * otherCenter.y <
		radiusSum * radiusSum;
}

void
Sprite::update(float dt)
{
	frameElapsed += dt;
	if (frameElapsed >= frameDelay)
	{
		frameElapsed -= frameDelay;
		frameIndex++;
		if (frameIndex >= frames.size())
		{
			frameIndex = 0;
		}
	}
	location += velocity * dt;
}
