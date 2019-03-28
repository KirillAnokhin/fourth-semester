#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "view.h"
#include "tui.h"

void sigdr(int x)
{
	View *v = Tui::get();
	v -> draw();
}

int main()
{
	signal(SIGWINCH, sigdr);

	View *v = Tui::get();
	v->draw();
	v->run();

	return 0;
}
