#include "stdafx.h"
#include "bullet.h"

bullet::bullet()
{
}


bullet::~bullet()
{
}

HRESULT bullet::init(const string imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}
void bullet::release()
{

}
void bullet::update() 
{
	move();
	frameUpdate();
}
void bullet::render() 
{
	draw();
}

void bullet::draw()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->imageName->frameRender(getMemDC(), _viBullet->x, _viBullet->y,
			_viBullet->currentFrameX, _viBullet->currentFrameY);
	}
}
void bullet::setBullet(float x, float y, float angle, float speed , bool isUpAttack)
{
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(bullet));
	bullet.imageName = IMAGEMANAGER->findImage(_imageName);
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = angle;
	bullet.speed = speed;
	bullet.gravity = 0.5f;
	bullet.isUpAttack = isUpAttack;
	bullet.currentFrameX = bullet.currentFrameY = bullet.count = 0;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y, bullet.imageName->getFrameWidth(), bullet.imageName->getFrameHeight());

	_vBullet.push_back(bullet);
}
void bullet::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (_viBullet->isUpAttack == true)
		{
			_viBullet->x = cosf(_viBullet->angle) * _viBullet->speed;
			_viBullet->y = -sinf(_viBullet->angle) * _viBullet->speed - _viBullet->gravity;
		}
		if (_viBullet->isUpAttack == false)
		{
			_viBullet->x = cosf(_viBullet->angle) * _viBullet->speed;
			_viBullet->y = -sinf(_viBullet->angle) * _viBullet->speed;
		}

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->imageName->getFrameWidth(),
			_viBullet->imageName->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}
void bullet::frameUpdate()
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