#include "shotmanager.hpp"

#include "rendertarget.hpp"

ShotManager::ShotManager(
	const FloatRect &screenBounds,
	float shotSpeed, float collisionRadius,
	const Texture &texture, const FloatRect &initialFrame, unsigned frameCount)
	: mTexture(texture)
	, mFrameSize(initialFrame.size)
	, mShotSpeed(shotSpeed)
	, mCollisionRadius(collisionRadius)
	, mScreenBounds(screenBounds)
{
	auto frame = initialFrame / texture.getSize();
	while (frameCount-->0)
	{
		mUVFrames.push_back(frame);
		frame.pos.x += frame.size.x;
	}
}

void
ShotManager::fireShot(glm::vec2 location, glm::vec2 velocity, bool)
{
	auto shot = std::make_unique<Sprite>(mFrameSize, location, velocity);
	shot->velocity *= mShotSpeed;
	shot->frames = mUVFrames;
	shot->collisionRadius = mCollisionRadius;
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
		target.draw(*shotPtr, mTexture);
	}
}
