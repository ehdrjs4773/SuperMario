#pragma once
#include "ship.h"

#define CARRIER_SPEED_MAX	6.0f
#define CARRIER_ANGLE_SPEED	3		// 디그리안
#define CARRIER_ACCEL		0.07f

class carrier : public ship
{
public:
	carrier();
	~carrier();

	HRESULT init(const string imageName, float x, float y);
};

