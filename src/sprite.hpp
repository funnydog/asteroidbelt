#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "color.hpp"
#include "rect.hpp"

class Texture;

struct Sprite
{
	// position
	glm::vec2 location;
	glm::vec2 velocity;
	float rotation;

	// drawable
	glm::vec2 textureSize;
	std::vector<FloatRect> frames;
	glm::vec2 frameSize;
	Color tintColor;

	// animation
	unsigned frameIndex;
	float frameElapsed;
	float frameDelay;

	// collision
	float collisionRadius;
	glm::vec2 boundingPadding;

	Sprite(const Texture &texture, FloatRect initialFrame, glm::vec2 location, glm::vec2 velocity);

	glm::vec2 getCenter() const;
	const FloatRect& getSource() const;
	FloatRect getDestination() const;

	FloatRect getBoundingBox() const;
	bool isBoxColliding(const FloatRect &other) const;
	bool isCircleColliding(glm::vec2 otherCenter, float otherRadius);

	void addFrame(const FloatRect &rect);

	virtual void update(float dt);
};
