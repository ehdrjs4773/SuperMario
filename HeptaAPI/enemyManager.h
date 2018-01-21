#pragma once
#include "gameNode.h"
#include "respawn.h"
#include "mario.h"
#include "hammer.h"
#include <vector>

class mario;

class enemyManager : public gameNode
{
private:
	hammer* _player;
	respawn* _respawn;
	RECT _cameraRc;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

};

