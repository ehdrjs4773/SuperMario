#include "stdafx.h"
#include "hammerBullet.h"

hammerBullet::hammerBullet()
{
}


hammerBullet::~hammerBullet()
{
}

HRESULT hammerBullet::init(const string imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}
void hammerBullet::release()
{

}
void hammerBullet::update()
{
	move();
	frameUpdate();
}
void hammerBullet::render()
{
	draw();
}

void hammerBullet::draw()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_isDebug)
		{
			Rectangle(CAMERAMANAGER->getMemDC(), _viBullet->rc.left, _viBullet->rc.top, _viBullet->rc.right, _viBullet->rc.bottom);
		}

		_viBullet->imageName->frameRender(CAMERAMANAGER->getMemDC(), _viBullet->x, _viBullet->y,
			_viBullet->currentFrameX, _viBullet->currentFrameY);


	}
}
void hammerBullet::setBullet(float x, float y, float angle, float speed , bool isUpAttack)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(bullet));
	bullet.imageName = IMAGEMANAGER->findImage(_imageName);
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.speed = speed;
	bullet.gravity = 0.0f;
	bullet.isUpAttack = (bool)isUpAttack;
	bullet.currentFrameX = bullet.currentFrameY = bullet.count = 0;
	bullet.rc = RectMake(bullet.x, bullet.y, bullet.imageName->getFrameWidth(), bullet.imageName->getFrameHeight());

	_vBullet.push_back(bullet);
}
void hammerBullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (_viBullet->isUpAttack)
		{
			_viBullet->gravity += 0.3f;
			_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
			_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed + _viBullet->gravity;
		}
		else
		{
			_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
			_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		}

		_viBullet->rc = RectMake(_viBullet->x, _viBullet->y,
			_viBullet->imageName->getFrameWidth(),
			_viBullet->imageName->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}
void hammerBullet::frameUpdate()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->count++;
		if (_viBullet->count > 3)
		{
			if (_viBullet->currentFrameX >= _viBullet->imageName->getMaxFrameX()) _viBullet->currentFrameX = 0;
			_viBullet->currentFrameX++;
			_viBullet->count = 0;
		}
	}
}

void hammerBullet::eraseBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}