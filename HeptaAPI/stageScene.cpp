#include "stdafx.h"
#include "stageScene.h"



stageScene::stageScene()
	: _player(NULL),
	_em(NULL)
{
}


stageScene::~stageScene()
{
}




HRESULT stageScene::init(void)  
{
	IMAGEMANAGER->addImage("배경", ".\\bmps\\stageOne.bmp", 2815, 432, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("뒷배경", ".\\bmps\\stageOneBackGround.bmp", 2815, 432, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("박스", ".\\bmps\\box.bmp", 64, 16, 4, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("박스충돌", ".\\bmps\\boxCollstion.bmp", 64, 16, 4, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("코인", ".\\bmps\\item\\item_coin.bmp", 56, 16, 4, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("finalImage", ".\\bmps\\finalstar.bmp", 26, 26, false, true, RGB(255, 0, 255));


	SOUNDMANAGER->addSound("1. 배경음악", ".\\sounds\\bgm.mp3", true, true);
	SOUNDMANAGER->play("1. 배경음악", 1.0F);
	SOUNDMANAGER->addSound("2. 박스쳤다", ".\\sounds\\boxcollstion.mp3", false, false);



	for (int i = 0; i < 8; i++)
	{
		_itemBox[i].itemImage = IMAGEMANAGER->findImage("박스");
		_itemBox[i].Collsion = false;
		_itemBox[0].rc = RectMakeCenter(184, 360, 16, 16);
		_itemBox[6].rc = RectMakeCenter(200, 360, 16, 16);
		_itemBox[1].rc = RectMakeCenter(232, 312, 16, 16);
		_itemBox[7].rc = RectMakeCenter(248, 312, 16, 16);
		_itemBox[2].rc = RectMakeCenter(424, 328, 16, 16);
		_itemBox[3].rc = RectMakeCenter(712, 360, 16, 16);
		_itemBox[4].rc = RectMakeCenter(664, 392, 16, 16);
		_itemBox[5].rc = RectMakeCenter(1480, 376, 16, 16);

	}

	_finishRect = RectMakeCenter(2696, 344, 26, 26);


	_currentFrameX = 0;

	_item = new item;
	_item->init();

	// 테스트용 플레이어
	switch (DATABASE->getCharacter())
	{
		case KIND_HAMMER:
			if (_player == NULL)
				_player = new hammer;
			_player->init(_characterKey[KIND_HAMMER], 50, WINSIZEY / 2);
		break;

		case KIND_FIRE:
			if (_player == NULL)
				_player = new fire;
			_player->init(_characterKey[KIND_FIRE], 50, WINSIZEY / 2);
		break;

		case KIND_POMPOKO:
			if (_player == NULL)
				_player = new pompoko;
			_player->init(_characterKey[KIND_POMPOKO], 50, WINSIZEY / 2);
		break;

		case KIND_FROG:
			if (_player == NULL)
				_player = new frog;
			_player->init(_characterKey[KIND_FROG], 50, WINSIZEY / 2);
		break;
	}

	if (_em == NULL)
		_em = new enemyManager;
	_em->init();

	_player->setEMMemoryAddressLink(_em);
	_em->setPlayerMemoryAddressLink(_player);

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
	_item->update();

	if (_player->getState() != STATE_CLEAR)
		CAMERAMANAGER->cameraMove(_player->getPos().x, _player->getPos().y);

	RECT temp;
	for (int i = 0; i < 8; i++)
	{
		if (IntersectRect(&temp, &_player->getRC(), &_itemBox[i].rc))
		{
			if (_player->getPos().y > _itemBox[i].rc.bottom &&
				_player->getPos().x > _itemBox[i].rc.left &&
				_player->getPos().x < _itemBox[i].rc.right)
			{
				if (_itemBox[i].Collsion) return;

				_itemBox[i].Collsion = true;
				SOUNDMANAGER->play("2. 박스쳤다", 1.0f);
				_itemBox[i].itemImage = IMAGEMANAGER->findImage("박스충돌");
				_item->setItem(_itemBox[i].rc.left, _itemBox[i].rc.top, ITME_COIN, "코인");
				break;
			}
		}
	}
	
	_em->update();


	// 마리오 죽었을 떄 처리
	if (_player->getState() == STATE_DIE &&
		_player->getPos().y > 1000)
		this->init();

	// 스테이지 클리어 상자랑 인터섹트렉트
	if (IntersectRect(&temp, &_player->getRC(), &_finishRect) &&
		_player->getState() != STATE_CLEAR)
	{
		_player->marioStateChange(STATE_CLEAR);
		_player->setJumpPower(0.0f);
	}
}


void stageScene::render(void)  
{
	IMAGEMANAGER->findImage("배경")->render(CAMERAMANAGER->getMemDC(), 0, 0);

	_item->render();

	if (_isDebug)

	{
		IMAGEMANAGER->findImage("뒷배경")->render(CAMERAMANAGER->getMemDC());
		Rectangle(CAMERAMANAGER->getMemDC(), _finishRect.left, _finishRect.top, _finishRect.right, _finishRect.bottom);
	}
	if (!_isDebug)
	for (int i = 0; i < 8; i++)
	{
		IMAGEMANAGER->findImage("finalImage")->render(CAMERAMANAGER->getMemDC(), _finishRect.left, _finishRect.top);
		_itemBox[i].itemImage->frameRender(CAMERAMANAGER->getMemDC(), _itemBox[i].rc.left, _itemBox[i].rc.top, _currentFrameX, 0);
	}

	_player->render();

	_em->render();

	CAMERAMANAGER->render(getMemDC());

}

