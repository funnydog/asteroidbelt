#pragma once

class AsteroidManager;
class PlayerManager;
class EnemyManager;
class ExplosionManager;

class CollisionManager
{
public:
	CollisionManager(
		AsteroidManager &asteroidManager,
		PlayerManager &playerManager,
		EnemyManager &enemyManager,
		ExplosionManager &explosionManager);

	void checkCollisions();

private:
	void checkShotToEnemy();
	void checkShotToAsteroid();
	void checkShotToPlayer();
	void checkEnemyToPlayer();
	void checkAsteroidToPlayer();

private:
	AsteroidManager &mAsteroidManager;
	PlayerManager &mPlayerManager;
	EnemyManager &mEnemyManager;
	ExplosionManager &mExplosionManager;
};
