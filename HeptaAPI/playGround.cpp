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
	
	//========�������� �׽�Ʈ��==//
	_x = _y = 0;
	//==== DON'T TOUCH ==����===//

	// ��� �̹��� ���
	IMAGEMANAGER->addImage("background", ".\\bmps\\background.bmp", WINSIZEX, WINSIZEY, false, true, MAGENTA);


	// �� �߰�
	SCENEMANAGER->addScene("selectScene", new selectScene);
	SCENEMANAGER->addScene("gameScene", new gameScene);

	//=================�������� �� �ʱ�ȭ ==================================//
	SCENEMANAGER->addScene("stageScene", new stageScene);
	CAMERAMANAGER->init(2815, 432, WINSIZEX, WINSIZEY, _x, _y, 3.0f);
	//==============�� ������ ��������============ ������(����) =============//


	SCENEMANAGER->changeScene("selectScene");

	//DATABASE->init();

	return S_OK;
}

//�޸� ���� ����
void playGround::release(void)
{
	gameNode::release();

}

//����
void playGround::update(void)
{
	gameNode::update();
	//============================ ȭ�� ���� �׽�Ʈ�� ===============//
	//CAMERAMANAGER->cameraMove(_x, _y);
	//
	//if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) _x += 3;
	//if (KEYMANAGER->isStayKeyDown(VK_LEFT)) _x -= 3;
	//if (KEYMANAGER->isStayKeyDown(VK_UP)) _y -= 3;
	//if (KEYMANAGER->isStayKeyDown(VK_DOWN)) _y += 3;
	//==============================================================//



	SCENEMANAGER->update();
}

//�׸��°�.......
void playGround::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== �� ���� �մ��� ���ÿ� =========================


	SCENEMANAGER->render();

	//================== �� �Ʒ��� �մ��� ���ÿ� ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);//hdc������ �׷��ش� 
}
