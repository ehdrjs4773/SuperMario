#pragma once
#include "gameNode.h"

enum Phase		//����� ���� ���ʹ��� ���긦 �ٲٱ�����
{
	Phase1,	//�翷���θ� �����̴� ���͵� 
	Phase2	//���Ʒ��� �����̴� ���͵�
};

class enemy : public gameNode
{
private:
	image * _imageName;
	RECT _enemy;

	int _moveType;

	int _currentFrameX;
	int _currentFrameY;

	int _count;
	float _speed;
	bool _isDie;
	bool _directionX;
	bool _directionY;

public:
	enemy();
	~enemy();

				//�̹��� Ű��,	ó�� ������ x,y��ǥ
	HRESULT init(const char* imageName, POINT position);
	void release();
	void update();
	void render();


	void setMoveType(int move) { _moveType = move; }

	inline bool getDirectionX() { return _directionX; }
	inline bool getDirectionY() { return _directionY; }
	inline bool getIsDie()		{ return _isDie; }
	inline RECT getEnemyRect()  { return _enemy; }
};

