#pragma once
#include "gameNode.h"

#define MARIO_IDLE_WIDTH	16
#define MARIO_IDLE_HEIGHT	32

#define JUMPPOWER	5.0f
#define GRAVITY		0.1f

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

public:
	mario();
	~mario();

	virtual HRESULT init(const string imageName, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void keyControl();
	virtual void move();
	virtual void draw();

	virtual void frameUpdate();
};

