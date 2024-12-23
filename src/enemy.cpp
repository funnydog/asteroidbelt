#include "enemy.hpp"

namespace
{
static const float EnemyRadius = 15.f;
}

Enemy::Enemy(glm::vec2 frameSize, glm::vec2 location)
	: Sprite(frameSize, location, glm::vec2(0.f))
	, mWaypoints()
	, mCurrentWaypoint(location)
	, mSpeed(120.f)
	, mDestroyed(false)
	, mPreviousLocation(location)
{
	collisionRadius = EnemyRadius;
}

void
Enemy::addWaypoint(glm::vec2 waypoint)
{
	mWaypoints.push_back(waypoint);
}

bool
Enemy::hasReachedWaypoint() const
{
	auto distance = glm::distance(location, mCurrentWaypoint);
	return distance < frameSize.x * 0.5f;
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

	mPreviousLocation = location;
	glm::vec2 dir = mCurrentWaypoint - mPreviousLocation;
	if (dir.x != 0.f || dir.y != 0.f)
	{
		dir = glm::normalize(dir);
	}
	velocity = dir * mSpeed;
	Sprite::update(dt);
	rotation = glm::atan(location.y - mPreviousLocation.y,
	                     location.x - mPreviousLocation.x);

	if (hasReachedWaypoint() && !mWaypoints.empty())
	{
		mCurrentWaypoint = mWaypoints.front();
		mWaypoints.pop_front();
	}
}
