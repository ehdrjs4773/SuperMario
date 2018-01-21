#pragma once
#include "gameNode.h"

#define JUMPPOWER	4.0f
#define GRAVITY		0.1f
#define LIMIT_X_LEFT	0
#define LIMIT_X_RIGHT	2815
#define MARIO_SPEED		2.0f

enum MARIO_STATE
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_JUMP,
	STATE_ATTACK,
	STATE_DIE,
	STATE_END
};

enum MARIO_KIND
{
	KIND_POMPOKO,
	KIND_FIRE,
	KIND_HAMMER,
	KIND_END
};

enum DIRECTION
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_END
};

static string _characterKey[KIND_END] =
{
	"pompoko",
	"fire",
	"hammer"
};

static string _stateKey[STATE_END] = 
{
	"_idle",
	"_move",
	"_jump",
	"_attack",
	"_die"
};

class mario : public gameNode
{
protected:
	string _imageName;
	float _x, _y;
	float _width, _height;
	float _speed;
	float _jumpPower;
	RECT _rc;
	MARIO_STATE _state;
	DIRECTION _dir;

	int _frameX;
	int _frameTime;

public:
	mario();
	~mario();

	virtual HRESULT init(const string imageName, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void move();
	virtual void attack();
	virtual void falling();
	virtual void draw();

	virtual void marioStateChange(MARIO_STATE state);

	virtual void frameUpdate();

	inline POINT getPos() { return PointMake(_x, _y); }
	inline RECT getRC() { return _rc; }
};

