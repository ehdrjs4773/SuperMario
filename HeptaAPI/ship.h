#pragma once
#include "gameNode.h"

enum SHIP_STATE
{
	STATE_IDLE,
	STATE_MOVE,
	STATE_END
};

enum SHIP_KIND
{
	KIND_BATTLE,
	KIND_CARRIER,
	KIND_MUTALISK,
	KIND_END
};

static string _characterKey[KIND_END] =
{
	"battle",
	"carrier",
	"mutalisk"
};

class ship : public gameNode
{
protected:
	string _imageName;
	float _x, _y;
	float _width, _height;
	float _speed;
	float _angle;
	float _angleSpeed;
	float _maxSpeed;
	float _accel;
	RECT _rc;
	SHIP_STATE _state;

public:
	ship();
	~ship();

	virtual HRESULT init(const string imageName, float x, float y);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void keyControl();
	virtual void move();
	virtual void draw();

	virtual void frameUpdate();
};

