#include "stdafx.h"
#include "button.h"


button::button()
{
}


button::~button()
{
}

HRESULT button::init(const char* imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint,
	CALLBACK_FUNCTION cbFunction)
{
	//콜백함수는 함수포인터로 전역화 시켜놨기때문에 형변환은 요로케
	_callbackFunction = std::move(std::bind(cbFunction));

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

HRESULT button::init(const char* imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint,
	CALLBACK_FUNCTION_INT cbFunction)
{
	//콜백함수는 함수포인터로 전역화 시켜놨기때문에 형변환은 요로케
	_callbackFunction_int = std::move(std::bind(cbFunction, std::placeholders::_1));

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_imageName = imageName;
	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	return S_OK;
}

void button::release(void)
{

}

void button::update(void) 
{
	if (PtInRect(&_rc, _ptMouse))
	{
		//클릭하면 버튼의 상태는 눌러짐
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION_DOWN;
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			//눌렀다 때면 버튼의 상태는 올라왔다
			_direction = BUTTONDIRECTION_UP;
			_callbackFunction(); //이때 콜백함수가 실행된다
		}
	}
	else _direction = BUTTONDIRECTION_NULL;
}

void button::update(int num)
{
	if (PtInRect(&_rc, _ptMouse))
	{
		//클릭하면 버튼의 상태는 눌러짐
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION_DOWN;
			_callbackFunction_int(num); //이때 콜백함수가 실행된다
		}
	}
}

void button::render(void) 
{
	switch (_direction)
	{
		//버튼의 초기화 및 올라와있는 상태의 이미지는 같다
		case BUTTONDIRECTION_NULL:	case BUTTONDIRECTION_UP:
			_image->frameRender(getMemDC(), _rc.left, _rc.top,
				_btnUpFramePoint.x, _btnUpFramePoint.y);
		break;
		//버튼 눌러졌을때 이미지
		case BUTTONDIRECTION_DOWN:
			_image->frameRender(getMemDC(), _rc.left, _rc.top,
				_btnDownFramePoint.x, _btnDownFramePoint.y);
		break;

	}
}
