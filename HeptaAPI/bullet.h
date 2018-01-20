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
	//=========�Ѹ� ��ǥ x,y | �ޱ۰� | ���ǵ� | �������Μi��? (true , false) |
	void setBullet(float x, float y, float angle, float speed , bool isUpAttack);
	void move();
	void frameUpdate();

	//�Ѿ˻���
	void eraseBullet(int arrNum);

	//������
	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet() { return _viBullet; }

};

