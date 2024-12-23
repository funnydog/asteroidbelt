#include <iostream>

#include "asteroidmanager.hpp"

#include "rendertarget.hpp"
#include "sprite.hpp"
#include "utility.hpp"

namespace
{
const glm::ivec2 ScreenPadding(10, 10);
const float MinSpeed = 60.f;
const float MaxSpeed = 120.f;
}

AsteroidManager::AsteroidManager(
	int width, int height, unsigned asteroidCount,
	const Texture &texture, const FloatRect &initialFrame,
	unsigned frameCount)
	: mScreenWidth(width)
	, mScreenHeight(height)
	, mScreenBounds{
			-ScreenPadding,
			glm::ivec2(width,height) + ScreenPadding * 2
		}
	, mTexture(texture)
	, mInitialFrame(initialFrame)
	, mFrameCount(frameCount)
{
	while (asteroidCount-->0)
	{
		addAsteroid();
	}
}

void
AsteroidManager::addAsteroid()
{
	auto asteroid = std::make_unique<Sprite>(
		mTexture,
		mInitialFrame,
		glm::vec2(-500, -500),
		glm::vec2(0.f));

	FloatRect frame = mInitialFrame;
	for (unsigned i = 1; i < mFrameCount; i++)
	{
		frame.pos.x += frame.size.x;
		asteroid->addFrame(frame);
	}

	asteroid->frameDelay = 1.1f / mFrameCount;
	asteroid->rotation = Utility::randomFloat(3.141592654f);
	asteroid->collisionRadius = 15.f;

	mAsteroids.push_back(std::move(asteroid));
}

void
AsteroidManager::clear()
{
	mAsteroids.clear();
}

glm::vec2
AsteroidManager::randomLocation() const
{
	glm::vec2 loc;
	int tryCount = 0;
	bool is_ok;
	do
	{
		is_ok = true;
		switch (Utility::randomInt(3))
		{
		case 0:
			loc.x = -mInitialFrame.size.x;
			loc.y = Utility::randomInt(mScreenHeight);
			break;

		case 1:
			loc.x = mScreenWidth;
			loc.y = Utility::randomInt(mScreenHeight);
			break;

		case 2:
			loc.x = Utility::randomInt(mScreenWidth);
			loc.y = -mInitialFrame.size.y;
			break;
		}
		for (auto &aptr: mAsteroids)
		{
			if (aptr->isBoxColliding({ loc, mInitialFrame.size }))
			{
				is_ok = false;
				break;
			}
		}
	} while(!is_ok && ++tryCount < 5);

	if (!is_ok)
	{
		loc.x = -500;
		loc.y = -500;
	}

	return loc;
}

glm::vec2
AsteroidManager::randomVelocity() const
{
	glm::vec2 vel(Utility::randomFloat(100.f) - 50.f,
		      Utility::randomFloat(100.f) - 50.f);
	vel = glm::normalize(vel);
	vel *= MinSpeed + Utility::randomFloat(MaxSpeed - MinSpeed);
	return vel;
}

bool
AsteroidManager::isOnScreen(const Sprite &asteroid) const
{
	return asteroid.getDestination().intersect(mScreenBounds);
}

void
AsteroidManager::update(float dt)
{
	for (auto &aptr: mAsteroids)
	{
		aptr->update(dt);
		if (!isOnScreen(*aptr))
		{
			aptr->location = randomLocation();
			aptr->velocity = randomVelocity();
		}
	}

	for (std::size_t x = 0; x < mAsteroids.size(); x++)
	{
		for (std::size_t y = x + 1; y < mAsteroids.size(); y++)
		{
			if (mAsteroids[x]->isCircleColliding(
				    mAsteroids[y]->getCenter(),
				    mAsteroids[y]->collisionRadius))
			{
				bounceAsteroids(*mAsteroids[x], *mAsteroids[y]);
			}
		}
	}
}

void
AsteroidManager::draw(RenderTarget &target)
{
	for (auto &aptr: mAsteroids)
	{
		target.draw(*aptr, mTexture);
	}
}

void
AsteroidManager::bounceAsteroids(Sprite &a1, Sprite &a2)
{
	glm::vec2 cOfMass = (a1.velocity + a2.velocity) * 0.5f;

	auto normal1 = glm::normalize(a2.getCenter() - a1.getCenter());
	auto normal2 = glm::normalize(a1.getCenter() - a2.getCenter());

	a1.velocity = glm::reflect(a1.velocity - cOfMass, normal1) + cOfMass;
	a2.velocity = glm::reflect(a2.velocity - cOfMass, normal2) + cOfMass;
}
