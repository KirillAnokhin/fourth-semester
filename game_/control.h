#ifndef CONTROL_H
#define CONTROL_H

#include "game.h"

class Control
{
public:
	explicit Control(Snake * s){ snake = s; };
	Snake *snake;
};

class AI:public Control
{
public:
	void onMove();
};

#endif //CONTROL_H
