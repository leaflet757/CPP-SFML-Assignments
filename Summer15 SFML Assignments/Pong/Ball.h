#pragma once
#include "Actor2D.h"


class Ball :
	public OpenSFMLEngine::Actor2D
{
public:
	Ball();
	~Ball();

	void update();
};

