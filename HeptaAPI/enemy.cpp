#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}
enemy::~enemy()
{
}
					//이미지 키값,	처음 생성될 x,y좌표
HRESULT enemy::init(const char* imageName, POINT position)  
{
	_currentFrameX = _currentFrameY = 0;

	_imageName = IMAGEMANAGER->findImage(imageName);

	_enemy = RectMakeCenter(position.x, position.y, _imageName->getFrameWidth(), _imageName->getFrameHeight());
	_speed = 1.f;
	_fallSpeed = 1.f;
	_count = 0;
	_isDie = false;
	_isAir = true;	//공중에있다면
	_directionXChange = false;
	_directionYChange = false;

	_player = new hammer;
	_player->init(_characterKey[KIND_HAMMER], 50, WINSIZEY / 2);

	_directionXRc = RectMake(_enemy.left - 40, _enemy.top - 40, 100, 80);
	_directionYRc = RectMake(_enemy.left, _enemy.top - 35, 18, 35);

	return S_OK;
}
void enemy::release()											   
{

}
void enemy::update()											   
{
	_count++;
	if (_count % 5 == 0)
	{
		if (_directionXChange)	//왼쪽으로간다면
		{
			_currentFrameY = 1;	//왼쪽이미지
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;

			_imageName->setFrameX(_currentFrameX);
			_currentFrameX++;

			_count = 0;

		}
		else                   //오른쪽으로간다면
		{
			_currentFrameY = 0; //오른쪽이미지
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;

			_imageName->setFrameX(_currentFrameX);
			_currentFrameX++;

			_count = 0;
		}
	}
	
	//--------------------------------------------------------------------------------------------
	//에너미 무브입니다.픽셀충돌 추가
	//--------------------------------------------------------------------------------------------
	_probeY = _enemy.bottom;
	_probeXRight = _enemy.right;
	_probeXLeft = _enemy.left;

	if (_directionXRc.left >= _enemy.left)
	{
		_directionXChange = false;
	}
	if (_directionXRc.right <= _enemy.right)
	{
		_directionXChange = true;
	}
	

	enemyMove();
}
void enemy::render()											   
{
	_imageName->frameRender(CAMERAMANAGER->getMemDC(), _enemy.left, _enemy.top, _currentFrameX, _currentFrameY);
}

void enemy::enemyMove()
{
	switch (_moveType)
	{
	case Phase1://양옆
		if (_directionXChange)	//왼쪽무브
		{
			//if (_isAir == true)
			//{
			//	_enemy.top += _fallSpeed;
			//	_enemy.bottom += _fallSpeed;
			//}
			//else
			//{
			//	_fallSpeed = 0.f;
			//}
			//
			//for (int i = _probeY - 3; i < _probeY + 5; ++i)
			//{
			//	for (int j = _probeXRight; j < _probeXRight; ++j)	
			//	{																			
			//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("뒷배경")->getMemDC(), j, i);
			//
			//		int r = GetRValue(color);
			//		int g = GetGValue(color);
			//		int b = GetBValue(color);
			//
			//		if ((r == 0 && g == 255 && b == 255))	//정해진 색에 닿는다면
			//		{
			//			_enemy.top = i - (_enemy.bottom - _enemy.top);	//
			//			_isAir = false;
			//			break;
			//		}
			//	}
			//}

			_enemy.left -= _speed;
			_enemy.right -= _speed;
		}
		else			//오른쪽무브
		{
			//if (_isAir == true)
			//{
			//	_enemy.top += _fallSpeed;
			//	_enemy.bottom += _fallSpeed;
			//}
			//else
			//{
			//	_fallSpeed = 0.f;
			//}
			//
			//for (int i = _probeY - 3; i < _probeY + 5; ++i)
			//{
			//	for (int j = _probeXRight; j < _probeXRight; ++j)
			//	{
			//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("뒷배경")->getMemDC(), j, i);
			//
			//		int r = GetRValue(color);
			//		int g = GetGValue(color);
			//		int b = GetBValue(color);
			//
			//		if ((r == 0 && g == 255 && b == 255))	//정해진 색에 닿는다면
			//		{
			//			_enemy.top = i - (_enemy.bottom - _enemy.top);	//
			//			_isAir = false;
			//			break;
			//		}
			//	}
			//}
			_enemy.left += _speed;
			_enemy.right += _speed;
		}

		break;

	case Phase2://위아래
		if (_directionYChange)	//위무브
		{
			_enemy.top -= _speed;
			_enemy.bottom -= _speed;
		}
		else			//아래무브
		{
			_enemy.top += _speed;
			_enemy.bottom += _speed;
		}
		break;
	}
}