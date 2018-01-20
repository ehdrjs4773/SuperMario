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
	IMAGEMANAGER->addFrameImage("��ٹ���", ".\\bmps\\��ٹ���.bmp", 0, 0, 72, 18, 4, 1,false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ٴ���", ".\\bmps\\��ٴ���.bmp", 0, 0, 36, 18, 2, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ź��̹���", ".\\bmps\\�ź��̹���.bmp", 0, 0, 72, 60, 4, 2, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ź��̴���", ".\\bmps\\�ź��̴���.bmp", 0, 0, 72, 18, 4, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���β�", ".\\bmps\\���β�.bmp", 0, 0, 72, 35, 4, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ų��", ".\\bmps\\ų��.bmp", 0, 0, 54, 36, 3, 2, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���Ϸ�ó", ".\\bmps\\���Ϸ�ó.bmp", 0, 0, 54, 18, 3, 1, false, true, RGB(255, 0, 255));

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
//�� ���� �Լ�
//-------------------------------------------------------------------

//�ȿ� �¿�ο����ϰŸ� 0 ���Ʒ��ο����ϰŸ� 1 ,x��ǥ,y��ǥ
void enemyManager::setCuba(int move, int x, int y)
{
	enemy* _cuba;
	_cuba = new cuba;
	_cuba->init("��ٹ���", PointMake(x, y));			//300, 416
	_cuba->setMoveType(move);

	_vCuba.push_back(_cuba);
}
//�ȿ� �¿�ο����ϰŸ� 0 ���Ʒ��ο����ϰŸ� 1 ,x��ǥ,y��ǥ
void enemyManager::setTurtle(int move, int x, int y)
{
	enemy* _turtle;
	_turtle = new turtle;
	_turtle->init("�ź��̹���", PointMake(x, y));		//566, 384
	_turtle->setMoveType(move);

	_vTurtle.push_back(_turtle);
}
//�ȿ� �¿�ο����ϰŸ� 0 ���Ʒ��ο����ϰŸ� 1 ,x��ǥ,y��ǥ
void enemyManager::setFlower(int move, int x, int y)
{
	enemy* _flower;
	_flower = new flower;
	_flower->init("���β�", PointMake(x, y));			//367, 368
	_flower->setMoveType(move);

	_vFlower.push_back(_flower);
}
//�ȿ� �¿�ο����ϰŸ� 0 ���Ʒ��ο����ϰŸ� 1 ,x��ǥ,y��ǥ
void enemyManager::setKiller(int move, int x, int y)
{
	enemy* _killer;
	_killer = new killer;
	_killer->init("ų��", PointMake(x, y));
	_killer->setMoveType(move);

	_vCuba.push_back(_killer);
}

//-------------------------------------------------------------------
//�� ���� �Լ�
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

