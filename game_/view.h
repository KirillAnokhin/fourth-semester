#ifndef VIEW_H
#define VIEW_H

#include "game.h"
#include "keypressable.h"

using timepress = std::function<void()>;

class View
{
public:
	void virtual draw() = 0;
	void virtual run() = 0;
	int virtual MyX() = 0;
	int virtual MyY() = 0;
	virtual ~View();

	static View *inst;
	virtual void getWinSize() = 0;
	static View *get();

	void setOnKey(KeyPressable *);
	KeyPressable *onkey_delegate;

	std::pair<int, timepress> time_deligate;

	void setOnTime(int t, timepress func)
	{
		time_deligate.first = t;
		time_deligate.second = func;
	}

	Game *game;
	void setModel(Game *);

	void virtual snakePainter(Coord c, Dir d) = 0;
	void virtual rabbitPainter(Coord c) = 0;
};

#endif //VIEW_H

