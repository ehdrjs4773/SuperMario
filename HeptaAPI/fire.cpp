#include "stdafx.h"
#include "fire.h"



fire::fire()
{
}


fire::~fire()
{
}


 HRESULT fire::init(const string imageName, float x, float y)
 {

	 mario::init(imageName, x, y);

	 _missile = new MF;
	 _missile->init( 30, 100);

	 return S_OK;
 }

 void fire::update()
{
	// 마리오가 죽은 상황이 아니면 이동 및 공격 가능
	if (_state != STATE_DIE)
	{
		this->move();			// 실제 마리오 움직임
		this->attack();			// 마리오 공격!
	}
	this->falling();
	_rc = RectMakeCenter(_x, _y, _width, _height);

	this->missileMove();

	this->frameUpdate();	// 마리오 프레임 업데이트

	if (KEYMANAGER->isOnceKeyDown('C')) missileFire();
}

void fire::render()
{
	this->draw();
	this->missileDraw();
}

void fire::move()
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
		if (!(GetRValue(color) == 255 &&
			GetGValue(color) == 0 &&
			GetBValue(color) == 255) ||
			!(GetRValue(color2) == 255 &&
				GetGValue(color2) == 0 &&
				GetBValue(color2) == 255) ||
			!(GetRValue(color3) == 255 &&
				GetGValue(color3) == 0 &&
				GetBValue(color3) == 255))
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


void fire::attack()
{
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_state != STATE_DIE &&
			_state != STATE_ATTACK)
		{
			this->marioStateChange(STATE_ATTACK);
			this->missileFire();
			this->marioStateChange(STATE_IDLE);
		}
	}
}

void fire::draw()
{
	if (_isDebug)
		Rectangle(CAMERAMANAGER->getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->frameRender(CAMERAMANAGER->getMemDC(), _rc.left, _rc.top, _frameX, _dir);


}

void fire::missileFire()
{
	float x = _x ;
	float y = _y	;

	_missile->fire(x, y);
}

void fire::missileMove()
{
	_missile->update();
}

void fire::missileDraw()
{
	_missile->render();
}
