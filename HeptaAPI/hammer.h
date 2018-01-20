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

	virtual void move();
	virtual void attack();
	virtual void falling();
	virtual void draw();

	virtual void frameUpdate();

	inline POINT getPos() { return PointMake(_x, _y); }
};

