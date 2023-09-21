#pragma once

#include <vector>
#include <memory>

#include "enemy.hpp"
#include "rect.hpp"
#include "shotmanager.hpp"

class RenderTarget;

class EnemyManager
{
public:
	EnemyManager(
		const FloatRect &screenBounds,
		const Texture &texture, const FloatRect &initialFrame, unsigned frameCount,
		const Sprite &player);

	void spawnEnemy(unsigned path);
	void spawnWave(unsigned type);

	void update(float dt);
	void draw(RenderTarget &target);

	bool isActive() const;
	void setActive(bool active);

private:
	void updateWaveSpawns(float dt);

private:
	const Texture &mTexture;
	FloatRect mInitialFrame;
	unsigned mFrameCount;

	const Sprite &mPlayer;
public:
	std::vector<std::unique_ptr<Enemy>> mEnemies;

private:
	std::vector<std::size_t> mWaveSpawns;
public:
	ShotManager mShots;
private:

	float mNextWaveTimer;
	float mShipSpawnTimer;

	bool mActive;
};
