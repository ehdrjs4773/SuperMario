#pragma once
#include "gameNode.h"
#include "mario.h"
#include "hammer.h"

enum Phase		//����� ���� ���ʹ��� ���긦 �ٲٱ�����
{
	Phase1,	//�翷���θ� �����̴� ���͵� 
	Phase2	//���Ʒ��� �����̴� ���͵�
};

class enemy : public gameNode
{
private:
	hammer * _player;

	image * _imageName;
	RECT _enemy;

	int _moveType;

	int _currentFrameX;
	int _currentFrameY;

	int _probeY;			//Ž����(Y Axis)
	int _probeXRight;			//Ž����
	int _probeXLeft;			//Ž����

	int _count;
	float _speed;
	float _fallSpeed;
	bool _isDie;
	bool _directionXChange;
	bool _directionYChange;
	bool _isAir; //���߿��ִ��� ����

	RECT _directionXRc;
	RECT _directionYRc;

public:
	enemy();
	~enemy();

				//�̹��� Ű��,	ó�� ������ x,y��ǥ
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();


	void setMoveType(int move) { _moveType = move; }

	void enemyMove();

	inline bool getDirectionX() { return _directionXChange; }
	inline bool getDirectionY() { return _directionYChange; }
	inline bool getIsDie()		{ return _isDie; }
	inline RECT getEnemyRect()  { return _enemy; }
};

