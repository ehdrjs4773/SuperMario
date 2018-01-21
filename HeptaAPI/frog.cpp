#include "stdafx.h"
#include "frog.h"




frog::frog()
{
}


frog::~frog()
{

}

HRESULT frog::init(const string imageName, float x, float y)
{
	mario::init(imageName, x, y);

	return S_OK;
}

void frog::release()										
{
	mario::release();
}

void frog::update()											
{
	mario::update();
}

void frog::render()											
{
	mario::render();
}

void frog::draw()
{
	if (_isDebug)
		Rectangle(CAMERAMANAGER->getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->frameRender(CAMERAMANAGER->getMemDC(), _rc.left, _rc.top, _frameX, _dir);
}
