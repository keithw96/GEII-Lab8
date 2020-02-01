#pragma once
#include <iostream>
class Player
{
public:

    void update(int& x);
};

void Player::update(int& x)
{
    std::cout << "Player Update" << std::endl;
    x += 1;
}