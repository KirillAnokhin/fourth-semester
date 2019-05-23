#include <cmath>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "game.h"
#include "view.h"
#include "tui.h"

Game::Game()
{
	View::get()->setOnTime(300, std::bind(&Game::move, this));
	rabbits.push_back(Coord(20, 20));
}

Snake::Snake()
{
	direction = UP;
	body.push_back(Coord(10, 11));
	body.push_back(Coord(11, 11));
	body.push_back(Coord(12, 11));
	body.push_back(Coord(13, 11));
	body.push_back(Coord(14, 11));
	body.push_back(Coord(15, 11));
}

Snake::Snake(const Snake &s):
	direction(s.direction),
	body(s.body)
{}

void Game::snake_p(SnakePainter pointer)
{
	bool f = true;
	for(const auto s: snakes)
	{
		for(const auto &c:s->body)
		{
			pointer(c, f ? s->direction : NO);
			f = false;
		}
	}
}

void Game::rabbit_p(RabbitPainter p) 
{
	for(const auto it: rabbits)
	{	
		p(it);
	}
}

void Game::add(Snake *p)
{
	snakes.push_back(p);
}

Snake& Snake::operator=(Snake const &s)
{
	snake_death = false;
	body = s.body;
	direction = s.direction;
}

void Game::move()
{
	for(auto s:snakes)
		if(!s->snake_death)
			s->move();
	View::get()->setOnTime(300, std::bind(&Game::move, this));
}

void Snake::move() 
{
	Coord a = body.front();
	Coord copy = body.front();
	Coord next = *(++body.begin());
	switch(direction){
		case UP:
			a.first--; 
			break;
		case DOWN:
			a.first++;
			break;
		case RIGHT:
			a.second++;
			break;
		case LEFT:
			a.second--;
			break;
	}
	
	switch(direction) {
		case UP:
			copy.first++;
			break;
		case DOWN:
			copy.first--;
			break;
		case RIGHT:
			copy.second--;
			break;
		case LEFT:
			copy.second++;
			break;
	}
	
	if(a == next)
	{
		//while(1) printf("hui");
		a = copy;
		direction = last_direction;
	}
	
	//body.push_front(a);
	if(find(View::get()->game->rabbits.begin(), 
			View::get()->game->rabbits.end(), a)
		       	!= View::get()->game->rabbits.end())
		View::get()->game->remove_rab(a);
	
	else if(find(++body.begin(), body.end(), a) != body.end() || a.first < 2 ||
		a.first > View::get() -> MyX() || a.second > View::get() -> MyY()  || a.second < 2)
	{
		snake_death = true;
		return;
	}
	
	else
		body.pop_back();
	body.push_front(a);
}

void Snake::set_direction(Dir d)
{
	last_direction = direction;
	direction = d;
}

int Coord::distance(const Coord &a)const
{
	return abs(abs(first - a.first) + abs(second - a.second));	
}

void Game::remove_rab(Coord c)
{
	rabbits.remove(c);
	new_rab();
}

void Game::new_rab()
{
	auto v = View::get();
	rabbits.push_back(Rabbit(rand()%(v -> MyX() - 3) + 1,
			       	rand()%(v -> MyY() - 3) + 1));
}

