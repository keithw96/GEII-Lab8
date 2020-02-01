#pragma once
#include <iostream>

class Render
{
public:

	void update(int &y);
};

void Render::update(int &y)
{
	std::cout << "Update Render" << std::endl;

	y += 1;

}