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
	is_hallway = false;
	width = 0;
	height = 0;
	distance = 0;
	number_doors = 0;
	room_number = 0;
	next = NULL;

	for(int i = 0; i < MAX_DOORS; i++)
	{
		doors[i] = NULL;
	}
	
}

room::room(int priz, int enem, bool hall, int widt, int heigh, int peri, int dist, int num)
{
	perimeter = peri;
	prize = priz;
	enemies = enem;
	is_hallway = hall;
	width = widt;
	height = heigh;
	distance = dist;
	number_doors = 0;
	room_number = num;
	next = NULL;

	for(int i = 0; i < MAX_DOORS; i++)
	{
		doors[i] = NULL;
	}
}

room::~room()
{

}


room * room::get_next()
{
	return next;
}

void room::set_doors(graph * home, int rooms_in_graph)
{
	int doors_to_add = 0;

	if(is_hallway)
	{
		doors_to_add = perimeter/5;
	}
	else
	{
		doors_to_add = perimeter/10;
	}
	
	//point first door to the next room
	if(this->next)
	{
		doors[0] = this->next;
	}
	//The last room points to the end room
	else
	{
		doors[0] = new room(0,0,false,0,0,0,0,0);
	}
	number_doors++;
	doors_to_add--;

	for(int i = 1; i < doors_to_add-2; i++)
	{
		
		room * temp = home->get_random_room();

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
}

bool room::not_already_a_door(room * source, int num_doors)
{
	for(int i = 0; i < num_doors-1; i++)
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

void room::display()
{
	display(this);

	if(next)
	{
		next->display();
	}
}

void room::display(room * source)
{
	if(source)
	{
		cout << "Room: " << room_number;
		if(is_hallway)
		{
			cout << " (Hallway)" << endl;
		}
		else
		{
			cout << endl;
		}

		cout << "Width X Height: " << width << "X" << height << endl;

		for(int i = 0; i < number_doors; i++)
		{
			cout << "Door " << i+1 << " leads to room # " << doors[i]->room_number << "." << endl;
		}
	}
}