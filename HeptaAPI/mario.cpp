#include "stdafx.h"
#include "mario.h"
#include "enemyManager.h"



mario::mario()
{
}


mario::~mario()
{
}

HRESULT mario::init(const string imageName, float x, float y)
{
	// 마리오가 사용할 사운드 등록
	SOUNDMANAGER->addSound("3. marioJump", ".\\sounds\\jump.mp3", false, false);

	// 마리오가 사용할 이미지 등록
	// 현재 고른 캐릭터에 따라 다르게 등록함
	switch (DATABASE->getCharacter())
	{
		case KIND_POMPOKO:
			IMAGEMANAGER->addFrameImage("pompoko_idle", ".\\bmps\\pompoko\\pompoko_idle.bmp", POMPOKO_IDLE_WIDTH, POMPOKO_IDLE_HEIGHT * 2, 1, 2, false, true, MAGENTA);
			IMAGEMANAGER->addFrameImage("pompoko_move", ".\\bmps\\pompoko\\pompoko_move.bmp", POMPOKO_MOVE_WIDTH * 3, POMPOKO_MOVE_HEIGHT * 2, 3, 2, false, true, MAGENTA);
			IMAGEMANAGER->addFrameImage("pompoko_jump", ".\\bmps\\pompoko\\pompoko_jump.bmp", POMPOKO_JUMP_WIDTH, POMPOKO_JUMP_HEIGHT * 2, 1, 2, false, true, MAGENTA);
			IMAGEMANAGER->addFrameImage("pompoko_attack", ".\\bmps\\pompoko\\pompoko_attack.bmp", POMPOKO_ATTACK_WIDTH * 3, POMPOKO_ATTACK_HEIGHT * 2, 3, 2, false, true, MAGENTA);
		break;
		
		case KIND_FIRE:
			IMAGEMANAGER->addFrameImage("fire_idle", ".\\bmps\\fire\\fire_idle.bmp", FIRE_IDLE_WIDTH, FIRE_IDLE_HEIGHT * 2, 1, 2, false, true, MAGENTA);
			IMAGEMANAGER->addFrameImage("fire_move", ".\\bmps\\fire\\fire_move.bmp", FIRE_MOVE_WIDTH * 3, FIRE_MOVE_HEIGHT * 2, 3, 2, false, true, MAGENTA);
			IMAGEMANAGER->addFrameImage("fire_jump", ".\\bmps\\fire\\fire_jump.bmp", FIRE_JUMP_WIDTH, FIRE_JUMP_HEIGHT * 2, 1, 2, false, true, MAGENTA);
			IMAGEMANAGER->addFrameImage("fire_attack", ".\\bmps\\fire\\fire_attack.bmp", FIRE_ATTACK_WIDTH * 2, FIRE_ATTACK_HEIGHT * 2, 2, 2, false, true, MAGENTA);
		break;
		
		case KIND_HAMMER:
			IMAGEMANAGER->addFrameImage("hammer_idle", ".\\bmps\\hammer\\hammer_idle.bmp", HAMMER_IDLE_WIDTH, HAMMER_IDLE_HEIGHT * 2, 1, 2, false, true, MAGENTA);
			IMAGEMANAGER->addFrameImage("hammer_move", ".\\bmps\\hammer\\hammer_move.bmp", HAMMER_MOVE_WIDTH * 3, HAMMER_MOVE_HEIGHT * 2, 3, 2, false, true, MAGENTA);
			IMAGEMANAGER->addFrameImage("hammer_jump", ".\\bmps\\hammer\\hammer_jump.bmp", HAMMER_JUMP_WIDTH, HAMMER_JUMP_HEIGHT * 2, 1, 2, false, true, MAGENTA);
			IMAGEMANAGER->addFrameImage("hammer_attack", ".\\bmps\\hammer\\hammer_attack.bmp", HAMMER_ATTACK_WIDTH * 2, HAMMER_ATTACK_HEIGHT * 2, 2, 2, false, true, MAGENTA);
		break;
		
		case KIND_FROG:
			IMAGEMANAGER->addFrameImage("frog_idle", ".\\bmps\\frog\\frog_idle.bmp", FROG_IDLE_WIDTH, FROG_IDLE_HEIGHT * 2, 1, 2, false, true, MAGENTA);
			IMAGEMANAGER->addFrameImage("frog_move", ".\\bmps\\frog\\frog_move.bmp", FROG_MOVE_WIDTH * 3, FROG_MOVE_HEIGHT * 2, 3, 2, false, true, MAGENTA);
			IMAGEMANAGER->addFrameImage("frog_jump", ".\\bmps\\frog\\frog_jump.bmp", FROG_JUMP_WIDTH, FROG_JUMP_HEIGHT * 2, 1, 2, false, true, MAGENTA);
			//IMAGEMANAGER->addFrameImage("hammer_attack", ".\\bmps\\hammer\\hammer_attack.bmp", HAMMER_ATTACK_WIDTH * 2, HAMMER_ATTACK_HEIGHT * 2, 2, 2, false, true, MAGENTA);
		break;
	}

	//string path = ".\\bmps\\" + imageName + "\\" + imageName + _stateKey[STATE_IDLE] + ".bmp";
	//IMAGEMANAGER->addFrameImage(imageName + _stateKey[STATE_IDLE], path.c_str(), 16, 28 * 2, 1, 2, false, true, MAGENTA);
	//path = ".\\bmps\\" + imageName + "\\" + imageName + _stateKey[STATE_MOVE] + ".bmp";
	//IMAGEMANAGER->addFrameImage(imageName + _stateKey[STATE_MOVE], path.c_str(), 16 * 3, 28 * 2, 3, 2, false, true, MAGENTA);
	//path = ".\\bmps\\" + imageName + "\\" + imageName + _stateKey[STATE_JUMP] + ".bmp";
	//IMAGEMANAGER->addFrameImage(imageName + _stateKey[STATE_JUMP], path.c_str(), 16, 27 * 2, 1, 2, false, true, MAGENTA);
	//path = ".\\bmps\\" + imageName + "\\" + imageName + _stateKey[STATE_ATTACK] + ".bmp";
	//IMAGEMANAGER->addFrameImage(imageName + _stateKey[STATE_ATTACK], path.c_str(), 16 * 2, 28 * 2, 2, 2, false, true, MAGENTA);

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
	if (_state != STATE_CLEAR)
	{
		// 마리오가 죽은 상황이 아니면 이동 및 공격 가능
		if (_state != STATE_DIE)
		{
			this->move();			// 실제 마리오 움직임
			this->attack();			// 마리오 공격!
		}
		this->falling();
		_rc = RectMakeCenter(_x, _y, _width, _height);

		if (_state != STATE_DIE)
			this->collisionControl();
	}
	else
	{
		_y += _jumpPower;
		_jumpPower -= GRAVITY;
		_rc = RectMakeCenter(_x, _y, _width, _height);
	}

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
			case STATE_MOVE: case STATE_JUMP: case STATE_ATTACK:
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
			case STATE_MOVE: case STATE_JUMP: case STATE_ATTACK:
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
			this->marioStateChange(STATE_JUMP);

			if (_imageName == "frog")
				_jumpPower = JUMPPOWER + 1.0f;
			else
				_jumpPower = JUMPPOWER;

			_y -= _jumpPower;

			SOUNDMANAGER->play("3. marioJump");
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
			if (((GetRValue(color) == 0 &&
				GetGValue(color) == 255 &&
				GetBValue(color) == 255) ||
				(GetRValue(color) == 255 &&
				GetGValue(color) == 255 &&
				GetBValue(color) == 0 &&
				_jumpPower < 0)) &&
				_state != STATE_DIE)
			{
				_y = j - IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getFrameHeight() / 2;
				_jumpPower = 0.0f;

				if (_state == STATE_JUMP)
				{
					if (KEYMANAGER->isStayKeyDown(VK_LEFT) ||
						KEYMANAGER->isStayKeyDown(VK_RIGHT))
						this->marioStateChange(STATE_MOVE);
					else
						this->marioStateChange(STATE_IDLE);
				}
				break;
			}
			if (GetRValue(color) == 255 &&
				GetGValue(color) == 0 &&
				GetBValue(color) == 0 &&
				_state != STATE_DIE)
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
		
		case STATE_CLEAR:
			if (_frameTime % 3 == 0)
			{
				_frameX++;

				if (_frameX > IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->getMaxFrameX())
					_frameX = 0;

				_frameTime = 0;
			}
		break;
	}
}

