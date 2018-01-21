#pragma once
#include "gameNode.h"

enum ITEM_KIND
{
	ITME_COIN,
	ITEM_STAR,
	ITEM_END
};

struct tagItem
{
	image* imageName;
	ITEM_KIND item_kind;
	RECT rc;
	float x, y;
	bool isMove;
	int currentFrameX, currentFrameY;
	int count;
};


class item : public gameNode
{
private:
	vector<tagItem> _vItem;
	vector<tagItem>::iterator _viItem;

private:
	string _imageName;
	

public:
	item();
	~item();

	virtual HRESULT init(const string imageName);
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void draw();
	virtual void setItem(float x , float y , ITEM_KIND itme_kind);
	virtual void itemMove();
	virtual void frameUpdate();
	virtual void eraseItem(int arrNum);
};

