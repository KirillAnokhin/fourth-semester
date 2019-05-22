#include <iostream>
#include <fstream>

#include "game.h"
#include "human.h"
#include "view.h"
#include "tui.h"

Human::Human(Snake * s, Game *g):Control(s), game(g)
{
	View::get()->setOnKey(this);
}

Human::~Human()
{
}

void Human::onkey(int n)
{
	//printf("key pressed = %d ", n);
	static std::fstream f("out",std::ios::out);
	f << 1111;
	f.close();
	switch (n) {
		case('d'):
			snake->direction = RIGHT;
			break;
		case('a'):
			snake->direction = LEFT;
           		break;
        	case('w'):
        		snake->direction = UP;
           	 	break;
        	case('s'):
            		snake->direction = DOWN;
            		break;
	}
	//game->move();
	//View::get()->draw();
}
