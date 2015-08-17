#include <iostream>
#include "graph.h"
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
	for(int i = 0; i < num_rooms; i++)
	{
		room * temp = new room;
		insert(temp);
	}
}

bool graph::insert(room * source)
{
	if(root)
	{
		return root->insert(root, source);
		 
	}
	else
	{
		root = source;
		return true;
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
}

bool room::insert(room * source, room * pointerToDifferentVariable)
{
	source->next = pointerToDifferentVariable;
}

void room::display()
{

}

void room::display()
{
	display(this);
	this->next->display();
}

void room::display(room * source)
{

}