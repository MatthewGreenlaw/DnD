#include <iostream>
#include "graph.h"

int main()
{
	graph test;
	test.generate(12);
	test.display();

	std::cin.get();
	std::cin.ignore();

	return 1;
}