#pragma once
#include "gameNode.h"

#define JUMPPOWER	3.5f
#define GRAVITY		0.1f
#define LIMIT_X_LEFT	0
#define LIMIT_X_RIGHT	2815
#define MARIO_SPEED		2.0f

#define POMPOKO_IDLE_WIDTH			21
#define POMPOKO_IDLE_HEIGHT			28
#define POMPOKO_MOVE_WIDTH			23
#define POMPOKO_MOVE_HEIGHT			28
#define POMPOKO_JUMP_WIDTH			23
#define POMPOKO_JUMP_HEIGHT			27
#define POMPOKO_ATTACK_WIDTH		24
#define POMPOKO_ATTACK_HEIGHT		28

#define FIRE_IDLE_WIDTH				16
#define FIRE_IDLE_HEIGHT			28
#define FIRE_MOVE_WIDTH				16
#define FIRE_MOVE_HEIGHT			28
#define FIRE_JUMP_WIDTH				16
#define FIRE_JUMP_HEIGHT			26
#define FIRE_ATTACK_WIDTH			16
#define FIRE_ATTACK_HEIGHT			28

#define HAMMER_IDLE_WIDTH			16
#define HAMMER_IDLE_HEIGHT			28
#define HAMMER_MOVE_WIDTH			16
#define HAMMER_MOVE_HEIGHT			28
#define HAMMER_JUMP_WIDTH			16
#define HAMMER_JUMP_HEIGHT			27
#define HAMMER_ATTACK_WIDTH			16
#define HAMMER_ATTACK_HEIGHT		28

#define FROG_IDLE_WIDTH				20
#define FROG_IDLE_HEIGHT			24
#define FROG_MOVE_WIDTH				20
#define FROG_MOVE_HEIGHT			29
#define FROG_JUMP_WIDTH				19
#define FROG_JUMP_HEIGHT			29

enum MARIO_STATE
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_JUMP,
	STATE_ATTACK,
	STATE_DIE,
	STATE_CLEAR,
	STATE_END
};

enum MARIO_KIND
{
	KIND_POMPOKO,
	KIND_FIRE,
	KIND_HAMMER,
	KIND_FROG,
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
	"hammer",
	"frog"
};

static string _stateKey[STATE_END] = 
{
	"_idle",
	"_move",
	"_jump",
	"_attack",
	"_jump",
	"_move"
};

// 전! 방! 선! 언!
class enemyManager;

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

	enemyManager* _em;

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

	virtual void collisionControl();
	virtual void collisionWithEnemy();

	inline POINT getPos() { return PointMake(_x, _y); }
	inline RECT getRC() { return _rc; }
	inline MARIO_STATE getState() { return _state; }
	inline void setJumpPower(float jp) { _jumpPower = jp; }

	inline void setEMMemoryAddressLink(enemyManager* em) { _em = em; }
};

