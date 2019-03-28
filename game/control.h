#ifndef CONTROL_H_
#define CONTROL_H_
class Control
{
	Control();
	~Control();
};

class Keypressable
{
	public:
		virtual void onkey(int key) = 0;
};


class Human : public Control, public Keypressable
{
	public:
		Human();	
		~Human();	
};

#endif //CONTROL_H_
