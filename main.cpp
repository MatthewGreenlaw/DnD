#include <iostream>
#include "graph.h"
#include <SFML/Graphics.hpp>
/*
void main()
{
// room to test
int room_to_test = 1;

// Number of rooms to be generated
int num_rooms_to_generate = 5;

// Size of a single tile
float tileSize = 32;

// Generate the rooms
graph test;
test.generate(num_rooms_to_generate);

// This value is used to help find the center of any size RenderWindow
sf::VideoMode display(1600,900);

// Create the display window
sf::RenderWindow window(display, "Random Dungeon Generator", sf::Style::Titlebar | sf::Style::Default);
window.setFramerateLimit(30);

// Center the placement of the room inside the viewing window
sf::Vector2f room_position(0, 0);
room_position.x = (float)((display.width / 2) - (test.at(room_to_test)->get_width() * tileSize / 2));
room_position.y = (float)((display.height / 2) - (test.at(room_to_test)->get_height() * tileSize / 2));

// tile color
sf::Color tileColor = sf::Color::Green;

// tile outline color
sf::Color tileOutlineColor = sf::Color::Black;

// tile outline thickness
float tileOutlineThickness = -1;

// outline/wall color
sf::Color wallColor = sf::Color::White;

// Outline Wall Width
float wallWidth = 1;

// top left room coord
sf::Vector2f pos1(0, 0);
// bottom right room coord
sf::Vector2f pos2(0, 0);

// Coordinates for the sides of a single door
sf::Vector2f door_point1(0,0);
sf::Vector2f door_point2(0,0);

// For calling up a single room, and door in that room
room * temp;
temp = test.at(room_to_test);
int height = temp->get_height();
int width = temp->get_width();

// Used for visual testing of a single room
std::cout << "Data for room " << room_to_test << ":" << std::endl;
std::cout << "Room #: " << temp->get_room_number() << std::endl;
std::cout << "Number of Doors: " << temp->get_num_doors() << std::endl;

// height and width for bottom right corner
pos2.y = (static_cast<float>(height));
pos2.x = (static_cast<float>(width));	

// Create a floor tile to be reused
sf::RectangleShape block(sf::Vector2f(tileSize,tileSize));
block.setFillColor(tileColor);
block.setOutlineColor(tileOutlineColor);
block.setOutlineThickness(tileOutlineThickness);

// Set the outline for the room
// North line for outline
sf::RectangleShape lineTop(sf::Vector2f(pos2.x * tileSize, wallWidth));
lineTop.setFillColor(wallColor);
lineTop.setPosition(room_position.x, room_position.y);
lineTop.rotate(0);

// East line for outline
sf::RectangleShape lineRight(sf::Vector2f(pos2.y * tileSize, wallWidth));
lineRight.setFillColor(wallColor);
lineRight.setPosition(pos2.x * tileSize + room_position.x, room_position.y);
lineRight.rotate(90);

// South line for outline
sf::RectangleShape lineBottom(sf::Vector2f(pos2.x * tileSize, wallWidth));
lineBottom.setFillColor(wallColor);
lineBottom.setPosition(room_position.x, pos2.y * tileSize + room_position.y - 1);
lineBottom.rotate(0);

// West line for outline
sf::RectangleShape lineLeft(sf::Vector2f(pos2.y * tileSize, wallWidth));
lineLeft.setFillColor(wallColor);
lineLeft.setPosition(room_position.x + 1, room_position.y);
lineLeft.rotate(90);


sf::Event Event;
while (window.isOpen())
{
while (window.pollEvent(Event))
{
switch (Event.type)
{ 
case sf::Event::Closed:
window.close();
break;
}
}

// clear the window
window.clear();

// Set and Draw the floor tiles of the room
for (int j = 0; j < width; j++)
{
for (int k = 0; k < height; k++)
{
// get next coordinate for the tile
pos1.x = static_cast<float>(j) * tileSize + room_position.x;
pos1.y = static_cast<float>(k) * tileSize + room_position.y;

// set next coordinate for the tile
block.setPosition(pos1.x, pos1.y);

// draw the new single tile
window.draw(block);
}
}

// Draw the outline of the room
window.draw(lineTop);
window.draw(lineRight);
window.draw(lineBottom);
window.draw(lineLeft);

// Set and Draw the doors
for (int i = 0; i < temp->get_num_doors(); i++)
{
// Retrieve the x1,y1, and x2,y2 coordinates of the door
temp->get_door_loc_at(i, door_point1, door_point2);

// Create to lines to draw with the doors 2 coordinates
sf::Vertex line[] =
{
sf::Vertex(sf::Vector2f(room_position.x + (tileSize * door_point1.x), room_position.y + (tileSize * door_point1.y))),
sf::Vertex(sf::Vector2f(room_position.x + (tileSize * door_point2.x), room_position.y + (tileSize * door_point2.y)))
};

// Change Color of Door Lines from White
line[0].color = sf::Color::Red;
line[1].color = sf::Color::Red;

// Draw the line representing the single door
window.draw(line, 2, sf::Lines);
}

// display the new window
window.display();

}
}
*/

