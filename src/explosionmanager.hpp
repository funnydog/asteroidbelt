#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <memory>

#include "particle.hpp"

class RenderTarget;
class SoundPlayer;
class Texture;

class ExplosionManager
{
public:
	ExplosionManager(
		const FloatRect &pointRectangle,
		const Texture &texture, const FloatRect &textureRect, unsigned frameCount,
		SoundPlayer &soundPlayer);

	static glm::vec2 getRandomDirection(float scale);

	void addExplosion(glm::vec2 location, glm::vec2 momentum);

	void update(float dt);
	void draw(RenderTarget &target);

private:
	const Texture &mTexture;
	glm::vec2 mFrameSize;
	std::vector<FloatRect> mExpUV;
	glm::vec2 mPointSize;
	FloatRect mPointUV;
	std::vector<std::unique_ptr<Particle>> mParticles;
	SoundPlayer &mSoundPlayer;
};
