#include "enemy.hpp"

namespace
{
static const float EnemyRadius = 15.f;
}

Enemy::Enemy(glm::vec2 location, const Texture &texture, const FloatRect &initialFrame, unsigned frameCount)
	: Sprite(texture, initialFrame, location, glm::vec2(0.f))
	, mWaypoints()
	, mCurrentWaypoint(location)
	, mSpeed(120.f)
	, mDestroyed(false)
	, mPreviousLocation(location)
{
	FloatRect rect = initialFrame;
	for (unsigned i = 1; i < frameCount; i++)
	{
		rect.pos.x += rect.size.x;
		addFrame(rect);
	}
	setCollisionRadius(EnemyRadius);
}

void
Enemy::addWaypoint(glm::vec2 waypoint)
{
	mWaypoints.push_back(waypoint);
}

bool
Enemy::hasReachedWaypoint() const
{
	auto distance = glm::distance(mLocation, mCurrentWaypoint);
	return distance < mFrameSize.x * 0.5f;
}

bool
Enemy::isActive() const
{
	if (mDestroyed)
	{
		return false;
	}
	if (!mWaypoints.empty())
	{
		return true;
	}
	if (hasReachedWaypoint())
	{
		return false;
	}
	return true;
}

void
Enemy::setDestroyed(bool destroyed)
{
	mDestroyed = destroyed;
}

void
Enemy::update(float dt)
{
	if (!isActive())
	{
		return;
	}

	mPreviousLocation = mLocation;
	glm::vec2 dir = mCurrentWaypoint - mPreviousLocation;
	if (dir.x != 0.f || dir.y != 0.f)
	{
		dir = glm::normalize(dir);
	}
	mVelocity = dir * mSpeed;
	Sprite::update(dt);
	setRotation(glm::atan(mLocation.y - mPreviousLocation.y,
			      mLocation.x - mPreviousLocation.x));

	if (hasReachedWaypoint() && !mWaypoints.empty())
	{
		mCurrentWaypoint = mWaypoints.front();
		mWaypoints.pop_front();
	}
}
