#include "stdafx.h"
#include "selectScene.h"


selectScene::selectScene()
{
}


selectScene::~selectScene()
{
}

int selectScene::_currentClickedButton = 0;
bool selectScene::_isClicked = false;
int selectScene::_selectButtonX = 0;
int selectScene::_selectButtonY = 0;
int selectScene::_frameTime = 0;

HRESULT selectScene::init()
{
	// 선택 버튼 이미지
	IMAGEMANAGER->addFrameImage("selectButton", ".\\bmps\\selectButton.bmp", SELECT_WIDTH, SELECT_HEIGHT * 2, 1, 2, false, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("selectBackButton", ".\\bmps\\selectBackButton.bmp", WINSIZEX / 3, WINSIZEY * 2, 1, 2, false, true, MAGENTA);

	// 선택될 캐릭터 이미지들
	IMAGEMANAGER->addFrameImage("battle", ".\\bmps\\battle.bmp", 96 * 16, 79, 16, 1, false, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("carrier", ".\\bmps\\carrier.bmp", 96 * 16, 96, 16, 1, false, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("mutalisk", ".\\bmps\\mutalisk.bmp", 64 * 16, 62, 16, 1, false, true, CYAN);

	_selectButton = new button;
	_selectButton->init("selectButton", 0, 0, PointMake(0, 1), PointMake(0, 0), selectButtonClick);

	for (int i = 0; i < 3; ++i)
	{
		_selectBackButton[i] = new button;
		_selectBackButton[i]->init("selectBackButton", i * WINSIZEX / 3 + WINSIZEX / 6, WINSIZEY / 2, PointMake(0, 1), PointMake(0, 0), selectBackButtonClick);
	}

	return S_OK;
}

void selectScene::release()
{

}

void selectScene::update()
{
	// 버튼들 업데이트
	// 우선순위의 중요성...
	if (_isClicked)
	{
		_selectButton->setPosition(PointMake(_selectButtonX, _selectButtonY));
		_selectButton->update();

		_frameTime++;
		for (int i = 0; i < KIND_END; ++i)
		{
			if (_frameTime % 10 == 0)
			{
				if (_currentClickedButton == i)
				{
					IMAGEMANAGER->findImage(_characterKey[i])->setFrameX(IMAGEMANAGER->findImage(_characterKey[i])->getFrameX() + 1);
					if (IMAGEMANAGER->findImage(_characterKey[i])->getFrameX() > IMAGEMANAGER->findImage(_characterKey[i])->getMaxFrameX())
						IMAGEMANAGER->findImage(_characterKey[i])->setFrameX(0);
				}
				else
					IMAGEMANAGER->findImage(_characterKey[i])->setFrameX(0);
			}
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		_selectBackButton[i]->update(i);
		if (i != _currentClickedButton)
			_selectBackButton[i]->setDirection(BUTTONDIRECTION_UP);
	}
}

void selectScene::render()
{
	for (int i = 0; i < 3; ++i)
		_selectBackButton[i]->render();

	if (_isClicked)
		_selectButton->render();

	for (int i = 0; i < KIND_END; ++i)
	{
		IMAGEMANAGER->findImage(_characterKey[i])->frameRender(getMemDC(),
			i * WINSIZEX / 3 + WINSIZEX / 6 - IMAGEMANAGER->findImage(_characterKey[i])->getFrameWidth() / 2,
			WINSIZEY / 2 - IMAGEMANAGER->findImage(_characterKey[i])->getFrameHeight() / 2);
	}
}

void selectScene::selectButtonClick()
{
	DATABASE->setCharacter(_currentClickedButton);
	SCENEMANAGER->changeScene("gameScene");
}

void selectScene::selectBackButtonClick(int num)
{
	_currentClickedButton = num;
	_isClicked = true;
	_selectButtonX = _currentClickedButton * WINSIZEX / 3 + WINSIZEX / 6;
	_selectButtonY = WINSIZEY / 2 + 200;
	_frameTime = -1;
}