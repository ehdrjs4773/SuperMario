#pragma once
#include "mario.h"

class pompoko : public mario
{

	RECT _atRC;

public:

	void update();
	void render();

	void attack();
	void draw();

	void missileFire();

	pompoko();
	~pompoko();
};

