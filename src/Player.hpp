#pragma once 

#include <string>

struct Player
{
    std::string name {};
    char symbol {}; /* 'X' ou 'O'*/
};

Player create_player();