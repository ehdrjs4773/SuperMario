#include "stdafx.h"
#include "gameScene.h"



gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

HRESULT gameScene::init()
{
	switch (DATABASE->getCharacter())
	{
		case KIND_BATTLE:
			_player = new battle;
		break;
		
		case KIND_CARRIER:
			_player = new carrier;
		break;
		
		case KIND_MUTALISK:
			_player = new mutalisk;
		break;
	}

	_player->init(_characterKey[DATABASE->getCharacter()], WINSIZEX / 2, WINSIZEY / 2);

	return S_OK;
}

void gameScene::release()
{

}

void gameScene::update()
{
	_player->update();
}

void gameScene::render()
{
	_player->render();
}