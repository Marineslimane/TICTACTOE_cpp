#pragma once 

#include <string>

struct Player
{
    std::string name {};
    char symbol {}; /* 'X' ou 'O'*/
};

Player create_player();

std::string symbol_to_name(const char c, const Player& player1, const Player& player2);
