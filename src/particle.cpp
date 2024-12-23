#include "particle.hpp"

Particle::Particle(glm::vec2 frameSize,
                   glm::vec2 location, glm::vec2 velocity, glm::vec2 acceleration,
                   float maxSpeed, float duration,
                   Color initialColor, Color finalColor)
	: Sprite(frameSize, location, velocity)
	, mAcceleration(acceleration)
	, mMaxSpeed(maxSpeed)
	, mInitialDuration(duration)
	, mRemainingDuration(duration)
	, mInitialColor(initialColor)
	, mFinalColor(finalColor)
{
}

float
Particle::getElapsedDuration() const
{
	return mInitialDuration - mRemainingDuration;
}

float
Particle::getDurationProgress() const
{
	return getElapsedDuration() / mInitialDuration;
}

bool
Particle::isActive() const
{
	return mRemainingDuration > 0.f;
}

void
Particle::update(float dt)
{
	if (isActive())
	{
		velocity += mAcceleration;
		if (glm::length(velocity) > mMaxSpeed)
		{
			velocity = glm::normalize(velocity);
			velocity *= mMaxSpeed;
		}
		tintColor = mix(mInitialColor, mFinalColor, getDurationProgress());
		mRemainingDuration -= dt;
		Sprite::update(dt);
	}
}
