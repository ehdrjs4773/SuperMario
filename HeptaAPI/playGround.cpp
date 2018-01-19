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

	// ��� �̹��� ���
	IMAGEMANAGER->addImage("background", ".\\bmps\\background.bmp", WINSIZEX, WINSIZEY, false, true, MAGENTA);


	// �� �߰�
	//SCENEMANAGER->addScene("selectScene", new selectScene);
	//SCENEMANAGER->addScene("gameScene", new gameScene);

	//SCENEMANAGER->changeScene("selectScene");

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

	//SCENEMANAGER->update();
}

//�׸��°�.......
void playGround::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== �� ���� �մ��� ���ÿ� =========================

	IMAGEMANAGER->findImage("background")->render(getMemDC());

	//SCENEMANAGER->render();

	//================== �� �Ʒ��� �մ��� ���ÿ� ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);//hdc������ �׷��ش� 
}
