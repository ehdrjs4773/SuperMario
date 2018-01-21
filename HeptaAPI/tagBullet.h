#pragma once
#include "stdafx.h"

struct tagBullet
{
	image* imageName;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float radius;					//�Ѿ��� ������
	float angle;
	float gravity;
	bool isUpAttack;					//�ϴ��� ���� �i��?
	bool isFire;					//�߻綯���?
	int currentFrameX, currentFrameY;	//���� ������ ��ȣ
	int count;							//ī��Ʈ
	float jumpPower;
};