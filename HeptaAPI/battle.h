#pragma once
#include "ship.h"

#define BATTLE_SPEED_MAX	5.0f
#define BATTLE_ANGLE_SPEED	2		// ��׸���
#define BATTLE_ACCEL		0.05f

class battle : public ship
{
public:
	battle();
	~battle();

	HRESULT init(const string imageName, float x, float y);
};

