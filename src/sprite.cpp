#include "sprite.hpp"

Sprite::Sprite(
	const Texture *texture,
	FloatRect initialFrame,
	glm::vec2 location,
	glm::vec2 velocity)
	: mTexture(texture)
	, mUV(initialFrame)
	, mSize(initialFrame.size)
	, mTintColor(Color::White)
	, mStart(initialFrame.pos)
	, mFrameColumns(1)
	, mFrameIndex(0)
	, mFrameCount(1)
	, mFrameElapsed(0.f)
	, mFrameDelay(0.f)
	, mRepeat(true)
	, mForward(true)
	, mLocation(location)
	, mVelocity(velocity)
	, mRotation(0.f)
	, mCollisionRadius(0.f)
	, mBoundingPadding()
{
}

glm::vec2
Sprite::getLocation() const
{
	return mLocation;
}

void
Sprite::setLocation(glm::vec2 location)
{
	mLocation = location;
}

glm::vec2
Sprite::getVelocity() const
{
	return mVelocity;
}

void
Sprite::setVelocity(glm::vec2 velocity)
{
	mVelocity = velocity;
}

Color
Sprite::getTintColor() const
{
	return mTintColor;
}

void
Sprite::setTintColor(Color color)
{
	mTintColor = color;
}

float
Sprite::getRotation() const
{
	return mRotation;
}

void
Sprite::setRotation(float rotation)
{
	mRotation = rotation;
}

unsigned
Sprite::getFrameIndex() const
{
	return mFrameIndex;
}

void
Sprite::setFrameIndex(unsigned index)
{
	mFrameIndex = index % mFrameCount;
}

float
Sprite::getFrameDelay() const
{
	return mFrameDelay;
}

void
Sprite::setFrameDelay(float delay)
{
	mFrameDelay = delay;
}

glm::vec2
Sprite::getCenter() const
{
	return mSize * 0.5f + mLocation;
}

const FloatRect&
Sprite::getSource() const
{
	return mUV;
}

const FloatRect
Sprite::getDestination() const
{
	return { mLocation, mSize };
}
