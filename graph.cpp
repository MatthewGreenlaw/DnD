#include <iostream>
#include "graph.h"
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int MAX_WIDTH = 12;
const int MIN_WIDTH = 6;
const int MAX_HEIGHT = 10;
const int MIN_HEIGHT = 3;
const int CHANCE_OF_ENEMIES = 2; //1 in x chance
const int CHANCE_OF_HALLWAY = 5; //1 in x chance

graph::graph()
{
	root = NULL;
	entrance = NULL;
	exit = NULL;
	number_rooms = 0;
}

graph::~graph()
{
	if(root)
	{
		destroy(root);
	}

	delete entrance;
	delete exit;
}

void graph::destroy(vertex * source)
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
	srand(static_cast<unsigned>(time(NULL)));

	entrance = new vertex(0, 0, false, 7, 7, 0, 0);
	exit = new vertex(true);

	//Initialize parameters
	int priz = 0;
	int enem = 0;
	int hall = 0;
	int widt = 0;
	int heigh = 0;
	int peri = 0;
	bool _hall = false;
	vertex * temp = NULL;
	int chance_enem = 0;


	//create a number of rooms equal to num_rooms
	for(int i = 0; i < num_rooms; i++)
	{
		//reset parameters
		priz = 0;
		enem = 0;
		_hall = false;
		temp = NULL;
		chance_enem = 0;

		//Make width and height default to max hallway width. 
		widt = 2;
		heigh = 2;
		peri = 0;
		hall = rand()%CHANCE_OF_HALLWAY;// 1/10 chance of hallway

		//If the new room is not a hallway
		if(hall != 0)
		{
			_hall = false;
			widt = rand()%(MAX_WIDTH-MIN_WIDTH)+MIN_WIDTH;;//Random: 6-12 
			heigh = rand()%(MAX_HEIGHT-MIN_HEIGHT)+MIN_HEIGHT;//Random: 3-10
			peri = widt*2+heigh*2;
		}
		//If the new room is a hallway
		else
		{
			_hall = true;
			
			//Randomize if the hallway will go vertical or horizontal
			if(rand()%2)
			{
				heigh = rand()%(MAX_HEIGHT-MIN_HEIGHT)+MIN_HEIGHT;//Random: 3-10
				peri = widt*2+heigh*2;
			}
			else
			{
				widt = rand()%(MAX_WIDTH-MIN_WIDTH)+MIN_WIDTH;;//Random: 6-12 
				peri = widt*2+heigh*2;
			}
		}

		chance_enem = rand()%CHANCE_OF_ENEMIES;

		//Randomize parameters
		if(chance_enem == 0)
		{
			enem = rand()%(peri/3);//Random: 0-(quarter of parameter)
			if(enem > 0) priz = rand()%(enem*2);//Random: 0-(enemies*2)
		}

		//Create a new room using the above parameters and insert it into the graph
		temp = new vertex(priz, enem, _hall, widt, heigh, peri, i);
		insert(temp);
	}

	//build the adjacentcy list of doors for each room once the graph is built
	root->build_doors(entrance, exit, this, num_rooms);
	root->build_door_locations(entrance);

}

void graph::insert(vertex * source)
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

int graph::get_num_rooms()
{
	return number_rooms;
}

vertex * graph::get_random_room()
{
	vertex * temp = root;

	for(int i = 0; i < rand()%number_rooms; i++)//rand()%number_rooms = Random: 0 - number_rooms-1
	{
		temp = temp->get_next();
	}

	return temp;
}

vertex * graph::at(int n)
{
	vertex * temp = root;

	for(int i = 0; i < n; i++)
	{
		temp = temp->get_next();
	}

	return temp;
}

void graph::display()
{
	ofstream output;
	output.open("output/output"+to_string(time(NULL))+".txt");

	root->display(output);

	output.close();
}
