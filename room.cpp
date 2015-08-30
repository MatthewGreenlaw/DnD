#include <iostream>
#include "graph.h"
#include <cstdlib>
#include <ctime>

using namespace std;

vertex::vertex()
{
	next = NULL;

	for(int i = 0; i < MAX_DOORS; i++)
	{
		doors[i] = NULL;
	}
}

vertex::vertex(bool is_exit):room(is_exit)
{
	next = NULL;

	for(int i = 0; i < MAX_DOORS; i++)
	{
		doors[i] = NULL;
	}
}

vertex::vertex(int priz, int enem, bool hall, int widt, int heigh, int peri, int num):room(priz, enem, hall, widt, heigh, peri, num)
{
	next = NULL;

	for(int i = 0; i < MAX_DOORS; i++)
	{
		doors[i] = NULL;
	}
}

vertex::~vertex()
{

}


vertex * vertex::get_next()
{
	return next;
}

void vertex::build_doors(vertex * _entrance, vertex * _exit, graph * container, int rooms_in_graph)
{
	vertex * temp = NULL;
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
		next->build_doors(this, _exit, container, rooms_in_graph);
		next->build_door_locations(this);
	}
}

//Prevents creating pointers to duplicate doors
bool vertex::not_already_a_door(vertex * source, int num_doors)
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

void vertex::insert(vertex * source)
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

void vertex::display(ofstream& output)
{
	display(this, output);

	if(next)
	{
		next->display(output);
	}
}

void vertex::display(vertex * source, ofstream& output)
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
		output << "Number of doors: " << number_doors << endl;
		for(int i = 0; i < number_doors; i++)
		{
			output << "Door " << i+1 << " leads to room # " << doors[i]->room_number << "." << endl;
			output << "Door grid: ";
			
		}
	}

}


room::room()
{
	perimeter = 0;
	prize = 0;
	enemies = 0;
	hallway = false;
	exit = false;
	width = 0;
	height = 0;
	number_doors = 0;
	room_number = 0;	
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
	number_doors = 0;
	room_number = 0;

	for(int i = 0; i < MAX_DOORS-1; i++)
	{
		door_location[i] = new door_coordinate(this);
	}
}

room::room(int priz, int enem, bool hall, int widt, int heigh, int peri, int num)
{
	perimeter = peri;
	prize = priz;
	enemies = enem;
	hallway = hall;
	exit = false;
	width = widt;
	height = heigh;
	number_doors = 0;
	room_number = num;


	for(int i = 0; i < MAX_DOORS-1; i++)
	{
		door_location[i] = new door_coordinate(this);
	}
}

room::~room()
{

}

int room::get_width()
{
	return width;
}

void room::set_width(int w)
{
	width = w;
}

int room::get_height()
{
	return height;
}

void room::set_height(int h)
{
	height = h;
}

int room::get_room_number()
{
	return room_number;
}

void room::set_room_number(int n)
{
	room_number = n;
}

int room::get_perimeter()
{
	return perimeter;
}

void room::set_perimeter(int p)
{
	perimeter = p;
}

int room::get_num_doors()
{
	return number_doors;
}

void room::set_num_doors(int n)
{
	number_doors = n;
}

bool room::get_hallway()
{
	return hallway;
}

void room::set_hallway(bool h)
{
	hallway = h;
}

bool room::get_exit()
{
	return exit;
}

void room::set_exit(bool e)
{
	exit = e;
}

std::string room::get_door_side_at(int loc)
{
	return door_location[loc]->get_door_side();
}

void room::get_door_loc_at(int loc, sf::Vector2f& point1, sf::Vector2f& point2)
{
	point1.x = (float)door_location[loc]->get_x1();
	point2.x = (float)door_location[loc]->get_x2();
	point1.y = (float)door_location[loc]->get_y1();
	point2.y = (float)door_location[loc]->get_y2();
}

//Base doors off of cardinal direction. NW wall etc...
//Base rooms off door to previous room.
//The whole map can be figured out by door locations and room dimensions.
void room::build_door_locations(room * source)
{
	//srand(static_cast<unsigned>(time(NULL)));
	int wall = 0;

	for(int i = 0; i < number_doors; i++)
	{
		
		wall = rand()%4+1;//Random: 1-4;

		//Determine placement for first door based off door from last room
		if(i == 0)
		{
			//Set doors to match up geographically |Room1| <- door-> |Room-B|
			if(source->door_location[1]->is_north_wall())//North Wall
			{
				wall = 1;//South Wall
			}
			else if(source->door_location[1]->is_south_wall())//South Wall
			{
				wall = 3;//North Wall
			}
			else if(source->door_location[1]->is_west_wall())//West wall
			{
				wall = 2;//East Wall
			}
			else if(source->door_location[1]->is_east_wall())//East Wall
			{
				wall = 4;//West Wall
			}
		}

		if(wall == 1)//North Wall
		{
			door_location[i]->build_north_wall();
			door_location[i]->set_door_side("north");
		}
		else if(wall == 2)// East Wall
		{
			door_location[i]->build_east_wall();
			door_location[i]->set_door_side("east");
		}
		else if(wall == 3)// South Wall
		{
			door_location[i]->build_south_wall();
			door_location[i]->set_door_side("south");
		}
		else if(wall == 4)// West Wall
		{
			door_location[i]->build_west_wall();
			door_location[i]->set_door_side("west");
		}

		if(duplicate_door_location())
		{
			door_location[i]->reset();
			i--;
		}

		std::cout << "Room: " << room_number << std::endl;
		std::cout << door_location[i]->get_door_side() << std::endl;
		door_location[i]->display();
	}
}

//true if the room has two doors at the same geographic location.
bool room::duplicate_door_location()
{
	for(int i = 0; i < number_doors; i++)
	{
		for(int j = 0; j < number_doors; j++)
		{
			if(i != j)
			{
				if(door_location[i]->same_as(door_location[j]) && door_location[i]->is_initialized())
				{

					//cout << this->room_number << " Probe0 " << i << j << endl;
					return true;

				}
			}
		}
	}

	return false;
}
