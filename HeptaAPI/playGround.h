#pragma once
#include "gameNode.h"
#include "selectScene.h"
#include "stageScene.h"

class playGround : public gameNode
{
private:
	//============ �� �� �� �� �� Ʈ ==== by ����===//
	float _x, _y; //ȭ�� Ȯ�� ������!!
	BOOL _BackGround; // �޹�� ������ ���� �����

	//============ �� �� ġ �� �� ======= by ���� ==//


public:
	virtual HRESULT init(void);		//�ʱ�ȭ �Լ�
	virtual void release(void);		//�޸� ���� ����
	virtual void update(void);		//������Ʈ(����)
	virtual void render(void);		//�׷��ִ� �Լ�

	playGround();
	~playGround();
};

