#pragma once

#include <glm/glm.hpp>

#include "rect.hpp"
#include "sprite.hpp"
#include "shotmanager.hpp"
#include "texture.hpp"

class Window;

class PlayerManager
{
public:
	PlayerManager(const FloatRect &screenBounds,
		      const Texture &texture, const FloatRect &initialFrame, unsigned frameCount);

	void update(float dt, Window &window);
	void draw(RenderTarget &target);

	const Sprite& getPlayer() const;

	bool isDestroyed() const;
	void setDestroyed(bool destroyed);

	void addScore(long points);

private:
	void fireShot();
	void handleKeyboardInput(Window &window);
	void handleGamepadInput();
	void limitMovements();

private:
	Sprite mPlayerSprite;
	float  mPlayerSpeed;
	FloatRect mPlayerAreaLimit;

	long mPlayerScore;
	int mLivesRemaining;
	bool mDestroyed;

	glm::vec2 mGunOffset;
	float mShotTimer;
	float mMinShotTimer;
	float mPlayerRadius;

public:
	ShotManager mShotManager;
};
