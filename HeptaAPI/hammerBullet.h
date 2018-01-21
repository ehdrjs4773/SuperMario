#pragma once
#include "gameNode.h"
#include "tagBullet.h"


class hammerBullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	string _imageName;
	int _bulletMax;
	float _range;

public:
	hammerBullet(); 
	~hammerBullet();

	HRESULT init(const string imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void draw();
	//=========뿌릴 좌표 x,y | 앵글값 | 스피드 | 공중으로쐇니? (true , false) |
	void setBullet(float x, float y, float angle, float speed , bool isUpAttack);
	void move();
	void frameUpdate();

	//총알삭제
	void eraseBullet(int arrNum);

	//접근자
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

};

