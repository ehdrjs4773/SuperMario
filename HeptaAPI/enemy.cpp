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
	_fallSpeed = 1.f;
	_count = 0;
	_isDie = false;
	_isAir = true;	//���߿��ִٸ�
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
		if (_directionXChange)	//�������ΰ��ٸ�
		{
			_currentFrameY = 1;	//�����̹���
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;

			_imageName->setFrameX(_currentFrameX);
			_currentFrameX++;

			_count = 0;

		}
		else                   //���������ΰ��ٸ�
		{
			_currentFrameY = 0; //�������̹���
			if (_currentFrameX >= _imageName->getMaxFrameX()) _currentFrameX = 0;

			_imageName->setFrameX(_currentFrameX);
			_currentFrameX++;

			_count = 0;
		}
	}
	
	//--------------------------------------------------------------------------------------------
	//���ʹ� �����Դϴ�.�ȼ��浹 �߰�
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
	case Phase1://�翷
		if (_directionXChange)	//���ʹ���
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
			//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("�޹��")->getMemDC(), j, i);
			//
			//		int r = GetRValue(color);
			//		int g = GetGValue(color);
			//		int b = GetBValue(color);
			//
			//		if ((r == 0 && g == 255 && b == 255))	//������ ���� ��´ٸ�
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
		else			//�����ʹ���
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
			//		COLORREF color = GetPixel(IMAGEMANAGER->findImage("�޹��")->getMemDC(), j, i);
			//
			//		int r = GetRValue(color);
			//		int g = GetGValue(color);
			//		int b = GetBValue(color);
			//
			//		if ((r == 0 && g == 255 && b == 255))	//������ ���� ��´ٸ�
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

	case Phase2://���Ʒ�
		if (_directionYChange)	//������
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