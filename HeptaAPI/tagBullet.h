#pragma once
#include "stdafx.h"

struct tagBullet
{
	image* imageName;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float radius;					//총알의 반지름
	float angle;
	float gravity;
	bool isUpAttack;					//하늘을 향해 쐇니?
	bool isFire;					//발사땡겼늬?
	int currentFrameX, currentFrameY;	//현제 프레임 번호
	int count;							//카운트
	float jumpPower;
};