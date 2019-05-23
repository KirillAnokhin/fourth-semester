#ifndef GAME_H
#define GAME_H

#include <list>
#include <utility>
#include <functional>

class Control;

enum Dir
{
	UP  ,
	DOWN,
	RIGHT,
	LEFT,
	NO,
};

struct Coord : public std::pair<int, int>
{
	using Base = std::pair<int, int>;
	int distance(const Coord &)const;
	using Base::Base;
};

class Snake
{
public:
	Snake();
	Snake(const Snake &);

	bool snake_death;
	std::list<Coord> body;
	Dir direction;
	Dir last_direction;
	Snake &operator=(Snake const &s);
	void move();
	void set_direction(Dir d);
};

using Rabbit = Coord;
using SnakePainter = std::function<void(Coord, Dir)>;
using RabbitPainter = std::function<void(Coord)>;

class Game
{
public:
	Game();

	std::list<Snake*> snakes;
	std::list<Rabbit> rabbits;

	void snake_p(SnakePainter p);
	void rabbit_p(RabbitPainter r);
	void add(Snake *p);
	void move();
	void remove_rab(Coord);
	void new_rab();
};

#endif //GAME_H

