#pragma once
#include "gameNode.h"
#include "killer.h"
#include "turtle.h"
#include "cuba.h"
#include "flower.h"
#include <vector>

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> vEnemy;
	typedef vector<enemy*>::iterator viEnemy;

	vEnemy _vCuba;
	viEnemy _viCuba;

	vEnemy _vTurtle;
	viEnemy _viTurtle;

	vEnemy _vFlower;
	viEnemy _viFlower;

	vEnemy _vKiller;
	viEnemy _viKiller;

	int _count;

public:
	enemyManager();
	~enemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//적 생성 함수
	void setCuba(int move,int x,int y);
	void setTurtle(int move, int x, int y);
	void setFlower(int move, int x, int y);
	void setKiller(int move, int x, int y);
	//적 삭제 함수
	void removeCuba(int arrNum);
	void removeTurtle(int arrNum);
	void removeFlower(int arrNum);
	void removeKiller(int arrNum);

	//접근자
	vector<enemy*> getVCuba() { return _vCuba; }
	vector<enemy*>::iterator getVICuba() { return _viCuba; }

	vector<enemy*> getVTurtle() { return _vTurtle; }
	vector<enemy*>::iterator getVITurtle() { return _viTurtle; }

	vector<enemy*> getVFlower() { return _vFlower; }
	vector<enemy*>::iterator getVIFlower() { return _viFlower; }

	vector<enemy*> getVKiller() { return _vKiller; }
	vector<enemy*>::iterator getVIKiller() { return _viKiller; }
};

