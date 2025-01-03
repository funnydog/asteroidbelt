#include <iostream>

#include <GLFW/glfw3.h>

#include "playermanager.hpp"

#include "audiodevice.hpp"
#include "rendertarget.hpp"
#include "window.hpp"

namespace
{
const glm::vec2 PlayerStartLocation(390.f, 550.f);
const int PlayerStartLives = 3;
}

PlayerManager::PlayerManager(
	const FloatRect &screenBounds,
	const Texture &texture, const FloatRect &initialFrame, unsigned frameCount,
	AudioDevice &audioDevice)
	: mTexture(texture)
	, mPlayerSprite(initialFrame.size, PlayerStartLocation, {})
	, mPlayerSpeed(160.f)
	, mPlayerAreaLimit{
			{0.f, screenBounds.size.y * 0.5f},
			{screenBounds.size.x, screenBounds.size.y * 0.5f}
		}
	, mPlayerScore(0)
	, mLivesRemaining(PlayerStartLives)
	, mDestroyed(false)
	, mGunOffset(45.f * 0.5f, 10.f)
	, mShotTimer(0.f)
	, mMinShotTimer(0.2f)
	, mPlayerRadius(15.f)
	, mShotManager(screenBounds, 250.f, 2, texture, {{0.f, 300.f}, {5.f, 5.f}}, 4)
	, mAudioDevice(audioDevice)
{
	// normalize the frame coordinates
	FloatRect frame = initialFrame / texture.getSize();
	while (frameCount-->0)
	{
		mPlayerFrames.push_back(frame);
		frame.pos.x += frame.size.x;
	}
	mPlayerSprite.frames = mPlayerFrames;
	mPlayerSprite.collisionRadius = mPlayerRadius;
}

const Sprite&
PlayerManager::getPlayer() const
{
	return mPlayerSprite;
}

int
PlayerManager::getLives() const
{
	return mLivesRemaining;
}

void
PlayerManager::loseLife()
{
	mLivesRemaining--;
}

bool
PlayerManager::isDestroyed() const
{
	return mDestroyed;
}

void
PlayerManager::setDestroyed(bool destroyed)
{
	mDestroyed = destroyed;
}

long
PlayerManager::getScore() const
{
	return mPlayerScore;
}

void
PlayerManager::addScore(long points)
{
	mPlayerScore += points;
}

void
PlayerManager::reset()
{
	mPlayerSprite.location = PlayerStartLocation;
	mDestroyed = false;
	mShotManager.mShots.clear();
}

void
PlayerManager::fireShot()
{
	if (mShotTimer >= mMinShotTimer)
	{
		mShotTimer = 0.f;
		mShotManager.fireShot(
			mPlayerSprite.location + mGunOffset,
			glm::vec2(0.f, -1.f),
			true);
		mAudioDevice.play(SoundID::Shot1);
	}
}

void
PlayerManager::handleKeyboardInput(Window &window)
{
	int h = window.isKeyPressed(GLFW_KEY_RIGHT) - window.isKeyPressed(GLFW_KEY_LEFT);
	int v = window.isKeyPressed(GLFW_KEY_DOWN) - window.isKeyPressed(GLFW_KEY_UP);
	auto vel = mPlayerSprite.velocity + glm::vec2(h, v);
	if (vel.x != 0.f && vel.y != 0.f)
	{
		vel = glm::normalize(vel);
	}
	mPlayerSprite.velocity = vel;

	if (window.isKeyPressed(GLFW_KEY_SPACE))
	{
		fireShot();
	}
}

void
PlayerManager::handleGamepadInput()
{
	// TODO
}

void
PlayerManager::limitMovements()
{
	auto dst = mPlayerSprite.getDestination();
	glm::vec2 loc;
	loc.x = std::clamp(
		dst.pos.x,
		mPlayerAreaLimit.pos.x,
		mPlayerAreaLimit.pos.x + mPlayerAreaLimit.size.x - dst.size.x);
	loc.y = std::clamp(
		dst.pos.y,
		mPlayerAreaLimit.pos.y,
		mPlayerAreaLimit.pos.y + mPlayerAreaLimit.size.y - dst.size.y);

	mPlayerSprite.location = loc;
}

void
PlayerManager::update(float dt, Window &window)
{
	mShotManager.update(dt);
	if (!mDestroyed)
	{
		mPlayerSprite.velocity = glm::vec2(0.f);

		mShotTimer += dt;
		handleKeyboardInput(window);
		handleGamepadInput();

		mPlayerSprite.velocity *= mPlayerSpeed;
		mPlayerSprite.update(dt);
		limitMovements();
	}
}

void
PlayerManager::draw(RenderTarget &target)
{
	mShotManager.draw(target);
 	if (!mDestroyed)
	{
		target.draw(mPlayerSprite, mTexture);
	}
}
