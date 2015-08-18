#include <iostream>
#include "graph.h"
#include <cstdlib>
#include <ctime>

using namespace std;

graph::graph()
{
	root = NULL;
}

graph::~graph()
{
	if(root)
	{
		delete root;
	}
}

void graph::generate(int num_rooms)
{
	srand (time(NULL));

	for(int i = 0; i < num_rooms; i++)
	{

		int priz = rand()%2;
		int enem = rand()%4;
		int hall = rand()%2;
		int widt = rand()%12+6;
		int heigh = rand()%10+3;
		int peri = widt*2+heigh*2;
		int dist = rand();

		bool _hall = false;

		if(hall % 2)
		{
			_hall = true;
		}

		room * temp = new room(priz, enem, _hall, widt, heigh, peri, dist);
		insert(temp);
	}

	set_doors(root, num_rooms);
}

void graph::set_doors(room * source, int num_rooms)
{
	if(source)
	{
		source->set_doors(num_rooms);
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
}

void graph::display()
{
	display(root);
}

void graph::display(room * source)
{
	source->display();
}

room::room()
{
	perimeter = 0;
	prize = 0;
	enemies = 0;
	is_hallway = false;
	width = 0;
	height = 0;
	distance = 0;
	next = NULL;
}

room::room(int priz, int enem, bool hall, int widt, int heigh, int peri, int dist)
{
	perimeter = peri;
	prize = priz;
	enemies = enem;
	is_hallway = hall;
	width = widt;
	height = heigh;
	distance = dist;
	next = NULL;
}

room::~room()
{

}


void room::set_doors(int rooms_in_graph)
{
	int num_doors = perimeter/10;
	
	if(is_hallway)
	{
		num_doors = perimeter/5;
	}

	//this->room
	//LEFT OFF HERE. I think I am on the wrong track for getting doors setup, but I am working through the process. 

	
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
		cout << "Width X Height: " << width << "X" << height << endl;
		cout << "Hallway: " << is_hallway << endl;
		//cout << "Number Doors: " << 
	}
}