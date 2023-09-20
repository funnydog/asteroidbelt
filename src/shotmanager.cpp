#include "shotmanager.hpp"

ShotManager::ShotManager(
	const FloatRect &screenBounds,
	float shotSpeed, float collisionRadius,
	const Texture &texture, const FloatRect &initialFrame, unsigned frameCount)
	: mTexture(texture)
	, mInitialFrame(initialFrame)
	, mFrameCount(frameCount)
	, mShotSpeed(shotSpeed)
	, mCollisionRadius(collisionRadius)
	, mScreenBounds(screenBounds)
{
}

void
ShotManager::fireShot(glm::vec2 location, glm::vec2 velocity, bool)
{
	auto shot = std::make_unique<Sprite>(mTexture, mInitialFrame, location, velocity);
	shot->setVelocity(shot->getVelocity() * mShotSpeed);

	FloatRect frame = mInitialFrame;
	for (unsigned x = 1; x < mFrameCount; x++)
	{
		frame.pos.x += frame.size.x;
		shot->addFrame(frame);
	}
	shot->setCollisionRadius(mCollisionRadius);
	mShots.push_back(std::move(shot));
}

void
ShotManager::update(float dt)
{
	for (auto it = mShots.begin(); it != mShots.end();)
	{
		(*it)->update(dt);
		if (!mScreenBounds.intersect((*it)->getDestination()))
		{
			it = mShots.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void
ShotManager::draw(RenderTarget &target)
{
	for (auto &shotPtr: mShots)
	{
		shotPtr->draw(target);
	}
}
