#pragma once
#include "mario.h"
#include "hammerBullet.h"


class hammer : public mario
{
private:
	hammerBullet* _bullet;


	//윗방향키를 누르고있는지 여부
	bool _isUpKey;
public:
	hammer();
	~hammer();

	virtual HRESULT init(const string imageName, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void attack();

	virtual void keyControl();

	virtual void collisionEnemyWithHammer();

	//해머마리오 불렛 접근자
	hammerBullet* getHammerBullet() { return _bullet; }

};

