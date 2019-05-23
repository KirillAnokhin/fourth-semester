#include <iostream>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <functional>
#include <poll.h>
#include <unistd.h>
#include <sys/time.h>

using namespace std::placeholders;

#include "tui.h"

void Tui::drawLineX(int start, int length, int y)
{
	for(int i = start; i < start + length; i++)
	{
		gotoxy(i, y);
		printf("#");
	}
}

void Tui::drawLineY(int start, int length, int x)
{
	for(int i = start; i < start + length; i++)
	{
		gotoxy(x, i);
		printf("#");
	}
}

void Tui::draw()
{
	clearScreen();
	getWinSize();
	
	drawLineX(0, x, 0);
	drawLineY(0, y, 0);
	drawLineX(0, x, y);
	drawLineY(0, y, x);

	game->snake_p(std::bind(&View::snakePainter, this, _1, _2));
	game->rabbit_p(std::bind(&View::rabbitPainter, this, _1));

	fflush(stdout);
}

void Tui::getWinSize()
{
	struct winsize ws;
	ioctl(1, TIOCGWINSZ, &ws);
	x = ws.ws_row;
	y = ws.ws_col;
}

void onwinch(int x)
{
	View *v = View::get();
	v->draw();
}

Tui::Tui():
   	 x(0),
   	 y(0)
{
   	 setbuf(stdout, NULL);

   	 struct sigaction sa = {0};
   	 sa.sa_handler = onwinch;
   	 sa.sa_flags = SA_RESTART;
   	 sigaction(SIGWINCH, &sa, 0);

   	 struct termios a;
   	 tcgetattr(1, &a);
   	 old = a;
   	 cfmakeraw(&a);
   	 tcsetattr(1, TCSANOW, &a);
}


void Tui::clearScreen()
{
       	printf("\e[H\e[J");
}

Tui::~Tui()
{
   	tcsetattr(0, TCSAFLUSH, &old);
  	clearScreen();
   	printf("GAME OVER\n");
}

void Tui::run()
{
  	struct pollfd fds = {1, POLLIN, 0};
    	//fds.fd = 0;
    	//fds.events = POLLIN;
	struct timeval t1, t2;	

   	draw();

   	while(1){
	
		char c;
		gettimeofday(&t1, NULL);
		int n = poll(&fds, 1, time_deligate.first);
		if(n == 1) {
        		read(1, &c, 1);
        		if(onkey_delegate != nullptr)
			{
        			onkey_delegate->onkey(c);
			}
			gettimeofday(&t2, NULL);
			time_deligate.first -= (t2.tv_sec-t1.tv_sec)*1000+(t2.tv_usec-t1.tv_usec)/1000;
			if(time_deligate.first < 0)
				time_deligate.first = 0;
		}
		else {
		        time_deligate.second();
			//game -> move();
			draw();
		}	
       
		gotoxy(x/2, y/2);
     
		if(c == 'q')
			break;
	}
}

void Tui::gotoxy(int x, int y)
{
	printf("\e[%d;%dH", x, y);
}

void Tui::snakePainter(Coord c, Dir d)
{
	gotoxy(c.first, c.second);
	putchar("^v><#"[d]);
}

void Tui::rabbitPainter(Coord c)
{
	gotoxy(c.first, c.second);
	putchar('@');
}
