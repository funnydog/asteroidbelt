#include "enemy.hpp"

namespace
{
static const float EnemyRadius = 15.f;
}

Enemy::Enemy(glm::vec2 location, const Texture &texture, const FloatRect &initialFrame, unsigned frameCount)
	: mSprite(texture, initialFrame, location, glm::vec2(0.f))
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
		mSprite.addFrame(rect);
	}
	mSprite.setCollisionRadius(EnemyRadius);
}

void
Enemy::addWaypoint(glm::vec2 waypoint)
{
	mWaypoints.push_back(waypoint);
}

bool
Enemy::hasReachedWaypoint() const
{
	auto distance = glm::distance(mSprite.getLocation(), mCurrentWaypoint);
	return distance < mSprite.getDestination().size.x * 0.5f;
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

glm::vec2
Enemy::getLocation() const
{
	return mSprite.getLocation();
}

void
Enemy::update(float dt)
{
	if (!isActive())
	{
		return;
	}

	mPreviousLocation = mSprite.getLocation();
	glm::vec2 dir = mCurrentWaypoint - mPreviousLocation;
	if (dir.x != 0.f || dir.y != 0.f)
	{
		dir = glm::normalize(dir);
	}
	mSprite.setVelocity(dir * mSpeed);
	mSprite.update(dt);
	auto loc = mSprite.getLocation();
	mSprite.setRotation(glm::atan(loc.y - mPreviousLocation.y,
				      loc.x - mPreviousLocation.x));

	if (hasReachedWaypoint() && !mWaypoints.empty())
	{
		mCurrentWaypoint = mWaypoints.front();
		mWaypoints.pop_front();
	}
}

void
Enemy::draw(RenderTarget &target)
{
	if (isActive())
	{
		mSprite.draw(target);
	}
}
