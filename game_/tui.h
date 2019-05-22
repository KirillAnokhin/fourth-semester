#ifndef TUI_H
#define TUI_H

#include <termios.h>
#include "view.h"

class Tui:public View
{
private:
	int x;
	int y;
	struct termios old;
public:
	Tui();
	~Tui();
	
	int MyX() { return x;}
	int MyY() { return y;}
	void draw();
	void getWinSize();
	void drawLineY(int, int, int);
	void drawLineX(int, int, int);
   	void run();
   	void gotoxy(int, int);
    	void clearScreen();
    	void snakePainter(Coord, Dir);
	void rabbitPainter(Coord);
};

#endif //TUI_H

