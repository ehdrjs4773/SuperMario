#include "stdafx.h"
#include "ship.h"



ship::ship()
{
}


ship::~ship()
{
}

HRESULT ship::init(const string imageName, float x, float y)
{
	_imageName = imageName;
	_x = x;
	_y = y;
	_state = STATE_IDLE;

	_width = IMAGEMANAGER->findImage(imageName)->getFrameWidth();
	_height = IMAGEMANAGER->findImage(imageName)->getFrameHeight();
	IMAGEMANAGER->findImage(imageName)->setFrameX(0);
	_rc = RectMakeCenter(x, y, _width, _height);

	_speed = 0.0f;
	_angle = 0.0f;

	return S_OK;
}
void ship::release()
{

}

void ship::update()
{
	this->keyControl();		// Ű �Է����� �� ó��
	this->move();			// ���� �� ������
	this->frameUpdate();	// ���� ������ ���� ������ ������Ʈ
}

void ship::render()
{
	this->draw();
}

void ship::keyControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_state = STATE_MOVE;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		switch (_state)
		{
			case STATE_MOVE:
				_speed += _accel;
				if (_speed > _maxSpeed)
					_speed = _maxSpeed;
			break;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_state = STATE_IDLE;
	}

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		_angle += _angleSpeed * DEG2RAD;
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		_angle -= _angleSpeed * DEG2RAD;

	if (_angle >= PI2)
		_angle -= PI2;
	if (_angle < 0)
		_angle += PI2;
}

void ship::move()
{
	if (_state == STATE_IDLE)
	{
		_speed -= _accel;
		if (_speed < 0)
			_speed = 0;
	}

	_x += cos(_angle) * _speed;
	_y += -sin(_angle) * _speed;

	_rc = RectMakeCenter(_x, _y, _width, _height);
}

void ship::draw()
{
	IMAGEMANAGER->findImage(_imageName)->frameRender(getMemDC(), _rc.left, _rc.top);
}

void ship::frameUpdate()
{
	int frame;		// �̹����� ������ ��ȣ
	float angle;	// �̹��� ����

	// Ư�� ���� ���� �������� ������
	angle = _angle + PI16;
	if (angle >= PI2) angle -= PI2;
	if (angle < 0) angle += PI2;

	// Ư�� ���� ���� ����� �� �������� �����۾�
	frame = (int)(angle / PI8);
	IMAGEMANAGER->findImage(_imageName)->setFrameX(frame);
}