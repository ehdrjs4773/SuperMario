#include "stdafx.h"
#include "battle.h"



battle::battle()
{
}


battle::~battle()
{
}

HRESULT battle::init(const string imageName, float x, float y)
{
	ship::init(imageName, x, y);

	_angleSpeed = BATTLE_ANGLE_SPEED;
	_maxSpeed = BATTLE_SPEED_MAX;
	_accel = BATTLE_ACCEL;

	return S_OK;
}
