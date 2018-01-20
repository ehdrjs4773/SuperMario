#include "stdafx.h"
#include "enemy.h"

enemy::enemy()
{
}


enemy::~enemy()
{
}

					//�̹��� Ű��,	ó�� ������ x,y��ǥ
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
			_currentFrameY = 1;	//�����̹���
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;

			_imageName->setFrameX(_currentFrameX);
			_currentFrameX++;

			_count = 0;
		}
		else
		{
			_currentFrameY = 0; //�������̹���
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;

			_imageName->setFrameX(_currentFrameX);
			_currentFrameX++;

			_count = 0;
		}
	}
	
	//--------------------------------------------------------------------------------------------
	//���ʹ� �����Դϴ�. �翷���� �����̴°�(���,�ź���,ų�� ��)�� ���Ʒ�(���β�)�� �����̴°��� �ֽ��ϴ�
	//--------------------------------------------------------------------------------------------
	switch (_moveType)
	{
	case Phase1://�翷
		if (_directionX)	//���ʹ���
		{
			_enemy.left -= _speed;
			_enemy.right -= _speed;
		}
		else			//�����ʹ���
		{
			_enemy.left += _speed;
			_enemy.right += _speed;
		}

		break;
	case Phase2://���Ʒ�
		if (_directionY)	//������
		{
			_enemy.top -= _speed;
			_enemy.bottom -= _speed;
		}
		else			//�Ʒ�����
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