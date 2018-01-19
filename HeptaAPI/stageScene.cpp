#include "stdafx.h"
#include "stageScene.h"



stageScene::stageScene()
{
}


stageScene::~stageScene()
{

}




HRESULT stageScene::init(void)  
{
	IMAGEMANAGER->addImage("¹è°æ", ".\\bmp\\stargeOne.bmp", 2815, 432, false, true, RGB(255, 0, 255));

	return S_OK;
}


void stageScene::release(void) 
{

}


void stageScene::update(void)  
{

}


void stageScene::render(void)  
{

}

