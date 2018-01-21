#pragma once
#include "mario.h"

class pompoko : public mario
{

	RECT _atRC;

public:

	HRESULT init(const string imageName, float x, float y);
	void update();
	void render();

	void attack();
	void draw();

	void missileFire();

	pompoko();
	~pompoko();
};

