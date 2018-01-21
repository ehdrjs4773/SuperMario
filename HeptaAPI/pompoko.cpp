#include "stdafx.h"
#include "pompoko.h"

pompoko::pompoko()
{
}


pompoko::~pompoko()
{
}


HRESULT pompoko::init(const string imageName, float x, float y)
{
		// 마리오가 사용할 이미지 등록
		string path = ".\\bmps\\" + imageName + "\\" + imageName + _stateKey[STATE_IDLE] + ".bmp";
		IMAGEMANAGER->addFrameImage(imageName + _stateKey[STATE_IDLE], path.c_str(), 21, 28 * 2, 1, 2, false, true, MAGENTA);
		path = ".\\bmps\\" + imageName + "\\" + imageName + _stateKey[STATE_MOVE] + ".bmp";
		IMAGEMANAGER->addFrameImage(imageName + _stateKey[STATE_MOVE], path.c_str(), 23 * 3, 28 * 2, 3, 2, false, true, MAGENTA);
		path = ".\\bmps\\" + imageName + "\\" + imageName + _stateKey[STATE_JUMP] + ".bmp";
		IMAGEMANAGER->addFrameImage(imageName + _stateKey[STATE_JUMP], path.c_str(), 23 * 2, 27 * 2, 2, 2, false, true, MAGENTA);
		path = ".\\bmps\\" + imageName + "\\" + imageName + _stateKey[STATE_ATTACK] + ".bmp";
		IMAGEMANAGER->addFrameImage(imageName + _stateKey[STATE_ATTACK], path.c_str(), 24 * 3, 28 * 2, 3, 2, false, true, MAGENTA);

		_imageName = imageName;
		_x = x;
		_y = y;
		_state = STATE_IDLE;
		_dir = DIR_RIGHT;

		_width = IMAGEMANAGER->findImage(imageName + _stateKey[_state])->getFrameWidth();
		_height = IMAGEMANAGER->findImage(imageName + _stateKey[_state])->getFrameHeight();
		_rc = RectMakeCenter(x, y, _width, _height);

		_speed = MARIO_SPEED;
		_jumpPower = 0.0f;

		_frameX = 0;
		_frameTime = 0;

		return S_OK;
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


