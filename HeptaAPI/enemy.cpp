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
	_count = 0;
	_isDie = false;
	_directionX = false;
	_directionY = false;

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
		if (_directionX)
		{
			_currentFrameY = 1;	//왼쪽이미지
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;

			_imageName->setFrameX(_currentFrameX);
			_currentFrameX++;

			_count = 0;
		}
		else
		{
			_currentFrameY = 0; //오른쪽이미지
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;

			_imageName->setFrameX(_currentFrameX);
			_currentFrameX++;

			_count = 0;
		}
	}
	
	//--------------------------------------------------------------------------------------------
	//에너미 무브입니다. 양옆으로 움직이는것(쿠바,거북이,킬러 등)과 위아래(식인꽃)로 움직이는것이 있습니다
	//--------------------------------------------------------------------------------------------
	switch (_moveType)
	{
	case Phase1://양옆
		if (_directionX)	//왼쪽무브
		{
			_enemy.left -= _speed;
			_enemy.right -= _speed;
		}
		else			//오른쪽무브
		{
			_enemy.left += _speed;
			_enemy.right += _speed;
		}

		break;
	case Phase2://위아래
		if (_directionY)	//위무브
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
void enemy::render()											   
{
	_imageName->frameRender(getMemDC(), _enemy.left, _enemy.top, _currentFrameX, _currentFrameY);
}