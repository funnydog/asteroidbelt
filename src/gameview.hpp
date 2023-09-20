#pragma once

#include "view.hpp"
#include "viewstack.hpp"

#include "asteroidmanager.hpp"
#include "playermanager.hpp"
#include "enemymanager.hpp"
#include "starfield.hpp"

class GameView: public View
{
public:
	GameView(ViewStack &stack, const Context &context);
	virtual ~GameView() override = default;
	virtual bool update(float dt) override;
	virtual bool handleEvent(const Event &event) override;
	virtual void render(RenderTarget &target) override;
private:
	ViewStack &mStack;
	Window &mWindow;
	AsteroidManager mAsteroidManager;
	StarField mStarField;
	PlayerManager mPlayerManager;
	EnemyManager mEnemyManager;
};
