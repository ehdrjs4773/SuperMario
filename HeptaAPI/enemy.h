#pragma once
#include "gameNode.h"
#include "mario.h"
#include "hammer.h"

enum Phase		//페이즈에 따라 에너미의 무브를 바꾸기위해
{
	Phase1,	//양옆으로만 움직이는 몬스터들 
	Phase2	//위아래로 움직이는 몬스터들
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

	int _probeY;			//탐사축(Y Axis)
	int _probeXRight;			//탐사축
	int _probeXLeft;			//탐사축

	int _count;
	float _speed;
	float _fallSpeed;
	bool _isDie;
	bool _directionXChange;
	bool _directionYChange;
	bool _isAir; //공중에있는지 판정

	RECT _directionXRc;
	RECT _directionYRc;

public:
	enemy();
	~enemy();

				//이미지 키값,	처음 생성될 x,y좌표
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

