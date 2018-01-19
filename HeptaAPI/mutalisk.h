#pragma once
#include "ship.h"

#define MUTALISK_SPEED_MAX		8.0f
#define MUTALISK_ANGLE_SPEED	5		// 디그리안
#define MUTALISK_ACCEL			0.1f

class mutalisk : public ship
{
public:
	mutalisk();
	~mutalisk();

	HRESULT init(const string imageName, float x, float y);
};

