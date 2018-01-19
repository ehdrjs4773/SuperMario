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
	IMAGEMANAGER->addImage("¹è°æ", ".\\bmps\\stageOne.bmp", 2815, 432, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("µŞ¹è°æ", ".\\bmps\\stageOneBackGround.bmp", 2815, 432, false, true, RGB(255, 0, 255));
	SOUNDMANAGER->addSound("¹è°æÀ½¾Ç", ".\\Sounds\\bgm.mp3", false, true);
	SOUNDMANAGER->play("¹è°æÀ½¾Ç", 1.0F);




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
	//IMAGEMANAGER->findImage("µŞ¹è°æ")->render(getMemDC());
	IMAGEMANAGER->findImage("¹è°æ")->render(CAMERAMANAGER->getMemDC(), 0, 0);

	CAMERAMANAGER->render(getMemDC());
}

