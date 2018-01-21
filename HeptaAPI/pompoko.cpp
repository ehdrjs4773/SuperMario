#include "stdafx.h"
#include "pompoko.h"

pompoko::pompoko()
{
}


pompoko::~pompoko()
{
}



void pompoko::update()
{

	mario::update();

	if (_state != STATE_ATTACK)
	{
		_atRC = RectMake(0, 0, 0, 0);
	}


}

void pompoko::render()
{
	this->draw();

}



void pompoko::attack()
{
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_state != STATE_DIE &&
			_state != STATE_ATTACK)
		{
			marioStateChange(STATE_ATTACK);
			missileFire();

		}
	}
}

void pompoko::draw()
{
	if (_isDebug)
	{
		Rectangle(CAMERAMANAGER->getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
		Rectangle(CAMERAMANAGER->getMemDC(), _atRC.left, _atRC.top, _atRC.right, _atRC.bottom);
	}
	IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->frameRender(CAMERAMANAGER->getMemDC(), _rc.left, _rc.top, _frameX, _dir);


}

void pompoko::missileFire()
{
	if (_dir == DIR_RIGHT)
	{

			_atRC = RectMake(_x+10, _y, 10, 10);

	}

	if (_dir == DIR_LEFT)
	{


			_atRC = RectMake(_x-20, _y, 10, 10);

	}

}


