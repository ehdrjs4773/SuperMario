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
	// 선택 씬 배경음악
	SOUNDMANAGER->addSound("0. selectScene_bgm", ".\\sounds\\selectScene_bgm.mp3", true, true);
	SOUNDMANAGER->play("0. selectScene_bgm", 0.3f);

	// 선택 씬 배경 이미지
	IMAGEMANAGER->addImage("select_background", ".\\bmps\\select_background.bmp", WINSIZEX, WINSIZEY, false, true, MAGENTA);

	// 선택 버튼 이미지
	IMAGEMANAGER->addFrameImage("selectButton", ".\\bmps\\selectButton.bmp", SELECT_WIDTH, SELECT_HEIGHT * 2, 1, 2, false, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("selectBackButton", ".\\bmps\\selectBackButton.bmp", WINSIZEX / 4, WINSIZEY * 2, 1, 2, true, true, MAGENTA);

	// 선택될 캐릭터 이미지들
	IMAGEMANAGER->addFrameImage("pompoko_select", ".\\bmps\\pompoko\\pompoko_select.bmp", 46 * 3, 56, 3, 1, false, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("fire_select", ".\\bmps\\fire\\fire_select.bmp", 32 * 3, 56, 3, 1, false, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("hammer_select", ".\\bmps\\hammer\\hammer_select.bmp", 32 * 3, 56, 3, 1, false, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("frog_select", ".\\bmps\\frog\\frog_select.bmp", 40 * 3, 58, 3, 1, false, true, MAGENTA);

	_selectButton = new button;
	_selectButton->init("selectButton", -1000, -1000, PointMake(0, 1), PointMake(0, 0), selectButtonClick);

	for (int i = 0; i < KIND_END; ++i)
	{
		_selectBackButton[i] = new button;
		_selectBackButton[i]->init("selectBackButton", i * WINSIZEX / 4 + WINSIZEX / 8, WINSIZEY / 2, PointMake(0, 1), PointMake(0, 0), selectBackButtonClick);
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
					IMAGEMANAGER->findImage(_characterKey[i] + "_select")->setFrameX(IMAGEMANAGER->findImage(_characterKey[i] + "_select")->getFrameX() + 1);
					if (IMAGEMANAGER->findImage(_characterKey[i] + "_select")->getFrameX() > IMAGEMANAGER->findImage(_characterKey[i] + "_select")->getMaxFrameX())
						IMAGEMANAGER->findImage(_characterKey[i] + "_select")->setFrameX(0);
				}
				else
					IMAGEMANAGER->findImage(_characterKey[i] + "_select")->setFrameX(0);
			}
		}
	}

	for (int i = 0; i < KIND_END; ++i)
	{
		_selectBackButton[i]->update(i);
		if (i != _currentClickedButton)
			_selectBackButton[i]->setDirection(BUTTONDIRECTION_UP);
	}
}

void selectScene::render()
{
	IMAGEMANAGER->findImage("select_background")->render(getMemDC());

	for (int i = 0; i < KIND_END; ++i)
		_selectBackButton[i]->render();

	if (_isClicked)
		_selectButton->render();

	for (int i = 0; i < KIND_END; ++i)
	{
		IMAGEMANAGER->findImage(_characterKey[i] + "_select")->frameRender(getMemDC(),
			i * WINSIZEX / 4 + WINSIZEX / 8 - IMAGEMANAGER->findImage(_characterKey[i] + "_select")->getFrameWidth() / 2,
			WINSIZEY / 2 - IMAGEMANAGER->findImage(_characterKey[i] + "_select")->getFrameHeight() / 2);
	}
}

void selectScene::selectButtonClick()
{
	DATABASE->setCharacter(_currentClickedButton);
	SCENEMANAGER->changeScene("stageScene");
	SOUNDMANAGER->stop("0. selectScene_bgm");
}

void selectScene::selectBackButtonClick(int num)
{
	_currentClickedButton = num;
	_isClicked = true;
	_selectButtonX = _currentClickedButton * WINSIZEX / 4 + WINSIZEX / 8;
	_selectButtonY = WINSIZEY / 2 + 200;
	_frameTime = -1;
}