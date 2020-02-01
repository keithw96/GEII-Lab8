#pragma once
#include <iostream>

class Physics
{
public:

	void update(int& y);
};

void Physics::update(int &y)
{
	std::cout << "Update Physics" << std::endl;
	y += 5;
}