#include <iostream>
#include <fstream>

#include "view.h"
#include "tui.h"

View::~View()
{
	inst = nullptr;
}

View *View::inst = nullptr;

View *View::get()
{
	if(inst != nullptr)
	{
		return inst;
	}

	inst = new Tui;
	return inst;
}

void View::setModel(Game *g)
{
	game = g;
}


void View::setOnKey(KeyPressable *key)
{
	onkey_delegate = key;
}

/*
void View::setOnTimer(int timeout, bind($Game::ontimer, this))
{

}
*/
