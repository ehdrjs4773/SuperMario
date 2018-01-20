#pragma once
#include "gameNode.h"

enum Phase		//페이즈에 따라 에너미의 무브를 바꾸기위해
{
	Phase1,	//양옆으로만 움직이는 몬스터들 
	Phase2	//위아래로 움직이는 몬스터들
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

				//이미지 키값,	처음 생성될 x,y좌표
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

