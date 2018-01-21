#include "stdafx.h"
#include "item.h"



item::item()
{
}


item::~item()
{
}

HRESULT item::init()
{


	return S_OK;
}
void item::release()
{

}
void item::update()	
{
	itemMove();
	frameUpdate();
}
void item::render()	
{
	draw();
}

void item::draw()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if (_isDebug) Rectangle(CAMERAMANAGER->getMemDC(), _viItem->rc.left, _viItem->rc.top, _viItem->rc.right, _viItem->rc.bottom);

		_viItem->imageName->frameRender(CAMERAMANAGER->getMemDC(), _viItem->x, _viItem->y,
			_viItem->currentFrameX, _viItem->currentFrameY);
	}
}

void item::setItem(float x, float y, ITEM_KIND itme_kind, const string imageName)
{
	tagItem item;
	ZeroMemory(&item, sizeof(item));
	item.item_kind = (ITEM_KIND)itme_kind;
	item.imageName = IMAGEMANAGER->findImage(imageName);
	item.x = x;
	item.y = y;
	item.currentFrameX = item.currentFrameY = item.count = 0;
	item.isMove = true;
	item.rc = RectMake(item.x, item.y, item.imageName->getFrameWidth(), item.imageName->getFrameHeight());

	_vItem.push_back(item);
}

void item::itemMove()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		switch (_viItem->item_kind)
		{
		case ITME_COIN:
			if (_viItem->isMove)
			{
				_viItem->y -= 4.0f;
			}
			else
			{

			}

			_viItem->rc = RectMake(_viItem->x, _viItem->y, _viItem->imageName->getFrameWidth(), _viItem->imageName->getFrameHeight());
			break;
		case ITEM_STAR:
			if (_viItem->isMove)
			{
				_viItem->y -= 4.0f;
			}
			else
			{

			}
			_viItem->rc = RectMake(_viItem->x, _viItem->y, _viItem->imageName->getFrameWidth(), _viItem->imageName->getFrameHeight());
			break;
		default:
			break;
		}
	}
}

void item::frameUpdate()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		_viItem->count++;
		if (_viItem->count > 4)
		{
			if (_viItem->currentFrameX >= _viItem->imageName->getMaxFrameX()) _viItem->currentFrameX = 0;
			_viItem->currentFrameX++;
			_viItem->count = 0;
		}
	}
}

void item::eraseItem(int arrNum)
{
	_vItem.erase(_vItem.begin() + arrNum);
}
