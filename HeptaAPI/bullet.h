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
	bool isUpAttack;					//�ϴ��� ���� �i��?
	int currentFrameX, currentFrameY;	//���� ������ ��ȣ
	int count;							//ī��Ʈ
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
	//�Ѹ� ��ǥ x,y | �ޱ۰� | ���ǵ� | ���ߺ���i��? (true , false) |
	void setBullet(float x, float y, float angle, float speed , bool isUpAttack);
	void move();
	void frameUpdate();

	//������
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

};

