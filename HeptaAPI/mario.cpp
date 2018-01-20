#include "stdafx.h"
#include "mario.h"



mario::mario()
{
}


mario::~mario()
{
}

HRESULT mario::init(const string imageName, float x, float y)
{
	// 마리오가 사용할 이미지 등록
	string path = ".\\bmps\\" + imageName + "\\" + imageName + _stateKey[STATE_IDLE] + ".bmp";
	IMAGEMANAGER->addFrameImage(imageName + _stateKey[STATE_IDLE], path.c_str(), 16, 28 * 2, 1, 2, false, true, MAGENTA);
	path = ".\\bmps\\" + imageName + "\\" + imageName + _stateKey[STATE_MOVE] + ".bmp";
	IMAGEMANAGER->addFrameImage(imageName + _stateKey[STATE_MOVE], path.c_str(), 16 * 3, 28 * 2, 3, 2, false, true, MAGENTA);
	path = ".\\bmps\\" + imageName + "\\" + imageName + _stateKey[STATE_JUMP] + ".bmp";
	IMAGEMANAGER->addFrameImage(imageName + _stateKey[STATE_JUMP], path.c_str(), 16 * 3, 27 * 2, 3, 2, false, true, MAGENTA);
	path = ".\\bmps\\" + imageName + "\\" + imageName + _stateKey[STATE_ATTACK] + ".bmp";
	IMAGEMANAGER->addFrameImage(imageName + _stateKey[STATE_ATTACK], path.c_str(), 16 * 2, 28 * 2, 2, 2, false, true, MAGENTA);

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
void mario::release()
{

}

void mario::update()
{
	// 마리오가 죽은 상황이 아니면 이동 및 공격 가능
	if (_state != STATE_DIE)
	{
		this->move();			// 실제 마리오 움직임
		this->attack();			// 마리오 공격!
	}
	this->falling();
	_rc = RectMakeCenter(_x, _y, _width, _height);

	this->frameUpdate();	// 마리오 프레임 업데이트
}

void mario::render()
{
	this->draw();
}

void mario::move()
{
	// 왼쪽 이동
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_state != STATE_ATTACK &&
			_state != STATE_JUMP)
			this->marioStateChange(STATE_MOVE);
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		switch (_state)
		{
		case STATE_MOVE:
			if (!KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_dir = DIR_LEFT;
				_x -= _speed;
			}
			else
				this->marioStateChange(STATE_IDLE);
			break;
		}

		char temp[32];
		sprintf(temp, "뒷배경");
		bool isProbe = false;

		for (int i = _rc.top; i <= _rc.bottom && !isProbe; i += IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 4)
		{
			for (int j = _x - IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2 + _speed; j >= _x - IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2 - _speed; --j)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage(temp)->getMemDC(), j, i);

				if (GetRValue(color) == 0 &&
					GetGValue(color) == 0 &&
					GetBValue(color) == 255)
				{
					_x = j + IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2;
					isProbe = true;
					break;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (_state != STATE_ATTACK &&
			_state != STATE_JUMP)
		{
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
				this->marioStateChange(STATE_MOVE);
			else
				this->marioStateChange(STATE_IDLE);
		}
	}

	//오른쪽 이동
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		if (_state != STATE_ATTACK &&
			_state != STATE_JUMP)
		{
			this->marioStateChange(STATE_MOVE);
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		switch (_state)
		{
		case STATE_MOVE:
			if (!KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_dir = DIR_RIGHT;
				_x += _speed;
			}
			else
				this->marioStateChange(STATE_IDLE);
			break;
		}

		char temp[32];
		sprintf(temp, "뒷배경");
		bool isProbe = false;

		for (int i = _rc.top; i <= _rc.bottom && !isProbe; i += IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 4)
		{
			for (int j = _x + IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2 - _speed; j <= _x + IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2 + _speed; ++j)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage(temp)->getMemDC(), j, i);

				if (GetRValue(color) == 0 &&
					GetGValue(color) == 0 &&
					GetBValue(color) == 255)
				{
					_x = j - IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2;
					isProbe = true;
					break;
				}
			}
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (_state != STATE_ATTACK &&
			_state != STATE_JUMP)
		{
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
				this->marioStateChange(STATE_MOVE);
			else
				this->marioStateChange(STATE_IDLE);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) &&
		_state != STATE_JUMP)
	{
		char temp[32];
		sprintf(temp, "뒷배경");
		int probeY = _y + IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 2 + 1;
		COLORREF color = GetPixel(IMAGEMANAGER->findImage(temp)->getMemDC(), _x - IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2, probeY);
		COLORREF color2 = GetPixel(IMAGEMANAGER->findImage(temp)->getMemDC(), _x + IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2, probeY);
		COLORREF color3 = GetPixel(IMAGEMANAGER->findImage(temp)->getMemDC(), _x, probeY);
		// 밝고 있는 곳의 색이 하늘색이거나 노란색일때만 점프 가능
		if ((GetRValue(color) == 0 &&
			GetGValue(color) == 255 &&
			GetBValue(color) == 255) ||
			(GetRValue(color2) == 0 &&
			GetGValue(color2) == 255 &&
			GetBValue(color2) == 255) ||
			(GetRValue(color3) == 0 &&
			GetGValue(color3) == 255 &&
			GetBValue(color3) == 255) ||

			(GetRValue(color) == 255 &&
			GetGValue(color) == 255 &&
			GetBValue(color) == 0) ||
			(GetRValue(color2) == 255 &&
			GetGValue(color2) == 255 &&
			GetBValue(color2) == 0) ||
			(GetRValue(color3) == 255 &&
			GetGValue(color3) == 255 &&
			GetBValue(color3) == 0))
		{
			_jumpPower = JUMPPOWER;
			_y -= _jumpPower;
		}
	}

	if (_x - _width / 2 < LIMIT_X_LEFT)
		_x = LIMIT_X_LEFT + _width / 2;
	if (_x + _width / 2 > LIMIT_X_RIGHT)
		_x = LIMIT_X_RIGHT - _width / 2;
}

