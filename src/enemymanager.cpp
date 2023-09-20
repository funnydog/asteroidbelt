#include <glm/glm.hpp>

#include "enemymanager.hpp"
#include "utility.hpp"

namespace
{

// constants
const int MinShipsPerWave = 5;
const int MaxShipsPerWave = 8;
const float NextWaveMinTimer = 8.f;
const float ShipSpawnWaitTime = 0.5f;
const float ShipShotChance = 0.2f;
const glm::vec2 GunOffset(25.f, 25.f);

const std::vector<std::vector<glm::vec2>> Waypoints = {
	{
		{850, 300},
		{-100, 300},
	},
	{
		{-50, 225},
		{850, 225},
	},
	{
		{-100, 50},
		{150, 50},
		{200, 75},
		{200, 125},
		{150, 150},
		{150, 175},
		{200, 200},
		{600, 200},
		{850, 600},
	},
	{
		{600, -100},
		{600, 250},
		{580, 275},
		{500, 250},
		{500, 200},
		{450, 175},
		{400, 150},
		{-100, 150},
	},
};

}

EnemyManager::EnemyManager(
	const FloatRect &screenBounds,
	const Texture &texture, const FloatRect &initialFrame, unsigned frameCount,
	const Sprite &player)
	: mTexture(texture)
	, mInitialFrame(initialFrame)
	, mFrameCount(frameCount)
	, mPlayer(player)
	, mEnemies()
	, mWaveSpawns(Waypoints.size(), 0)
	, mShots(screenBounds, 150.f, 2.f, texture, {{0.f, 300.f}, {5.f, 5.f}}, 4)
	, mNextWaveTimer(0.f)
	, mShipSpawnTimer(0.f)
	, mActive(true)
{
}

void
EnemyManager::spawnEnemy(unsigned path)
{
	auto enemyPtr = std::make_unique<Enemy>(
		Waypoints[path][0],
		mTexture,
		mInitialFrame,
		mFrameCount);
	for (unsigned x = 1; x < Waypoints[path].size(); x++)
	{
		enemyPtr->addWaypoint(Waypoints[path][x]);
	}
	mEnemies.push_back(std::move(enemyPtr));
}

void
EnemyManager::spawnWave(unsigned type)
{
	mWaveSpawns[type] +=
		MinShipsPerWave + Utility::randomInt(MaxShipsPerWave - MinShipsPerWave + 1);
}

void
EnemyManager::updateWaveSpawns(float dt)
{
	mShipSpawnTimer += dt;
	if (mShipSpawnTimer >= ShipSpawnWaitTime)
	{
		mShipSpawnTimer -= ShipSpawnWaitTime;
		for (std::size_t i = 0; i < mWaveSpawns.size(); i++)
		{
			if (mWaveSpawns[i] > 0)
			{
				mWaveSpawns[i]--;
				spawnEnemy(i);
			}
		}
	}

	mNextWaveTimer += dt;
	if (mNextWaveTimer >= NextWaveMinTimer)
	{
		mNextWaveTimer -= NextWaveMinTimer;
		spawnWave(Utility::randomInt(Waypoints.size()));
	}
}

void
EnemyManager::update(float dt)
{
	mShots.update(dt);
	for (auto it = mEnemies.begin(); it != mEnemies.end();)
	{
		(*it)->update(dt);
		if (!(*it)->isActive())
		{
			it = mEnemies.erase(it);
			continue;
		}

		if (Utility::randomFloat(100.f) <= ShipShotChance)
		{
			glm::vec2 loc = (*it)->getLocation() + GunOffset;
			glm::vec2 dir = mPlayer.getCenter() - loc;
			dir = glm::normalize(dir);
			mShots.fireShot(loc, dir, false);
		}
		++it;
	}

	if (mActive)
	{
		updateWaveSpawns(dt);
	}
}

void
EnemyManager::draw(RenderTarget &target)
{
	mShots.draw(target);
	for (auto &enemyPtr: mEnemies)
	{
		enemyPtr->draw(target);
	}
}
