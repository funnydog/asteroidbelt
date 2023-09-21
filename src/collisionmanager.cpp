#include "collisionmanager.hpp"

#include "asteroidmanager.hpp"
#include "playermanager.hpp"
#include "enemymanager.hpp"
#include "explosionmanager.hpp"

namespace
{
const glm::vec2 OffScreen(-500.f, -500.f);
const glm::vec2 ShotToAsteroidImpact(0, -20.f);
const int EnemyPointValue = 100;
}

CollisionManager::CollisionManager(
	AsteroidManager &asteroidManager,
	PlayerManager &playerManager,
	EnemyManager &enemyManager,
	ExplosionManager &explosionManager)
	: mAsteroidManager(asteroidManager)
	, mPlayerManager(playerManager)
	, mEnemyManager(enemyManager)
	, mExplosionManager(explosionManager)
{
}

void
CollisionManager::checkCollisions()
{
	checkShotToEnemy();
	checkShotToAsteroid();
	if (!mPlayerManager.isDestroyed())
	{
		checkShotToPlayer();
		checkEnemyToPlayer();
		checkAsteroidToPlayer();
	}
}

void
CollisionManager::checkShotToEnemy()
{
	for (auto &shotPtr: mPlayerManager.mShotManager.mShots)
	{
		for (auto &enemyPtr: mEnemyManager.mEnemies)
		{
			auto enemyCenter = enemyPtr->getCenter();
			if (shotPtr->isCircleColliding(
				    enemyCenter, enemyPtr->getCollisionRadius()))
			{
				shotPtr->setLocation(OffScreen);
				enemyPtr->setDestroyed(true);
				mPlayerManager.addScore(EnemyPointValue);
				mExplosionManager.addExplosion(
					enemyCenter, enemyPtr->getVelocity() * 0.2f);
			}
		}
	}
}

void
CollisionManager::checkShotToAsteroid()
{
	for (auto &shotPtr: mPlayerManager.mShotManager.mShots)
	{
		for (auto &asteroidPtr: mAsteroidManager.mAsteroids)
		{
			if (shotPtr->isCircleColliding(
				    asteroidPtr->getCenter(),
				    asteroidPtr->getCollisionRadius()))
			{
				shotPtr->setLocation(OffScreen);
				asteroidPtr->setVelocity(
					asteroidPtr->getVelocity() + ShotToAsteroidImpact);
			}
		}
	}
}

void
CollisionManager::checkShotToPlayer()
{
	auto playerCenter = mPlayerManager.getPlayer().getCenter();
	auto playerRadius = mPlayerManager.getPlayer().getCollisionRadius();
	for (auto &shotPtr: mEnemyManager.mShots.mShots)
	{
		if (shotPtr->isCircleColliding(playerCenter, playerRadius))
		{
			shotPtr->setLocation(OffScreen);
			mPlayerManager.setDestroyed(true);
			mExplosionManager.addExplosion(playerCenter, glm::vec2(0.f));
		}
	}
}

void
CollisionManager::checkEnemyToPlayer()
{
	auto playerCenter = mPlayerManager.getPlayer().getCenter();
	auto playerRadius = mPlayerManager.getPlayer().getCollisionRadius();
	for (auto &enemyPtr: mEnemyManager.mEnemies)
	{
		if (enemyPtr->isCircleColliding(playerCenter, playerRadius))
		{
			enemyPtr->setDestroyed(true);
			mExplosionManager.addExplosion(
				enemyPtr->getCenter(),
				enemyPtr->getVelocity() * 0.1f);

			mPlayerManager.setDestroyed(true);
			mExplosionManager.addExplosion(playerCenter, glm::vec2(0.f));
		}
	}
}

void
CollisionManager::checkAsteroidToPlayer()
{
	auto playerCenter = mPlayerManager.getPlayer().getCenter();
	auto playerRadius = mPlayerManager.getPlayer().getCollisionRadius();
	for (auto &asteroidPtr: mAsteroidManager.mAsteroids)
	{
		if (asteroidPtr->isCircleColliding(playerCenter, playerRadius))
		{
			mExplosionManager.addExplosion(
				asteroidPtr->getCenter(),
				asteroidPtr->getVelocity() * 0.1f);

			asteroidPtr->setLocation(OffScreen);

			mPlayerManager.setDestroyed(true);
			mExplosionManager.addExplosion(playerCenter, glm::vec2(0.f));
		}
	}
}
