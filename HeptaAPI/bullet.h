#pragma once
#include "gameNode.h"

struct tagBullet
{
	image* imageName;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	bool isUpAttack;					//하늘을 향해 쐇니?
	int currentFrameX, currentFrameY;	//현제 프레임 번호
	int count;							//카운트
};

class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	string _imageName;
	int _bulletMax;
	float _range;

public:
	bullet();
	~bullet();

	HRESULT init(const string imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void draw();
	//뿌릴 좌표 x,y | 앵글값 | 스피드 | 공중보고쐇니? (true , false) |
	void setBullet(float x, float y, float angle, float speed , bool isUpAttack);
	void move();
	void frameUpdate();

	//접근자
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

};

