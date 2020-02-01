#pragma once
#include <iostream>

class Input
{
public:

	void update(int& x);
};

void Input::update(int &x)
{
	std::cout << "Input Update" << std::endl;
	x += 5;
}