#include "stdafx.h"
#include "mutalisk.h"



mutalisk::mutalisk()
{
}


mutalisk::~mutalisk()
{
}

HRESULT mutalisk::init(const string imageName, float x, float y)
{
	ship::init(imageName, x, y);

	_angleSpeed = MUTALISK_ANGLE_SPEED;
	_maxSpeed = MUTALISK_SPEED_MAX;
	_accel = MUTALISK_ACCEL;

	return S_OK;
}
