#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <memory>

#include "particle.hpp"

class ExplosionManager
{
public:
	ExplosionManager(
		const FloatRect &pointRectangle,
		const Texture &texture, const FloatRect &textureRect, unsigned frameCount);

	static glm::vec2 getRandomDirection(float scale);

	void addExplosion(glm::vec2 location, glm::vec2 momentum);

	void update(float dt);
	void draw(RenderTarget &target);

private:
	const Texture &mTexture;
	std::vector<FloatRect> mFrames;
	FloatRect mPointRectangle;
	std::vector<std::unique_ptr<Particle>> mParticles;
};
