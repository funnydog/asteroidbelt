#pragma once

#include <span>

#include <glm/glm.hpp>

#include "color.hpp"
#include "rect.hpp"

struct Sprite
{
	// position
	glm::vec2 location;
	glm::vec2 velocity;
	float rotation;

	// drawable
	std::span<const FloatRect> frames;
	glm::vec2 frameSize;
	Color tintColor;

	// animation
	unsigned frameIndex;
	float frameElapsed;
	float frameDelay;

	// collision
	float collisionRadius;
	glm::vec2 boundingPadding;

	Sprite(glm::vec2 frameSize, glm::vec2 location, glm::vec2 velocity);

	glm::vec2 getCenter() const;
	const FloatRect& getSource() const;
	FloatRect getDestination() const;

	FloatRect getBoundingBox() const;
	bool isBoxColliding(const FloatRect &other) const;
	bool isCircleColliding(glm::vec2 otherCenter, float otherRadius) const;

	virtual void update(float dt);
};