void DrawRoom(sf::RenderWindow& _window, sf::VideoMode _display, room * _temp, sf::Uint8& _alpha, sf::Clock& _clock);

void main()
{
	// Alpha levels for map color 0 to 255
	sf::Uint8 alpha = 0;
	sf::Clock clock;

	int nextRoom = 0;

	// room to test
	int room_to_test = 1;

	// Number of rooms to be generated
	int num_rooms_to_generate = 5;

	// Generate the rooms
	graph test;
	test.generate(num_rooms_to_generate);

	// This value is used to help find the center of any size RenderWindow
	sf::VideoMode display(1600,900);

	// Create the display window
	sf::RenderWindow window(display, "Random Dungeon Generator", sf::Style::Titlebar | sf::Style::Default);
	window.setFramerateLimit(30);

	// For calling up a single room, and door in that room
	room * temp;
	temp = test.at(room_to_test);
	int height = temp->get_height();
	int width = temp->get_width();

	// Used for visual testing of a single room
	std::cout << "Data for room " << room_to_test << ":" << std::endl;
	std::cout << "Room #: " << temp->get_room_number() << std::endl;
	std::cout << "Number of Doors: " << temp->get_num_doors() << std::endl;

	sf::Event Event;
	while (window.isOpen())
	{
		while (window.pollEvent(Event))
		{
			switch (Event.type)
			{ 
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed: // Real time map changes
				if(Event.key.code == sf::Keyboard::Return)
				{
					if(nextRoom < test.get_num_rooms())
					{
						temp = test.at(nextRoom);// Set current room to the next room in the list
						nextRoom++;// Set iterator to the next room in the list
						alpha = 0;// Set to 0, so next room can fade in
					}
					else// if nextRoom is out of bounds,
					{
						temp = test.at(0);// start back at room 0
						nextRoom = 1;// set iterator to the second room in the list
						alpha = 0;// Set to 0, so next room can fade in
					}
				}
			}
		}

		// clear the window
		window.clear();

		DrawRoom(window, display, temp, alpha, clock);

		// display the new window
		window.display();

	}
}

