#pragma once

#include <glm/glm.hpp>

#include "color.hpp"
#include "rect.hpp"
#include "texture.hpp"

class Sprite
{
public:
	Sprite(const Texture *texture, FloatRect initialFrame, glm::vec2 location, glm::vec2 velocity);

	glm::vec2 getLocation() const;
	void setLocation(glm::vec2 location);

	glm::vec2 getVelocity() const;
	void setVelocity(glm::vec2 velocity);

	Color getTintColor() const;
	void setTintColor(Color color);

	float getRotation() const;
	void setRotation(float rotation);

	unsigned getFrameIndex() const;
	void setFrameIndex(unsigned frame);

	float getFrameDelay() const;
	void setFrameDelay(float delay);

	glm::vec2 getCenter() const;
	const FloatRect& getSource() const;
	const FloatRect getDestination() const;


private:
	// drawable
	const Texture *mTexture;
	FloatRect mUV;
	glm::vec2 mSize;
	Color mTintColor;

	// animation
	glm::vec2 mStart;
	unsigned mFrameColumns;
	unsigned mFrameIndex;
	unsigned mFrameCount;
	float mFrameElapsed;
	float mFrameDelay;
	bool  mRepeat;
	bool  mForward;

	// position
	glm::vec2 mLocation;
	glm::vec2 mVelocity;
	float mRotation;

	// collision
	float mCollisionRadius;
	glm::vec2 mBoundingPadding;
};
