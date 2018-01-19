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
	_imageName = imageName;
	_x = x;
	_y = y;
	_state = STATE_IDLE;

	_width = IMAGEMANAGER->findImage(imageName)->getFrameWidth();
	_height = IMAGEMANAGER->findImage(imageName)->getFrameHeight();
	IMAGEMANAGER->findImage(imageName)->setFrameX(0);
	_rc = RectMakeCenter(x, y, _width, _height);

	_speed = 0.0f;

	return S_OK;
}
void mario::release()
{

}

void mario::update()
{
	this->keyControl();		// 키 입력했을 때 처리
	this->move();			// 실제 배 움직임
	this->frameUpdate();	// 배의 각도에 따른 프레임 업데이트
}

void mario::render()
{
	this->draw();
}

void mario::keyControl()
{
}

void mario::move()
{
}

void mario::draw()
{
	IMAGEMANAGER->findImage(_imageName)->frameRender(getMemDC(), _rc.left, _rc.top);
}

void mario::frameUpdate()
{
}