#pragma once
#include "mario.h"
#include "fireBullet.h"

class fire : public mario
{
private:
	MF* _missile;


public:

	 HRESULT init(const string imageName, float x, float y);
	 void update();
	 void render();

	 void attack();
	 void draw();

	 void missileFire();
	 void missileMove();
	 void missileDraw();

	 void collisionEnemyWithFireBullet();

	fire();
	~fire();
};

