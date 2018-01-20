#include "stdafx.h"
#include "hammer.h"



hammer::hammer()
{
}


hammer::~hammer()
{
}

HRESULT hammer::init(const string imageName, float x, float y)
{
	mario::init(imageName, x, y);

	IMAGEMANAGER->addFrameImage("hammer_bullet", ".\\bmps\\hammer\\hammer_bullet.bmp ", 0, 0, 128, 16, 8, 1,
		true, true, RGB(255, 0, 255));

	_bullet = new hammerBullet;
	_bullet->init("hammer_bullet", 10, 150);

	//윗방향키를 누르고있는지 여부
	_isUpKey = false;

	return S_OK;
}
void hammer::release()
{
	mario::release();


}
void hammer::update() 
{
	mario::update();
	keyControl();
	attack();
	_bullet->update();

}
void hammer::render() 
{
	mario::render();
	_bullet->render();

}


void hammer::attack()
{
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_state != STATE_DIE &&
			_state != STATE_ATTACK)
		{
			//marioStateChange(STATE_ATTACK);		

			if (!_isUpKey)
			{
				if (_dir == DIR_RIGHT)
				{
					_bullet->setBullet(getPos().x + 3, getPos().y - 5, 0.0f, 5.0f, false);
				}
				if (_dir == DIR_LEFT)
				{
					_bullet->setBullet(getPos().x - 15, getPos().y - 5, PI, 5.0f, false);
				}
			}
			if (_isUpKey)
			{
				if (_dir == DIR_RIGHT)
				{
					_bullet->setBullet(getPos().x + 3, getPos().y - 7, PI / 2 - 0.2f, 5.0f, true);
				}
				if (_dir == DIR_LEFT)
				{
					_bullet->setBullet(getPos().x - 15, getPos().y - 7, PI / 2 + 0.2f, 5.0f, true);
				}
			}
		}
	}
}

void hammer::keyControl()
{
	//윗방향키를 누르고있는지 여부
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_isUpKey = true;
	}

	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_isUpKey = false;
	}
}

