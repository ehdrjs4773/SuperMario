#include "stdafx.h"
#include "fireBullet.h"


//==============================================
// ## MF ## �߻���� �������� �����Ǵ� �̜X ##
//==============================================

MF::MF() {}
MF::~MF() {}

HRESULT MF::init(int missileMax, float range)
{
	_bulletMax = missileMax;
	_range = range;

	return S_OK;
}

void MF::release()
{

}

void MF::update()
{
	move();
}

void MF::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->imageName->frameRender(CAMERAMANAGER->getMemDC(),
			_viBullet->rc.left,
			_viBullet->rc.top,
			_viBullet->imageName->getFrameX(), 0);

		_viBullet->count++;

		if (_viBullet->count % 5 == 0)
		{
			_viBullet->imageName->setFrameX(_viBullet->imageName->getFrameX() + 1);

			if (_viBullet->imageName->getFrameX() >= _viBullet->imageName->getMaxFrameX())
			{
				_viBullet->imageName->setFrameX(0);
			}

			_viBullet->count = 0;
		}
	}
}


void MF::fire(float x, float y)
{
	//�ִ밹������ �� �����ɷ��� �ϸ�
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));
	bullet.imageName = new image;
	bullet.imageName->init(".\\bmps\\fire\\fire_bullet.bmp", 0, 0, 45, 15, 4, 1, false, true, RGB(255, 0, 255));
	bullet.speed = 0.1f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.angle = 0.0f;
	bullet.jumpPower = 0.0f;
	bullet.rc = RectMakeCenter(bullet.x, bullet.y,
		bullet.imageName->getFrameWidth(),
		bullet.imageName->getFrameHeight());

	_vBullet.push_back(bullet);
}


void MF::move()
{
	float gravity = 0.1f;

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
	
		char temp[32];
		sprintf(temp, "�޹��");
		int probeY = _viBullet->y +_viBullet->imageName->getFrameHeight() / 2 - 1;

				COLORREF color = GetPixel(IMAGEMANAGER->findImage(temp)->getMemDC(), _viBullet->imageName->getFrameWidth(), probeY);
				if (GetRValue(color) == 0 &&
					GetGValue(color) == 255 &&
					GetBValue(color) == 255) //���� pixel �浹��
				{
					_viBullet->jumpPower = 1.0f;
				}

				_viBullet->x += cosf(_viBullet->angle)*_viBullet->speed * 12;
				_viBullet->y -= _viBullet->jumpPower;
				_viBullet->jumpPower -= gravity;
				_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
					_viBullet->imageName->getFrameWidth(),
					_viBullet->imageName->getFrameHeight());

	

		if (_range < getDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			SAFE_RELEASE(_viBullet->imageName);
			SAFE_DELETE(_viBullet->imageName);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void MF::removeMissile(int arrNum)
{
	_vBullet[arrNum].imageName->release();
	_vBullet.erase(_vBullet.begin() + arrNum);
}
