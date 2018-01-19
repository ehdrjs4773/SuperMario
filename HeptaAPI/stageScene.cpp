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
	IMAGEMANAGER->addFrameImage("�ڽ�", ".\\bmps\\box.bmp", 64, 16, 4, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ڽ��浹", ".\\bmps\\boxCollstion.bmp", 64, 16, 4, 1, false, true, RGB(255, 0, 255));



	SOUNDMANAGER->addSound("�������", ".\\Sounds\\bgm.mp3", false, true);
	SOUNDMANAGER->play("�������", 1.0F);

	for (int i = 0; i < 6; i++)
	{
		_itemBox[i].itemImage = IMAGEMANAGER->findImage("�ڽ�");
		_itemBox[i].Collsion = false;
		_itemBox[0].rc = RectMakeCenter(184, 360, 16, 16);
		_itemBox[1].rc = RectMakeCenter(232, 312, 16, 16);
		_itemBox[2].rc = RectMakeCenter(424, 328, 16, 16);
		_itemBox[3].rc = RectMakeCenter(712, 360, 16, 16);
		_itemBox[4].rc = RectMakeCenter(664, 392, 16, 16);
		_itemBox[5].rc = RectMakeCenter(1480, 376, 16, 16);
		
	}
	_currentFrameX = 0;

	// �׽�Ʈ�� �÷��̾�
	switch (DATABASE->getCharacter())
	{
		case KIND_HAMMER:
			_player = new mario;
			_player->init(_characterKey[KIND_HAMMER], 50, WINSIZEY / 2);
		break;
	}

	return S_OK;
}


void stageScene::release(void) 
{

}


void stageScene::update(void)  
{
	_count++;
	if (_count % 10 == 0)
	{
		_currentFrameX++;
		if (_currentFrameX > _itemBox[0].itemImage->getMaxFrameX()) _currentFrameX = 0;

		_count = 0;
	}

	_player->update();
	CAMERAMANAGER->cameraMove(_player->getPos().x, _player->getPos().y);
}


void stageScene::render(void)  
{
	//IMAGEMANAGER->findImage("�޹��")->render(getMemDC());
	IMAGEMANAGER->findImage("���")->render(CAMERAMANAGER->getMemDC(), 0, 0);

	for (int i = 0; i < 6; i++)
	{
		_itemBox[i].itemImage->frameRender(CAMERAMANAGER->getMemDC(), _itemBox[i].rc.left, _itemBox[i].rc.top, _currentFrameX, 0);
	}

	_player->render();

	CAMERAMANAGER->render(getMemDC());

}

