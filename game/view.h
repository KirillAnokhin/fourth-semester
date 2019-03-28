#ifndef VIEW_H_
#define VIEW_H_
#include "control.h"

class View 
{
	public:
	//	Keypressable *onkey_delegate;
		View();
		virtual ~View();
		virtual void draw() = 0;
		virtual void run() = 0;
	//	void setonkey(Keypressable *k);
};

#endif //VIEW_H_
