#include "particle.hpp"

Particle::Particle(
		glm::vec2 location, glm::vec2 velocity, glm::vec2 acceleration,
		float maxSpeed, float duration,
		Color initialColor, Color finalColor,
		const Texture &texture, const FloatRect &textureRect)
	: Sprite(texture, textureRect, location, velocity)
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
		mVelocity += mAcceleration;
		if (glm::length(mVelocity) > mMaxSpeed)
		{
			mVelocity = glm::normalize(mVelocity);
			mVelocity *= mMaxSpeed;
		}
		mTintColor = mix(mInitialColor, mFinalColor, getDurationProgress());
		mRemainingDuration -= dt;
		Sprite::update(dt);
	}
}

void
Particle::draw(RenderTarget &target)
{
	if (isActive())
	{
		Sprite::draw(target);
	}
}
