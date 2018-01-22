#include "stdafx.h"
#include "fire.h"
#include "enemyManager.h"


fire::fire()
{
}


fire::~fire()
{
}


 HRESULT fire::init(const string imageName, float x, float y)
 {

	 mario::init(imageName, x, y);

	 _missile = new MF;
	 _missile->init( 30, 800);

	 return S_OK;
 }

 void fire::update()
{

	 mario::update();


	this->missileMove();

	this->collisionEnemyWithFireBullet();

}

void fire::render()
{
	this->draw();
	this->missileDraw();
}



void fire::attack()
{
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_state != STATE_DIE &&
			_state != STATE_ATTACK)
		{
			marioStateChange(STATE_ATTACK);
			missileFire();
			
		}
	}
}

void fire::draw()
{
	if (_isDebug)
		Rectangle(CAMERAMANAGER->getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	IMAGEMANAGER->findImage(_imageName + _stateKey[_state])->frameRender(CAMERAMANAGER->getMemDC(), _rc.left, _rc.top, _frameX, _dir);


}

void fire::missileFire()
{
	if (_dir == DIR_RIGHT)
	{
		float x = _x;
		float y = _y;
		_missile->fire(x, y, 0);
	}

	if (_dir == DIR_LEFT)
	{
		float x = _x;
		float y = _y;
		_missile->fire(x, y, PI);
	}

}

void fire::missileMove()
{
	_missile->update();
}

void fire::missileDraw()
{
	_missile->render();
}

void fire::collisionEnemyWithFireBullet()
{
	//cuba
	//bool isCollision = false;
	for (int i = 0; i < _missile->getVBullet().size(); ++i)
	{
		//isCollision = false;

		for (int j = 0; j < _em->getRespawn()->getVCuba().size(); ++j)
		{
			RECT temp;
			if (IntersectRect(&temp, &_missile->getVBullet()[i].rc, &_em->getRespawn()->getVCuba()[j]->getEnemyRect()))
			{
				_missile->removeMissile(i);
				_em->getRespawn()->removeCuba(j);
				//isCollision = true;
				break;
			}
		}

		//if (isCollision) break;
	}

	//TURTLE
	for (int i = 0; i < _missile->getVBullet().size(); ++i)
	{
		for (int j = 0; j < _em->getRespawn()->getVTurtle().size(); ++j)
		{
			RECT temp;
			if (IntersectRect(&temp, &_missile->getVBullet()[i].rc, &_em->getRespawn()->getVTurtle()[j]->getEnemyRect()))
			{
				_missile->removeMissile(i);
				_em->getRespawn()->removeTurtle(j);

				break;
			}
		}
	}

	//Flower
	for (int i = 0; i < _missile->getVBullet().size(); ++i)
	{
		for (int j = 0; j < _em->getRespawn()->getVFlower().size(); ++j)
		{
			RECT temp;
			if (IntersectRect(&temp, &_missile->getVBullet()[i].rc, &_em->getRespawn()->getVFlower()[j]->getEnemyRect()))
			{
				_missile->removeMissile(i);
				_em->getRespawn()->removeFlower(j);

				break;
			}
		}
	}
	//Killwer
	for (int i = 0; i < _missile->getVBullet().size(); ++i)
	{
		for (int j = 0; j < _em->getRespawn()->getVKiller().size(); ++j)
		{
			RECT temp;
			if (IntersectRect(&temp, &_missile->getVBullet()[i].rc, &_em->getRespawn()->getVKiller()[j]->getEnemyRect()))
			{
				_missile->removeMissile(i);
				_em->getRespawn()->removeKiller(j);

				break;
			}
		}
	}
}
