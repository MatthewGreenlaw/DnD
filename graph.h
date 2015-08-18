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
	room(int priz, int enem, bool hall, int widt, int heigh, int peri, int dist);
	//room(const room& source);
	~room();

	void insert(room * source);
	//void generate();
	void display();

	void set_doors(int rooms_in_graph);

private:
	room * next;
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
	//graph(const graph& source);
	graph(int rooms);
	~graph();

	void generate(int num_rooms);
	void insert(room * source);
	void display();

private:
	void set_doors(room * source, int rooms_in_graph);
	void display(room * source);
	room * root;
};


#endif