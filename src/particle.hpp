#pragma once

#include <glm/glm.hpp>

#include "color.hpp"
#include "rect.hpp"
#include "sprite.hpp"

class Particle: public Sprite
{
public:
	Particle(glm::vec2 frameSize,
	         glm::vec2 location, glm::vec2 velocity, glm::vec2 acceleration,
	         float maxSpeed, float duration,
	         Color initialColor, Color finalColor);
	float getElapsedDuration() const;
	float getDurationProgress() const;
	bool isActive() const;

	void update(float dt) override;

private:
	glm::vec2 mAcceleration;
	float mMaxSpeed;
	float mInitialDuration;
	float mRemainingDuration;
	Color mInitialColor;
	Color mFinalColor;
};
