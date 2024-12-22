#pragma once

#include "view.hpp"
#include "viewstack.hpp"

#include "asteroidmanager.hpp"
#include "playermanager.hpp"
#include "enemymanager.hpp"
#include "explosionmanager.hpp"
#include "starfield.hpp"
#include "collisionmanager.hpp"
#include "font.hpp"

class GameView: public View
{
public:
	GameView(ViewStack &stack, const Context &context);
	~GameView() override = default;
	bool update(float dt) override;
	bool handleEvent(const Event &event) override;
	void render(RenderTarget &target) override;

private:
	void resetGame();

private:
	ViewStack &mStack;
	Window &mWindow;
	Font &mFont;

	float mDeathTimer;

	AsteroidManager mAsteroidManager;
	StarField mStarField;
	PlayerManager mPlayerManager;
	EnemyManager mEnemyManager;
	ExplosionManager mExplosionManager;
	CollisionManager mCollisionManager;
};