void mario::collisionControl()
{
	this->collisionWithEnemy();
}

void mario::collisionWithEnemy()
{
	// 쿠바
	for (int i = 0; i < _em->getRespawn()->getVCuba().size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp, &_rc, &_em->getRespawn()->getVCuba()[i]->getEnemyRect()))
		{
			// 겹친 부분의 가로, 세로 길이
			int tempWidth = temp.right - temp.left;
			int tempHeight = temp.bottom - temp.top;

			// 가로길이 > 세로길이 == 위, 아래에서 부딪혔으면
			if (tempWidth >= tempHeight)
			{
				// 플레이어가 위에 있다면 -> 적 사망
				if (_y < _em->getRespawn()->getVCuba()[i]->getEnemyRect().bottom)
				{
					_em->getRespawn()->removeCuba(i);
					this->marioStateChange(STATE_JUMP);
					_jumpPower = JUMPPOWER - 1.0f;
					_y -= _jumpPower;
				}
				else
				{
					this->marioStateChange(STATE_DIE);
					_jumpPower = JUMPPOWER;
					_y -= _jumpPower;
				}
			}
			else
			{
				this->marioStateChange(STATE_DIE);
				_jumpPower = JUMPPOWER;
				_y -= _jumpPower;
			}
		}
	}

	// 킬러
	for (int i = 0; i < _em->getRespawn()->getVKiller().size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp, &_rc, &_em->getRespawn()->getVKiller()[i]->getEnemyRect()))
		{
			// 겹친 부분의 가로, 세로 길이
			int tempWidth = temp.right - temp.left;
			int tempHeight = temp.bottom - temp.top;

			// 가로길이 > 세로길이 == 위, 아래에서 부딪혔으면
			if (tempWidth >= tempHeight)
			{
				// 플레이어가 위에 있다면 -> 적 사망
				if (_y < _em->getRespawn()->getVKiller()[i]->getEnemyRect().bottom)
				{
					_em->getRespawn()->removeCuba(i);
					this->marioStateChange(STATE_JUMP);
					_jumpPower = JUMPPOWER - 1.0f;
					_y -= _jumpPower;
				}
				else
				{
					this->marioStateChange(STATE_DIE);
					_jumpPower = JUMPPOWER;
					_y -= _jumpPower;
				}
			}
			else
			{
				this->marioStateChange(STATE_DIE);
				_jumpPower = JUMPPOWER;
				_y -= _jumpPower;
			}
		}
	}

	// 꽃
	for (int i = 0; i < _em->getRespawn()->getVFlower().size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp, &_rc, &_em->getRespawn()->getVFlower()[i]->getEnemyRect()))
		{
			// 겹친 부분의 가로, 세로 길이
			int tempWidth = temp.right - temp.left;
			int tempHeight = temp.bottom - temp.top;

			// 가로길이 > 세로길이 == 위, 아래에서 부딪혔으면
			if (tempWidth >= tempHeight)
			{
				// 플레이어가 위에 있다면 -> 적 사망
				if (_y < _em->getRespawn()->getVFlower()[i]->getEnemyRect().bottom)
				{
					_em->getRespawn()->removeCuba(i);
					this->marioStateChange(STATE_JUMP);
					_jumpPower = JUMPPOWER - 1.0f;
					_y -= _jumpPower;
				}
				else
				{
					this->marioStateChange(STATE_DIE);
					_jumpPower = JUMPPOWER;
					_y -= _jumpPower;
				}
			}
			else
			{
				this->marioStateChange(STATE_DIE);
				_jumpPower = JUMPPOWER;
				_y -= _jumpPower;
			}
		}
	}

	// 거북이
	for (int i = 0; i < _em->getRespawn()->getVTurtle().size(); ++i)
	{
		RECT temp;
		if (IntersectRect(&temp, &_rc, &_em->getRespawn()->getVTurtle()[i]->getEnemyRect()))
		{
			// 겹친 부분의 가로, 세로 길이
			int tempWidth = temp.right - temp.left;
			int tempHeight = temp.bottom - temp.top;

			// 가로길이 > 세로길이 == 위, 아래에서 부딪혔으면
			if (tempWidth >= tempHeight)
			{
				// 플레이어가 위에 있다면 -> 적 사망
				if (_y < _em->getRespawn()->getVTurtle()[i]->getEnemyRect().bottom)
				{
					_em->getRespawn()->removeCuba(i);
					this->marioStateChange(STATE_JUMP);
					_jumpPower = JUMPPOWER - 1.0f;
					_y -= _jumpPower;
				}
				else
				{
					this->marioStateChange(STATE_DIE);
					_jumpPower = JUMPPOWER;
					_y -= _jumpPower;
				}
			}
			else
			{
				this->marioStateChange(STATE_DIE);
				_jumpPower = JUMPPOWER;
				_y -= _jumpPower;
			}
		}
	}
}