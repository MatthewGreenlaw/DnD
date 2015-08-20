#include <iostream>
#include "graph.h"
#include <cstdlib>
#include <ctime>

using namespace std;

room::room()
{
	perimeter = 0;
	prize = 0;
	enemies = 0;
	hallway = false;
	exit = false;
	width = 0;
	height = 0;
	distance = 0;
	number_doors = 0;
	room_number = 0;
	next = NULL;
	
	for(int i = 0; i < MAX_DOORS; i++)
	{
		doors[i] = NULL;
		door_location[i].x1 = 0;
		door_location[i].y1 = 0;
		door_location[i].x2 = 0;
		door_location[i].y2 = 0;
	}
	
}

room::room(bool is_exit)
{
	perimeter = 0;
	prize = 0;
	enemies = 0;
	hallway = false;
	exit = is_exit;
	width = 0;
	height = 0;
	distance = 0;
	number_doors = 0;
	room_number = 0;
	next = NULL;

	for(int i = 0; i < MAX_DOORS; i++)
	{
		doors[i] = NULL;
		door_location[i].x1 = 0;
		door_location[i].y1 = 0;
		door_location[i].x2 = 0;
		door_location[i].y2 = 0;
	}
	
}

room::room(int priz, int enem, bool hall, int widt, int heigh, int peri, int dist, int num)
{
	perimeter = peri;
	prize = priz;
	enemies = enem;
	hallway = hall;
	exit = false;
	width = widt;
	height = heigh;
	distance = dist;
	number_doors = 0;
	room_number = num;
	next = NULL;

	for(int i = 0; i < MAX_DOORS; i++)
	{
		doors[i] = NULL;
		door_location[i].x1 = 0;
		door_location[i].y1 = 0;
		door_location[i].x2 = 0;
		door_location[i].y2 = 0;
	}
}

room::~room()
{

}

room * room::get_next()
{
	return next;
}

void room::set_doors(room * _entrance, room * _exit, graph * container, int rooms_in_graph)
{
	room * temp = NULL;
	int doors_to_add = 0;

	if(hallway)
	{
		doors_to_add = perimeter/5;
	}
	else
	{
		doors_to_add = perimeter/10;
	}
	
	//point first door to the next room if there is one
	if(this->next)
	{
		doors[0] = _entrance;
		doors[1] = this->next;
	}
	//The last room points to the exit
	else
	{
		doors[0] = _entrance;
		doors[1] = _exit;
	}
	number_doors = number_doors + 2;
	//doors_to_add = doors_to_add + 2;//Played around with this being -2. leaving it out all together seems best.

	for(int i = 2; i < doors_to_add; i++)
	{
		temp = container->get_random_room();

		if(not_already_a_door(temp, number_doors) && temp->room_number != this->room_number)
		{
			doors[i] = temp;
			number_doors++;
		}
		else
		{
			i--;
		}
	}

	if(next)
	{
		next->set_doors(this, _exit, container, rooms_in_graph);
		next->set_door_locations();
	}
}

//Base doors off of cardinal direction. NW wall etc...
//Base rooms off door to previous room.
//The whole map can be figured out by door locations and room dimensions.
void room::set_door_locations()
{
	int wall = 0;

	for(int i = 0; i < number_doors; i++)
	{
		wall = rand()%4+1;//Random: 1-4;

		//North Wall
		if(wall == 1)
		{
			door_location[i].x1 = width - (rand()%width);

			if(door_location[i].x1 > 0)
			{
				door_location[i].x2 = door_location[i].x1-1;
			}
			else
			{
				door_location[i].x2 = 1;
			}

			door_location[i].y1 = height;
			door_location[i].y2 = height;
		}
		else if(wall == 2)
		{
			door_location[i].y1 = height - (rand()%height);

			if(door_location[i].y1 > 0)
			{
				door_location[i].y2 = door_location[i].y1-1;
			}
			else
			{
				door_location[i].y2 = 1;
			}

			door_location[i].x1 = width;
			door_location[i].x2 = width;
		}
		else if(wall == 3)
		{
			door_location[i].y1 = height - (rand()%height);

			if(door_location[i].y1 > 0)
			{
				door_location[i].y2 = door_location[i].y1-1;
			}
			else
			{
				door_location[i].y2 = 1;
			}
		}
		else if(wall == 4)
		{
			door_location[i].y1 = height - (rand()%height);

			if(door_location[i].y1 > 0)
			{
				door_location[i].y2 = door_location[i].y1-1;
			}
			else
			{
				door_location[i].y2 = 1;
			}
		}
	}
}

bool room::not_already_a_door(room * source, int num_doors)
{
	for(int i = 0; i < num_doors; i++)
	{
		if(source == doors[i])
		{
			return false;
		}
	}

	return true;
}

void room::insert(room * source)
{
	if(this->next)
	{
		this->next->insert(source);		
	}
	else
	{
		this->next = source;
	}
}

void room::display(ofstream& output)
{
	display(this, output);

	if(next)
	{
		next->display(output);
	}
}

void room::display(room * source, ofstream& output)
{
	

	if(source)
	{
		//output << time << endl;
		output << "************************************" << endl;
		output << "Room: " << room_number;
		if(hallway)
		{
			output << " (Hallway)" << endl;
		}
		else
		{
			output << endl;
		}

		output << "Width X Height: " << width << "X" << height << endl;
		output << "#Enemies: " << enemies << endl;
		output << "Loot: " << prize << endl;

		for(int i = 0; i < number_doors; i++)
		{
			output << "Door " << i+1 << " leads to room # " << doors[i]->room_number << "." << endl;
			output << "Door grid: (" << door_location[i].x1 << "," << door_location[i].y1 << ") (" << door_location[i].x2 << "," << door_location[i].y2 << ")" << endl;
		}
	}
	
}