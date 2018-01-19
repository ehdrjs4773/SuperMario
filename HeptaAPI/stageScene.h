#pragma once
#include "gameNode.h"
#include "mario.h"

// 아이템 박스 구조체!!
struct ItemBox
{
	image* itemImage; // 아이템 박스 이미지
	RECT rc;		 // 아이템 박스 렉트
	bool Collsion;   // 아이템 박스를 충돌 했는지?
	int itemNum;    // 아이템 치면 뭐 나올지?
	
};


class stageScene : public gameNode
{
private :
	int _currentFrameX;
	int _count;
	ItemBox _itemBox[6]; //아이템 박스

	mario* _player;


public:
	stageScene();
	~stageScene();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


};

