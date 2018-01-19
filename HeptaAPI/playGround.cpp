#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{

}


playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);

	// 배경 이미지 등록
	IMAGEMANAGER->addImage("background", ".\\bmps\\background.bmp", WINSIZEX, WINSIZEY, false, true, MAGENTA);


	// 씬 추가
	//SCENEMANAGER->addScene("selectScene", new selectScene);
	//SCENEMANAGER->addScene("gameScene", new gameScene);

	//SCENEMANAGER->changeScene("selectScene");

	//DATABASE->init();

	return S_OK;
}

//메모리 관련 삭제
void playGround::release(void)
{
	gameNode::release();

}

//연산
void playGround::update(void)
{
	gameNode::update();

	//SCENEMANAGER->update();
}

//그리는거.......
void playGround::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== 이 위는 손대지 마시오 =========================

	IMAGEMANAGER->findImage("background")->render(getMemDC());

	//SCENEMANAGER->render();

	//================== 이 아래는 손대지 마시오 ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);//hdc영역에 그려준다 
}
