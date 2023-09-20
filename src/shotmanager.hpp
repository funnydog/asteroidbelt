#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

#include "rect.hpp"
#include "sprite.hpp"

class RenderTarget;

class ShotManager
{
public:
	ShotManager(
		const FloatRect &screenBounds,
		float shotSpeed, float collisionRadius,
		const Texture &texture, const FloatRect &initialFrame, unsigned frameCount);

	void fireShot(glm::vec2 location, glm::vec2 velocity, bool playerFired);

	void update(float dt);
	void draw(RenderTarget &target);

private:
	const Texture &mTexture;
	FloatRect mInitialFrame;
	unsigned mFrameCount;
	float mShotSpeed;
	float mCollisionRadius;
	FloatRect mScreenBounds;
	std::vector<std::unique_ptr<Sprite>> mShots;
};
