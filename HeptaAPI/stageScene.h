#pragma once
#include "gameNode.h"

// ������ �ڽ� ����ü!!
struct ItemBox
{
	image itemImage; // ������ �ڽ� �̹���
	RECT rc;		 // ������ �ڽ� ��Ʈ
	bool Collsion;   // ������ �ڽ��� �浹 �ߴ���?
	float x, y;     // ������ �ڽ� ��ġ
};



class stageScene : public gameNode
{
private :

	image* _stageImage; // �������� �̹���
	ItemBox _itemBox; //������ �ڽ�



public:
	stageScene();
	~stageScene();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


};

