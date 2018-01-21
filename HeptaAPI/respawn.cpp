#include "stdafx.h"
#include "respawn.h"

respawn::respawn()
{
}
respawn::~respawn()
{
}

HRESULT respawn::init()	 
{
	IMAGEMANAGER->addFrameImage("��ٹ���", ".\\bmps\\��ٹ���.bmp", 0, 0, 72, 36, 4, 2, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ٴ���", ".\\bmps\\��ٴ���.bmp", 0, 0, 36, 18, 2, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ź��̹���", ".\\bmps\\�ź��̹���.bmp", 0, 0, 72, 60, 4, 2, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ź��̴���", ".\\bmps\\�ź��̴���.bmp", 0, 0, 72, 18, 4, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���β�", ".\\bmps\\���β�.bmp", 0, 0, 72, 35, 4, 1, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ų��", ".\\bmps\\ų��.bmp", 0, 0, 54, 36, 3, 2, false, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���Ϸ�ó", ".\\bmps\\���Ϸ�ó.bmp", 0, 0, 54, 18, 3, 1, false, true, RGB(255, 0, 255));

	_count = 0;
	_regenTime = 0;

	//�ѹ��� ��ٸ� 5����
	setCuba(0, 270, 415-6 /*- 17*/);
	setCuba(0, 500, 415-6 /*- 17*/);
	setCuba(0, 800, 400-7 /*- 17*/);
	setCuba(0, 840, 400-7 /*- 17*/);
	setCuba(0, 880, 400-7 /*- 17*/);
	//�źα⸦ 5����
	setTurtle(0, 560,  384-13 /*- 29*/);
	setTurtle(0, 1340-20, 384-13 /*- 29*/);
	setTurtle(0, 1380-20, 352-13 /*- 29*/);
	setTurtle(0, 1420-20, 320-13 /*- 29*/);
	setTurtle(0, 1470-13, 415-13 /*- 29*/);
	//���� ���� ������
	setFlower(1, 367, 368);
	setFlower(1, 1805, 384);
	setFlower(1, 1870, 368);
	//������ ����ų���� �θ�
	setKiller(0, 1664, 369 - 18);
	setKiller(0, 1984, 364 - 18);

	return S_OK;
}
void respawn::release()	 
{
}
void respawn::update()	 
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

	//if (_vCuba.size() == 0)
	//{
	//	_regenTime++;
	//	if (_regenTime % 600 == 0)
	//	{
	//
	//		_regenTime = 0;
	//	}
	//}
	//else
	//{
	//
	//}

	//---------------------------------------------------------------------
	//������ȯ
	//---------------------------------------------------------------------
	for (int i = 0; i < 3; i++)
	{
		//_viFlower[i]->getDirectionY();
	}
}
void respawn::render()	 
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

void respawn::setCuba(int move, int x, int y)
{
	enemy* _cuba;
	_cuba = new cuba;
	_cuba->init("��ٹ���", PointMake(x, y));			//300, 416
	_cuba->setMoveType(move);

	_vCuba.push_back(_cuba);
}
//�ȿ� �¿�ο����ϰŸ� 0 ���Ʒ��ο����ϰŸ� 1 ,x��ǥ,y��ǥ
void respawn::setTurtle(int move, int x, int y)
{
	enemy* _turtle;
	_turtle = new turtle;
	_turtle->init("�ź��̹���", PointMake(x, y));		//566, 384
	_turtle->setMoveType(move);

	_vTurtle.push_back(_turtle);
}
//�ȿ� �¿�ο����ϰŸ� 0 ���Ʒ��ο����ϰŸ� 1 ,x��ǥ,y��ǥ
void respawn::setFlower(int move, int x, int y)
{
	enemy* _flower;
	_flower = new flower;
	_flower->init("���β�", PointMake(x, y));			//367, 368
	_flower->setMoveType(move);

	_vFlower.push_back(_flower);
}
//�ȿ� �¿�ο����ϰŸ� 0 ���Ʒ��ο����ϰŸ� 1 ,x��ǥ,y��ǥ
void respawn::setKiller(int move, int x, int y)
{
	enemy* _killer;
	_killer = new killer;
	_killer->init("ų��", PointMake(x, y));
	_killer->setMoveType(move);

	_vKiller.push_back(_killer);
}

//-------------------------------------------------------------------
//�� ���� �Լ�
//-------------------------------------------------------------------
void respawn::removeCuba(int arrNum)
{
	SAFE_DELETE(_vCuba[arrNum]);
	_vCuba.erase(_vCuba.begin() + arrNum);
}
void respawn::removeTurtle(int arrNum)
{
	SAFE_DELETE(_vTurtle[arrNum]);
	_vTurtle.erase(_vTurtle.begin() + arrNum);
}
void respawn::removeFlower(int arrNum)
{
	SAFE_DELETE(_vFlower[arrNum]);
	_vFlower.erase(_vFlower.begin() + arrNum);
}
void respawn::removeKiller(int arrNum)
{
	SAFE_DELETE(_vKiller[arrNum]);
	_vKiller.erase(_vKiller.begin() + arrNum);
}
