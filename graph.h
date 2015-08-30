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
#include <SFML/Graphics.hpp>

const int MAX_DOORS = 8;

class graph; //forward declaration
class room;

class door_coordinate
{
public:
	door_coordinate();
	door_coordinate(room * container);

	//Getters/setters
	int get_x1();
	void set_x1(int n);
	int get_x2();
	void set_x2(int n);
	int get_y1();
	void set_y1(int n);
	int get_y2();
	void set_y2(int n);

	std::string get_door_side();
	void set_door_side(std::string n);

	//helpers
	bool is_north_wall();
	bool is_south_wall();
	bool is_west_wall();
	bool is_east_wall();
	bool is_initialized();
	bool same_as(door_coordinate * source);

	//Mutators
	void reset();
	void build_north_wall();
	void build_south_wall();
	void build_east_wall();
	void build_west_wall();

	//Debugging
	void display();

	//Operator Overloads
	bool operator == (const door_coordinate&) const;

private:
	int container_width;
	int container_height;
	int x1;
	int y1;
	int x2;
	int y2;
	enum DOOR_SIDE// The side of the room the door is on 
	{
		north,
		south,
		east,
		west
	};
	DOOR_SIDE door_side;
};

class room
{
public:
	//Constructors
	room();
	room(bool is_exit);//used to build the exit room
	room(int priz, int enem, bool hall, int widt, int heigh, int peri, int num);//Used to insert random rooms
	~room();

	//Getters/setters
	int get_width();
	void set_width(int w);
	int get_height();
	void set_height(int h);
	int get_room_number();
	void set_room_number(int n);
	int get_perimeter();
	void set_perimeter(int p);
	int get_num_doors();
	void set_num_doors(int n);
	bool get_hallway();
	void set_hallway(bool h);
	bool get_exit();
	void set_exit(bool e);

	std::string get_door_side_at(int loc);// returns a string of north, south, east, or west, that the door resides on
	void get_door_loc_at(int loc, sf::Vector2f& point1, sf::Vector2f& point2);

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
};

class vertex:public room
{
public:
	//Constructors
	vertex();
	vertex(bool is_exit);//used to build the exit room
	vertex(int priz, int enem, bool hall, int widt, int heigh, int peri, int num);//Used to insert random rooms
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
	int get_num_rooms();
	vertex * get_random_room();
	vertex * at(int n);

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
