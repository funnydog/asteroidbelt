#pragma once

#include <span>

#include <glm/glm.hpp>

#include "rect.hpp"
#include "sprite.hpp"

class Enemy: public Sprite
{
public:
	Enemy(glm::vec2 frameSize, glm::vec2 location);

	void addPath(std::span<const glm::vec2> path);
	bool hasReachedWaypoint() const;
	bool isActive() const;

	void setDestroyed(bool destroyed);

	void update(float dt) override;

private:
	std::span<const glm::vec2> mPath;
	unsigned mNext;
	float mSpeed;
	bool mDestroyed;
};
