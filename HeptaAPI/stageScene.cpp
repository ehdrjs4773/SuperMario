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
	IMAGEMANAGER->addImage("���", ".\\bmps\\stageOne.bmp", 2815, 432, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޹��", ".\\bmps\\stageOneBackGround.bmp", 2815, 432, false, true, RGB(255, 0, 255));

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
	//IMAGEMANAGER->findImage("�޹��")->render(getMemDC());
	IMAGEMANAGER->findImage("���")->render(CAMERAMANAGER->getMemDC(), 0, 0);
}

