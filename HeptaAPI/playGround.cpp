#include "stdafx.h"
#include "playGround.h"
#include "stageScene.h"

playGround::playGround()
{

}


playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);
	
	//========스테이지 테스트용==//
	_x = _y = 0;
	//==== DON'T TOUCH ==동건===//

	// 배경 이미지 등록
	IMAGEMANAGER->addImage("background", ".\\bmps\\background.bmp", WINSIZEX, WINSIZEY, false, true, MAGENTA);


	// 씬 추가
	SCENEMANAGER->addScene("selectScene", new selectScene);
	SCENEMANAGER->addScene("gameScene", new gameScene);

	//=================스테이지 씬 초기화 ==================================//
	SCENEMANAGER->addScene("stageScene", new stageScene);
	CAMERAMANAGER->init(2815, 432, WINSIZEX, WINSIZEY, _x, _y, 3.0f);
	//==============위 에꺼랑 마찬가지============ 내꺼임(동건) =============//


	SCENEMANAGER->changeScene("selectScene");

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
	//============================ 화면 배율 테스트용 ===============//
	//CAMERAMANAGER->cameraMove(_x, _y);
	//
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 3;
	//if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 3;
	//if (KEYMANAGER->isStayKeyDown(VK_UP)) _y -= 3;
	//if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _y += 3;
	//==============================================================//



	SCENEMANAGER->update();
}

//그리는거.......
void playGround::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== 이 위는 손대지 마시오 =========================


	SCENEMANAGER->render();

	//================== 이 아래는 손대지 마시오 ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);//hdc영역에 그려준다 
}
