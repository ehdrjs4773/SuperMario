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

	IMAGEMANAGER->addFrameImage("hammer_bullet", ".\\bmps\\hammer\\hammer_bullet.bmp\\ ", 0, 0, 128, 16, 8, 1,
		true, true, RGB(255, 0, 255));

	_bullet = new hammerBullet;
	_bullet->init("hammer_bullet", 10, 600);

	return S_OK;
}
void hammer::release()
{
	mario::release();


}
void hammer::update() 
{
	mario::update();
	//attack();
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
			marioStateChange(STATE_ATTACK);

			if (_dir == DIR_RIGHT)
			{
				_bullet->setBullet(IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2,
					IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 2, 0.0f, 5.0f, false);
			}
			if (_dir == DIR_LEFT)
			{
				_bullet->setBullet(IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2,
					IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 2, PI , 5.0f, false);
			}
		}
	}
}

