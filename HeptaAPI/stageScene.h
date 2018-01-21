#pragma once
#include "gameNode.h"
#include "mario.h"
#include "hammer.h"
#include "fire.h"
#include "pompoko.h"
#include "item.h"

// ������ �ڽ� ����ü!!
struct ItemBox
{
	image* itemImage; // ������ �ڽ� �̹���
	RECT rc;		 // ������ �ڽ� ��Ʈ
	bool Collsion;   // ������ �ڽ��� �浹 �ߴ���?
	int itemNum;    // ������ ġ�� �� ������?
	
};

class stageScene : public gameNode
{
private :
	int _currentFrameX;
	int _count;
	ItemBox _itemBox[8]; //������ �ڽ�


	RECT _finishRect; // ������ ��Ʈ
	item* _item;
	mario* _player;


public:
	stageScene();
	~stageScene();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


};

