#pragma once
#include "gameNode.h"
#include "tagBullet.h"
#include <vector> 


//발사할때 생성해서 발사하는 총알
class MF : public gameNode
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;



public:
	MF();
	~MF();

	HRESULT init(int missileMax, float range);
	void release();
	void update();
	void render();

	void fire(float x, float y, float angle);

	void move();

	void removeMissile(int arrNum);




	//접근자
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }




};
