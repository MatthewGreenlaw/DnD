#include <iostream>
#include "graph.h"
#include <cstdlib>
#include <ctime>

using namespace std;

graph::graph()
{
	root = NULL;
	exit = new room(true);
	number_rooms = 0;
}

graph::~graph()
{
	if(root)
	{
		destroy(root);
	}

	delete exit;
}

void graph::destroy(room * source)
{
	if(source->get_next())
	{
		destroy(source->get_next());
		delete source;
	}
	else
	{
		delete source;
	}
}

void graph::generate(int num_rooms)
{
	srand (time(NULL));

	//create a number of rooms equal to num_rooms
	for(int i = 0; i < num_rooms; i++)
	{
		//Initialize random parameters
		int priz = rand()%2;
		int enem = rand()%4;
		int dist = rand();
		int hall = rand()%2;//Either a 0 or 1

		//Make width and height default to max hallway width. 
		int widt = 2;
		int heigh = 2;
		int peri = 0;

		//If the new room is not a hallway
		if(hall == 0)
		{

			widt = rand()%12+6;
			heigh = rand()%10+3;
			peri = widt*2+heigh*2;
		}
		//If the new room is a hallway
		else
		{
			//Randomize if the hallway will go vertical/horizontal
			if(rand()%2)
			{
				heigh = rand()%10+3;
				peri = widt*2+heigh*2;
			}
			else
			{
				widt = rand()%12+6;
				peri = widt*2+heigh*2;
			}
		}

		//Convert random number to bool
		bool _hall = false;
		if(hall % 2)
		{
			_hall = true;
		}

		//Create a new room using the above parameters and insert it into the graph
		room * temp = new room(priz, enem, _hall, widt, heigh, peri, dist, i+1);
		insert(temp);
	}

	//Once the graph is built, build the adjacentcy list of doors for each room
	room * temp = root;
	while(temp)
	{
		set_doors(this, temp, num_rooms);
		temp = temp->get_next();
	}
}

room * graph::get_exit()
{
	return exit;
}

void graph::set_doors(graph * home, room * source, int num_rooms)
{
	if(source)
	{
		source->set_doors(home, num_rooms);
	}
}

void graph::insert(room * source)
{
	if(root)
	{
		root->insert(source);
	}
	else
	{
		root = source;
	}

	number_rooms++;
}

room * graph::get_random_room()
{
	room * temp = root;

	for(int i = 0; i < rand()%number_rooms; i++)//rand()%number_rooms = a random number from 0 through number_rooms-1
	{
		temp = temp->get_next();
	}

	return temp;
}

void graph::display()
{
	display(root);
}

void graph::display(room * source)
{
	source->display();
}

