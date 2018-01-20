#include "stdafx.h"
#include "enemyManager.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{

}

HRESULT enemyManager::init() 
{
	IMAGEMANAGER->addFrameImage("쿠바무브", ".\\bmps\\쿠바무브.bmp", 0, 0, 72, 18, 4, 1,false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("쿠바다이", ".\\bmps\\쿠바다이.bmp", 0, 0, 36, 18, 2, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("거북이무브", ".\\bmps\\거북이무브.bmp", 0, 0, 72, 60, 4, 2, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("거북이다이", ".\\bmps\\거북이다이.bmp", 0, 0, 72, 18, 4, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("식인꽃", ".\\bmps\\식인꽃.bmp", 0, 0, 72, 35, 4, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("킬러", ".\\bmps\\킬러.bmp", 0, 0, 54, 36, 3, 2, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("로켓런처", ".\\bmps\\로켓런처.bmp", 0, 0, 54, 18, 3, 1, false, true, RGB(255, 0, 255));

	_count = 0;

	return S_OK;
}
void enemyManager::release() 
{

}
void enemyManager::update()	 
{
	for (_viCuba = _vCuba.begin(); _viCuba != _vCuba.end(); ++_viCuba)
	{
		(*_viCuba)->update();
	}
	for (_viTurtle = _vTurtle.begin(); _viTurtle != _vTurtle.end(); ++_viTurtle)
	{
		(*_viTurtle)->update();
	}
	for (_viFlower = _vFlower.begin(); _viFlower != _vFlower.end(); ++_viFlower)
	{
		(*_viFlower)->update();
	}
	for (_viKiller = _vKiller.begin(); _viKiller != _vKiller.end(); ++_viKiller)
	{
		(*_viKiller)->update();
	}

	
}

void enemyManager::render()	 
{
	for (_viCuba = _vCuba.begin(); _viCuba != _vCuba.end(); ++_viCuba)
	{
		(*_viCuba)->render();
	}
	for (_viTurtle = _vTurtle.begin(); _viTurtle != _vTurtle.end(); ++_viTurtle)
	{
		(*_viTurtle)->render();
	}
	for (_viFlower = _vFlower.begin(); _viFlower != _vFlower.end(); ++_viFlower)
	{
		(*_viFlower)->render();
	}
	for (_viKiller = _vKiller.begin(); _viKiller != _vKiller.end(); ++_viKiller)
	{
		(*_viKiller)->render();
	}
}

//-------------------------------------------------------------------
//적 생성 함수
//-------------------------------------------------------------------

//안에 좌우로움직일거면 0 위아래로움직일거면 1 ,x좌표,y좌표
void enemyManager::setCuba(int move, int x, int y)
{
	enemy* _cuba;
	_cuba = new cuba;
	_cuba->init("쿠바무브", PointMake(x, y));			//300, 416
	_cuba->setMoveType(move);

	_vCuba.push_back(_cuba);
}
//안에 좌우로움직일거면 0 위아래로움직일거면 1 ,x좌표,y좌표
void enemyManager::setTurtle(int move, int x, int y)
{
	enemy* _turtle;
	_turtle = new turtle;
	_turtle->init("거북이무브", PointMake(x, y));		//566, 384
	_turtle->setMoveType(move);

	_vTurtle.push_back(_turtle);
}
//안에 좌우로움직일거면 0 위아래로움직일거면 1 ,x좌표,y좌표
void enemyManager::setFlower(int move, int x, int y)
{
	enemy* _flower;
	_flower = new flower;
	_flower->init("식인꽃", PointMake(x, y));			//367, 368
	_flower->setMoveType(move);

	_vFlower.push_back(_flower);
}
//안에 좌우로움직일거면 0 위아래로움직일거면 1 ,x좌표,y좌표
void enemyManager::setKiller(int move, int x, int y)
{
	enemy* _killer;
	_killer = new killer;
	_killer->init("킬러", PointMake(x, y));
	_killer->setMoveType(move);

	_vCuba.push_back(_killer);
}

//-------------------------------------------------------------------
//적 삭제 함수
//-------------------------------------------------------------------
void enemyManager::removeCuba(int arrNum)	 
{
	SAFE_DELETE(_vCuba[arrNum]);
	_vCuba.erase(_vCuba.begin() + arrNum);
}
void enemyManager::removeTurtle(int arrNum)	 
{
	SAFE_DELETE(_vTurtle[arrNum]);
	_vTurtle.erase(_vTurtle.begin() + arrNum);
}
void enemyManager::removeFlower(int arrNum)	 
{
	SAFE_DELETE(_vFlower[arrNum]);
	_vFlower.erase(_vFlower.begin() + arrNum);
}
void enemyManager::removeKiller(int arrNum)	 
{
	SAFE_DELETE(_vKiller[arrNum]);
	_vKiller.erase(_vKiller.begin() + arrNum);
}

