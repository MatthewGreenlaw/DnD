#ifndef GRAPH
#define GRAPH

const int ROOMS_LARGE = 100;
const int ROOMS_MED = 50;
const int ROOMS_SM = 10;

enum NUM_ROOMS
{
	LARGE,
	MEDIUM,
	SMALL
};

class room
{
public:

	room();
	~room();

	bool insert(room * source, room * pointerToDifferentVariable);
	//void generate();
	void display();
protected:
		room * next;

private:
	void display(room * source);
	room ** doors [1];
	int perimeter;
	int prize;
	int enemies;
	bool is_hallway;
	int width;
	int height;	
	int distance;


};

class graph
{
public:
	graph();
	graph(int rooms);
	~graph();

	void generate(int num_rooms);
	bool insert(room * source);
	void display();

private:
	void display(room * source);
	room * root;
};
#endif GRAPH
