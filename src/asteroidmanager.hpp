#pragma once

#include <vector>
#include <memory>

#include "rect.hpp"
#include "sprite.hpp"
#include "texture.hpp"


class RenderTarget;

class AsteroidManager
{
public:
	AsteroidManager(int width, int height, unsigned asteroidCount,
			const Texture &texture, const FloatRect &initialFrame,
			unsigned frameCount);

	void addAsteroid();
	void clear();

	void update(float dt);
	void draw(RenderTarget &target);

private:
	glm::vec2 randomLocation() const;
	glm::vec2 randomVelocity() const;
	bool isOnScreen(const Sprite &asteroid) const;

	static void bounceAsteroids(Sprite &a1, Sprite &a2);

private:
	int mScreenWidth;
	int mScreenHeight;
	FloatRect mScreenBounds;

	const Texture &mTexture;
	glm::vec2 mFrameSize;
	unsigned mFrameCount;
	std::vector<FloatRect> mFrames;
public:
	std::vector<std::unique_ptr<Sprite>> mAsteroids;
};
