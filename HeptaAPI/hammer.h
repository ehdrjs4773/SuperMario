#pragma once
#include "mario.h"
#include "bullet.h"

class hammer : public mario
{
private:
	hammerBullet* _bullet;
	
public:
	hammer();
	~hammer();

	virtual HRESULT init(const string imageName, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void attack();

};

