#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "rect.hpp"
#include "sprite.hpp"
#include "shotmanager.hpp"
#include "texture.hpp"

class SoundPlayer;
class Window;

class PlayerManager
{
public:
	PlayerManager(
		const FloatRect &screenBounds,
		const Texture &texture, const FloatRect &initialFrame, unsigned frameCount,
		SoundPlayer &soundPlayer);

	void update(float dt, Window &window);
	void draw(RenderTarget &target);

	const Sprite& getPlayer() const;

	int getLives() const;
	void loseLife();

	bool isDestroyed() const;
	void setDestroyed(bool destroyed);

	long getScore() const;
	void addScore(long points);

	void reset();

private:
	void fireShot();
	void handleKeyboardInput(Window &window);
	void handleGamepadInput();
	void limitMovements();

private:
	const Texture &mTexture;
	std::vector<FloatRect> mPlayerFrames;

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

private:
	SoundPlayer &mSoundPlayer;
};