// Draw Room
// Descrip: This is called to draw a room in the RenderWindow. Multiple rooms can be called at once by calling this method multiple times in main().
// Arguments: sf::RenderWindow& - (_window) - Pass the renderWindow so that we can draw to it in int main()
//            sf::VideoMode (_display) - This is used to pass the size of the renderWindow so that we can set the map in the center of any window size set.
//            room * (_temp) - The room object that is to be displayed.
//            sf::Uint8& _alpha - An int variable to be set between 0 and 255 to set the opacity of the shapes being drawn.
//            sf::Clock (_clock) - A time keeper used to time the fade in rate of the room.
// Return: void
void DrawRoom(sf::RenderWindow& _window, sf::VideoMode _display, room * _temp, sf::Uint8& _alpha, sf::Clock& _clock)
{
	sf::Time time;

	// Size of a single tile
	float tileSize = 32;

	// Center the placement of the room inside the viewing window
	sf::Vector2f room_position(0, 0);
	room_position.x = (float)((_display.width / 2) - (_temp->get_width() * tileSize / 2));
	room_position.y = (float)((_display.height / 2) - (_temp->get_height() * tileSize / 2));

	// tile color
	sf::Color tileColor = sf::Color(0,255,0,_alpha);

	// tile outline color
	sf::Color tileOutlineColor = sf::Color(0,0,0,_alpha);

	// tile outline thickness
	float tileOutlineThickness = -1;

	// outline/wall color
	sf::Color wallColor = sf::Color(255,255,255,_alpha);

	// Outline Wall Width
	float wallWidth = 1;

	// top left room coord
	sf::Vector2f pos1(0, 0);
	// bottom right room coord
	sf::Vector2f pos2(0, 0);

	// Coordinates for the sides of a single door
	sf::Vector2f door_point1(0,0);
	sf::Vector2f door_point2(0,0);

	// Copy width and height of the room
	int height = _temp->get_height();
	int width = _temp->get_width();


	// height and width for bottom right corner
	pos2.y = (static_cast<float>(height));
	pos2.x = (static_cast<float>(width));	

	// Create a floor tile to be reused
	sf::RectangleShape block(sf::Vector2f(tileSize,tileSize));
	block.setFillColor(tileColor);
	block.setOutlineColor(tileOutlineColor);
	block.setOutlineThickness(tileOutlineThickness);

	// Set the outline for the room
	// North line for outline
	sf::RectangleShape lineTop(sf::Vector2f(pos2.x * tileSize, wallWidth));
	lineTop.setFillColor(wallColor);
	lineTop.setPosition(room_position.x, room_position.y);
	lineTop.rotate(0);

	// East line for outline
	sf::RectangleShape lineRight(sf::Vector2f(pos2.y * tileSize, wallWidth));
	lineRight.setFillColor(wallColor);
	lineRight.setPosition(pos2.x * tileSize + room_position.x, room_position.y);
	lineRight.rotate(90);

	// South line for outline
	sf::RectangleShape lineBottom(sf::Vector2f(pos2.x * tileSize, wallWidth));
	lineBottom.setFillColor(wallColor);
	lineBottom.setPosition(room_position.x, pos2.y * tileSize + room_position.y - 1);
	lineBottom.rotate(0);

	// West line for outline
	sf::RectangleShape lineLeft(sf::Vector2f(pos2.y * tileSize, wallWidth));
	lineLeft.setFillColor(wallColor);
	lineLeft.setPosition(room_position.x + 1, room_position.y);
	lineLeft.rotate(90);

	// Fade in
	time = _clock.getElapsedTime();
	if(time.asMilliseconds() >= 1 && _alpha < 251)
	{
		_alpha = _alpha + 4;
		_clock.restart();
	}

	block.setFillColor(sf::Color(0,255,0,_alpha));
	block.setOutlineColor(sf::Color(0,0,0,_alpha));
	lineTop.setFillColor(sf::Color(255,255,255,_alpha));
	lineRight.setFillColor(sf::Color(255,255,255,_alpha));
	lineBottom.setFillColor(sf::Color(255,255,255,_alpha));
	lineLeft.setFillColor(sf::Color(255,255,255,_alpha));


	// Set and Draw the floor tiles of the room
	for (int j = 0; j < width; j++)
	{
		for (int k = 0; k < height; k++)
		{
			// get next coordinate for the tile
			pos1.x = static_cast<float>(j) * tileSize + room_position.x;
			pos1.y = static_cast<float>(k) * tileSize + room_position.y;

			// set next coordinate for the tile
			block.setPosition(pos1.x, pos1.y);

			// draw the new single tile
			_window.draw(block);
		}
	}

	// Draw the outline of the room
	_window.draw(lineTop);
	_window.draw(lineRight);
	_window.draw(lineBottom);
	_window.draw(lineLeft);

	// Set and Draw the doors
	for (int i = 0; i < _temp->get_num_doors(); i++)
	{
		// Retrieve the x1,y1, and x2,y2 coordinates of the door
		_temp->get_door_loc_at(i, door_point1, door_point2);

		// Create to lines to draw with the doors 2 coordinates
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(room_position.x + (tileSize * door_point1.x), room_position.y + (tileSize * door_point1.y))),
			sf::Vertex(sf::Vector2f(room_position.x + (tileSize * door_point2.x), room_position.y + (tileSize * door_point2.y)))
		};

		// Change Color of Door Lines from White
		line[0].color = sf::Color(255,0,0,_alpha);
		line[1].color = sf::Color(255,0,0,_alpha);

		// Draw the line representing the single door
		_window.draw(line, 2, sf::Lines);
	}
}
