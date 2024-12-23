#pragma once

#include <deque>

#include <glm/glm.hpp>

#include "rect.hpp"
#include "sprite.hpp"

class Texture;
class RenderTarget;

class Enemy: public Sprite
{
public:
	Enemy(glm::vec2 frameSize, glm::vec2 location);

	void addWaypoint(glm::vec2 waypoint);
	bool hasReachedWaypoint() const;
	bool isActive() const;

	void setDestroyed(bool destroyed);

	void update(float dt) override;

private:
	std::deque<glm::vec2> mWaypoints;
	glm::vec2 mCurrentWaypoint;
	float mSpeed;
	bool mDestroyed;
	glm::vec2 mPreviousLocation;
};
