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

	attack();
	frameUpdate();
	_bullet->update();

}
void hammer::render() 
{
	mario::render();
	_bullet->render();

}

void hammer::move()
{

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
				this->_bullet->setBullet(IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2,
					IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 2, 0.0f, 5.0f, false);
			}
			if (_dir == DIR_LEFT)
			{
				this->_bullet->setBullet(IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2,
					IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 2, PI , 5.0f, false);
			}
		}
	}
}

void hammer::falling()
{

}

void hammer::draw()
{

}

void hammer::frameUpdate()
{
	_frameTime++;
	switch (_state)
	{
	case STATE_IDLE:
		break;

	case STATE_MOVE:
		if (_frameTime % 3 == 0)
		{
			_frameX++;

			if (_frameX > IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getMaxFrameX())
				_frameX = 0;

			_frameTime = 0;
		}
		break;

	case STATE_ATTACK:
		if (_frameTime % 2 == 0)
		{
			_frameX++;

			if (_frameX > IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getMaxFrameX())
				_frameX = IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getMaxFrameX();

			_frameTime = 0;
		}
		break;

	case STATE_DIE:
		if (_frameTime % 20 == 0)
		{
			_frameX++;

			if (_frameX > IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getMaxFrameX())
				_frameX = 0;

			_frameTime = 0;
		}
		break;
	}
}