void mario::falling()
{
	char temp[32];
	sprintf(temp, "뒷배경");
	for (int i = _rc.left; i <= _rc.right; i += IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2)
	{
		for (int j = _y + IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 2 - 1; j <= _y + IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 2 + 1; ++j)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(temp)->getMemDC(), i, j);
			if ((GetRValue(color) == 0 &&
				GetGValue(color) == 255 &&
				GetBValue(color) == 255) ||
				(GetRValue(color) == 255 &&
				GetGValue(color) == 255 &&
				GetBValue(color) == 0 &&
				_jumpPower < 0))
			{
				_y = j - IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 2;
				_jumpPower = 0.0f;
				break;
			}
			if (GetRValue(color) == 255 &&
				GetGValue(color) == 0 &&
				GetBValue(color) == 0)
			{
				this->marioStateChange(STATE_DIE);
			}
		}
	}

	_y -= _jumpPower;
	for (int i = _rc.left; i <= _rc.right; i += IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth() / 2)
	{
		for (int j = _y - IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 2 + _jumpPower; j >= _y - IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 2 - _jumpPower; --j)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(temp)->getMemDC(), i, j);
			if (GetRValue(color) == 0 &&
				GetGValue(color) == 255 &&
				GetBValue(color) == 255 &&
				_state != STATE_DIE)
			{
				_y = j + IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 2;
				_jumpPower = 0.0f;
				break;
			}
		}
	}
	_jumpPower -= GRAVITY;
	if (_jumpPower < -JUMPPOWER)
		_jumpPower = -JUMPPOWER;
}

void mario::attack()
{
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_state != STATE_DIE &&
			_state != STATE_ATTACK)
		{
			this->marioStateChange(STATE_ATTACK);
		}
	}
}

void mario::draw()
{
	if (_isDebug)
		Rectangle(CAMERAMANAGER->getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->frameRender(CAMERAMANAGER->getMemDC(), _rc.left, _rc.top, _frameX, _dir);
}

void mario::marioStateChange(MARIO_STATE state)
{
	_state = state;
	_frameX = 0;
	_frameTime = 0;
	_width = IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameWidth();
	_height = IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight();
}

void mario::frameUpdate()
{
	_frameTime++;
	switch (_state)
	{
		case STATE_IDLE:
		break;

		case STATE_MOVE:
			if (_frameTime % 10 == 0)
			{
				_frameX++;

				if (_frameX > IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getMaxFrameX())
					_frameX = 0;

				_frameTime = 0;
			}
		break;

		case STATE_ATTACK:
			if (_frameTime % 10 == 0)
			{
				_frameX++;

				if (_frameX > IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getMaxFrameX())
				{
					_frameX = 0;

					if (KEYMANAGER->isStayKeyDown(VK_LEFT) ||
						KEYMANAGER->isStayKeyDown(VK_RIGHT))
						this->marioStateChange(STATE_MOVE);
					else
						this->marioStateChange(STATE_IDLE);
				}

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