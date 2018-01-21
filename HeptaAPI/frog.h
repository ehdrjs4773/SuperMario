#pragma once
#include "mario.h"

class frog : public mario
{
private:

public:
	frog();
	~frog();

	HRESULT init(const string imageName, float x, float y);
	void release();
	void update();
	void render();

	void draw();

};

