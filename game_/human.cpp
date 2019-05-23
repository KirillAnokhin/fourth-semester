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

	switch (n) {
		case('d'):
			snake->Snake::set_direction(RIGHT);
			break;
		case('a'):
			snake->Snake::set_direction(LEFT);
           		break;
        	case('w'):
        		snake->Snake::set_direction(UP);
           	 	break;
        	case('s'):
            		snake->Snake::set_direction(DOWN);
            		break;
	}
}
