#ifndef GRAPH
#define GRAPH
#include <fstream>

class graph; //forward declaration
class room; //forward declaration

class room
{
public:

	room();
	room(bool is_exit);
	room(int priz, int enem, bool hall, int widt, int heigh, int peri, int dist, int num);
	~room();

	void insert(room * source);
	void display(std::ofstream& output);
	void set_doors(room * _entrance, room * _exit, graph * container, int rooms_in_graph);
	room * get_next();

private:
	room * next;
	room * doors[MAX_DOORS];
	void display(room * source, std::ofstream& output);
	int perimeter;
	int prize;
	int enemies;
	bool hallway;
	int width;
	int height;	
	int distance;//What is this for?
	int number_doors;
	int room_number;
	bool not_already_a_door(room * source, int num_doors);
	bool exit;
};

class graph
{
public:
	graph();
	graph(int rooms);
	~graph();

	room * get_random_room();
	void generate(int num_rooms);
	void insert(room * source);
	void display();

private:
	void destroy(room * source);
	room * root;
	room * entrance;
	room * exit;
	int number_rooms;
};
#endif
