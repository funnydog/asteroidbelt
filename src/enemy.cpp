#include "enemy.hpp"

namespace
{
static const float EnemyRadius = 15.f;
}

Enemy::Enemy(glm::vec2 frameSize, glm::vec2 location)
	: Sprite(frameSize, location, glm::vec2(0.f))
	, mPath()
	, mNext(0)
	, mSpeed(120.f)
	, mDestroyed(false)
{
	collisionRadius = EnemyRadius;
}

void
Enemy::addPath(std::span<const glm::vec2> path)
{
	mPath = path;
	mNext = 0;
}

bool
Enemy::hasReachedWaypoint() const
{
	if (mNext >= mPath.size())
	{
		return true;
	}
	auto distance = glm::distance(location, mPath[mNext]);
	return distance < frameSize.x * 0.5f;
}

bool
Enemy::isActive() const
{
	if (mDestroyed)
	{
		return false;
	}
	if (mNext < mPath.size())
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

	glm::vec2 dir = mPath[mNext] - location;
	if (dir.x != 0.f || dir.y != 0.f)
	{
		dir = glm::normalize(dir);
	}
	velocity = dir * mSpeed;

	auto previousLocation = location;
	Sprite::update(dt);
	rotation = glm::atan(location.y - previousLocation.y,
	                     location.x - previousLocation.x);

	if (hasReachedWaypoint() && mNext < mPath.size())
	{
		mNext++;
	}
}
