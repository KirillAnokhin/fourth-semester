#include <termios.h>
#include <iostream>
#include <stdio.h>
#include <sys/ioctl.h>
#include "tui.h"
#include "control.h"

using namespace std;

Tui::~Tui() {}; 

Tui::Tui() 
{
	struct winsize ws;
	ioctl(1, TIOCGWINSZ, &ws);
	row = ws.ws_row;
	col = ws.ws_col;	
}

void Tui::clear()
{
	printf("\e[H\e[J");
}

void Tui::draw()
{
	struct winsize ws;
	ioctl(1, TIOCGWINSZ, &ws);	
	printf("cols = %d rows = %d\n", ws.ws_col, ws.ws_row);

	int i,j, rows = ws.ws_row, cols = ws.ws_col;
	char ch = '#';

	for(i = 0; i < rows; i++) 
	{
		for (j = 0; j < cols; j++) 
		{
			if(i == 0 || i == rows - 1) cout << ch;
			else if(j == 0 || j == cols - 1) cout << ch;
			else cout << " "; 
		}
		cout << endl;
	}

	printf("\e[H");
}

void Tui::run()
{
	//class Keypressable onkey_delegate;
	while(1) {

		int key = getchar();
		if(key == 'q') {
			//выйти
			break;
		} else {
			//onkey_delegate.onkey(key);
		}
	}
}

/*
   gotoxy(int x, int y)
   {

   }
   */


