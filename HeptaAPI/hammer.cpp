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
	_bullet = new bullet;


	return S_OK;
}
void hammer::release()
{
	mario::release();
	_bullet->release();

}
void hammer::update() 
{
	mario::update();
	keyControl();
	_bullet->update();

}
void hammer::render() 
{
	mario::render();
	_bullet->render();

}

void hammer::keyControl()
{

}
void hammer::move()
{

}
void hammer::draw()
{

}

void hammer::frameUpdate()
{

}