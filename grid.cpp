#include <string>
#include <iostream>
#include "graph.h"

bool door_coordinate::operator == (const door_coordinate& source) const
{
	if(
		x1 == source.x1 &&
		x2 == source.x2 &&
		y1 == source.y1 &&
		y2 == source.y2
		)
	{
		return false;
	}

	return true;
}

door_coordinate::door_coordinate()
{
	container_width = 0;
	container_height = 0;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
}

door_coordinate::door_coordinate(room * parent)
{
	container_width = parent->get_width();
	container_height = parent->get_height();
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
}

int door_coordinate::get_x1()
{
	return x1;
}

void door_coordinate::set_x1(int n)
{
	x1 = n;
}

int door_coordinate::get_x2()
{
	return x2;
}

void door_coordinate::set_x2(int n)
{
	x2 = n;
}

int door_coordinate::get_y1()
{
	return y1;
}

void door_coordinate::set_y1(int n)
{
	y1 = n;
}

int door_coordinate::get_y2()
{
	return y2;
}

void door_coordinate::set_y2(int n)
{
	y2 = n;
}

std::string door_coordinate::get_door_side()
{
	if(door_side == north)
	{
		return "north";
	}else if (door_side == south)
	{
		return "south";
	}else if(door_side == east)
	{
		return "east";
	}else if(door_side == west)
	{
		return "west";
	}
	else
		return NULL;
}

void door_coordinate::set_door_side(std::string n)
{
	if(n == "north")
	{
		door_side = north;
	}else if(n == "south")
	{
		door_side = south;
	}else if(n == "east")
	{
		door_side = east;
	}else if(n == "west")
	{
		door_side = west;
	}
}

void door_coordinate::reset()
{
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
}

bool door_coordinate::is_north_wall()
{
	if(y1 == container_height && y2 == container_height)
	{
		return true;
	}

	return false;
}

bool door_coordinate::is_south_wall()
{
	if(y1 == 0 && y2 == 0)
	{
		return true;
	}

	return false;
}

bool door_coordinate::is_west_wall()
{
	if(x1 == 0 && x2 == 0)
	{
		return true;
	}

	return false;
}

bool door_coordinate::is_east_wall()
{
	if(x1 == container_width && x2 == container_width)
	{
		return true;
	}

	return false;
}

bool door_coordinate::same_as(door_coordinate * source)
{
	if(
		x1 == source->x1 &&
		x2 == source->x2 &&
		y1 == source->y1 &&
		y2 == source->y2
		)
	{
		return true;
	}

	return false;
}


void door_coordinate::build_north_wall()
{
	x1 = container_width - (rand()%container_width);

	if(x1 > 0)
	{
		x2 = x1-1;
	}
	else
	{
		x2 = 1;
	}

	y1 = 0;
	y2 = 0;
}

void door_coordinate::build_south_wall()
{
	x1 = container_width - (rand()%container_width);

	if(x1 > 0)
	{
		x2 = x1-1;
	}
	else
	{
		x2 = 1;
	}

	y1 = container_height;
	y2 = container_height;
}

void door_coordinate::build_east_wall()
{
	y1 = container_height - (rand()%container_height);

	if(y1 > 0)
	{
		y2 = y1-1;
	}
	else
	{
		y2 = 1;
	}

	x1 = container_width;
	x2 = container_width;
}

void door_coordinate::build_west_wall()
{
	y1 = container_height - (rand()%container_height);

	if(y1 > 0)
	{
		y2 = y1-1;
	}
	else
	{
		y2 = 1;
	}

	x1 = 0;
	x2 = 0;
}

bool door_coordinate::is_initialized()
{
	if(
		x1 != 0 &&
		x2 != 0 &&
		y1 != 0 &&
		y2 != 0
		)
	{
		return true;
	}

	return false;
}

void door_coordinate::display()
{
	std::cout << "(" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")" << std::endl;
}
