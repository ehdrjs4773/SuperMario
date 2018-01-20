#pragma once
#include "mario.h"
#include "bullet.h"

class hammer : public mario
{
private:
	hammerBullet* _bullet;
	
	//������Ű�� �������ִ��� ����
	bool _isUpKey;
public:
	hammer();
	~hammer();

	virtual HRESULT init(const string imageName, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void attack();

	virtual void keyControl();

	//�ظӸ����� �ҷ� ������
	hammerBullet* getHammerBullet() { return _bullet; }

};

