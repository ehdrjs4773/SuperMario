#include "stdafx.h"
#include "enemyManager.h"
#include "mario.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{

}

HRESULT enemyManager::init() 
{
	_respawn = new respawn;
	_respawn->init();

	for (int i = 0; i < 3; i++)
	{
		//_viFlower[i]->getDirectionY();
	}


	return S_OK;
}
void enemyManager::release() 
{

}
void enemyManager::update()	 
{
	//플레이어 거리 재는 렉트(아직 테스트용)
	_cameraRc = RectMake(_player->getPos().x - 200, _player->getPos().x + 200, 400, 50);
	_respawn->update();
}

void enemyManager::render()	 
{
	_respawn->render();
}



