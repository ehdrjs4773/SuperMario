#pragma once
#include "gameNode.h"
#include "mario.h"
#include "button.h"

#define SELECT_WIDTH	168
#define SELECT_HEIGHT	68

class selectScene : public gameNode
{
private:
	button* _selectButton;
	button* _selectBackButton[KIND_END];
	static int _currentClickedButton;
	static int _selectButtonX, _selectButtonY;
	static bool _isClicked;

	static int _frameTime;

public:
	selectScene();
	~selectScene();

	HRESULT init();
	void release();
	void update();
	void render();

	static void selectButtonClick();
	static void selectBackButtonClick(int num);
};

