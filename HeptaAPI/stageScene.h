#pragma once
#include "gameNode.h"

// 아이템 박스 구조체!!
struct ItemBox
{
	image itemImage; // 아이템 박스 이미지
	RECT rc;		 // 아이템 박스 렉트
	bool Collsion;   // 아이템 박스를 충돌 했는지?
	float x, y;     // 아이템 박스 위치
};



class stageScene : public gameNode
{
private :

	image* _stageImage; // 스테이지 이미지
	ItemBox _itemBox; //아이템 박스



public:
	stageScene();
	~stageScene();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);


};

