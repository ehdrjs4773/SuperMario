#include "stdafx.h"
#include "carrier.h"



carrier::carrier()
{
}


carrier::~carrier()
{
}

HRESULT carrier::init(const string imageName, float x, float y)
{
	ship::init(imageName, x, y);

	_angleSpeed = CARRIER_ANGLE_SPEED;
	_maxSpeed = CARRIER_SPEED_MAX;
	_accel = CARRIER_ACCEL;

	return S_OK;
}