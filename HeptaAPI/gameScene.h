#pragma once
#include "gameNode.h"
#include "battle.h"
#include "carrier.h"
#include "mutalisk.h"

class gameScene : public gameNode
{
private:
	ship* _player;

public:
	gameScene();
	~gameScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

