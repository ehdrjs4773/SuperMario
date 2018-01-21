#pragma once
#include "gameNode.h"
#include "respawn.h"
#include <vector>

class mario;

class enemyManager : public gameNode
{
private:
	mario* _player;
	respawn* _respawn;
	RECT _cameraRc;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	inline void setPlayerMemoryAddressLink(mario* player) { _player = player; }
};

