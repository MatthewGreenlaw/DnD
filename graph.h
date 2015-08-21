/*====================================
Program Name: graph (header file)
Programmer(s): Matthew Greenlaw
Program number: Version 1
Date: Aug. 20, 2015
Program used: Visual Studio, VIm, gdb, valgrind

Purpose: 
o The room class:
	The room class is based off a vertex node used in graph data structures.
	Each instance of the room class represents a virtual room.
	The room class emulates a virtex node used in 
	
o The graph class:

================================================== */

#ifndef GRAPH
#define GRAPH
#include <fstream>

const int MAX_DOORS = 8;

class graph; //forward declaration
class room;

class door_coordinate
{
public:
	door_coordinate();
	door_coordinate(room * container);

	//helpers
	bool is_north_wall();
	bool is_south_wall();
	bool is_west_wall();
	bool is_east_wall();
	bool is_itialized();

	//Mutators
	void reset();
	void build_north_wall();
	void build_south_wall();
	void build_east_wall();
	void build_west_wall();

	//Debugging
	void display(std::ofstream& output);

	//Operator Overloads
	bool operator == (const door_coordinate&) const;

private:
	int container_width;
	int container_height;
	int x1;
	int y1;
	int x2;
	int y2;
};

class room
{
public:
	//Constructors
	room();
	room(bool is_exit);//used to build the exit room
	room(int priz, int enem, bool hall, int widt, int heigh, int peri, int dist, int num);//Used to insert random rooms
	~room();

	//Getters/setters
	int get_width();
	int get_height();

	//Mutators
	void build_door_locations(room * source);
	
protected:
	//Helpers
	bool duplicate_door_location();

	//Abstract Data Members
	door_coordinate * door_location[MAX_DOORS];//Pair of xy coordinates creating a vector representing the door
	int prize;//Build this into an ADT
	int enemies;//Build this into an ADT
	
	//Basic Data Members
	int width;
	int height;	
	int perimeter;
	int number_doors;//How many doors a room has
	int room_number;//The number of the room
	bool hallway;//True if room is a hallway
	bool exit;//True if the room is the exit placeholder

	int distance;//What is this for?
};

class vertex:public room
{
public:
	//Constructors
	vertex();
	vertex(bool is_exit);//used to build the exit room
	vertex(int priz, int enem, bool hall, int widt, int heigh, int peri, int dist, int num);//Used to insert random rooms
	~vertex();

	//Getters/Setters
	vertex * get_next();

	//Mutators
	void insert(vertex * source);
	void build_doors(vertex * _entrance, vertex * _exit, graph * container, int rooms_in_graph);

	//helpers
	bool not_already_a_door(vertex * source, int num_doors);

	//Debugging
	void display(vertex * source, std::ofstream& output);
	void display(std::ofstream& output);
protected:
	
private:
	//Abstract Data Members
	vertex * next;
	vertex * doors[MAX_DOORS];//Adjacentcy list
};

class graph
{
public:
	//Constructors
	graph();
	//graph(const graph& source);
	graph(int rooms);//Builds a graph with X amount of rooms
	~graph();

	//Getters/Setters
	vertex * get_random_room();

	//Mutators
	void insert(vertex * source);
	void generate(int num_rooms);
	
	//Debugging
	void display();

private:
	//Mutators
	void destroy(vertex * source);
	
	//Abstract Data Members
	vertex * root;
	vertex * entrance;//Empty placeholder room used for door generation and placement
	vertex * exit;//Empty placeholder room used for door generation and placement

	//Basic Data Members
	int number_rooms;//Keeps track of how many rooms are in a graph
};
#endif