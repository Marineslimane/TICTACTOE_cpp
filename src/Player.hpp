#pragma once 

#include <string>

struct Player
{
    std::string name {};
    char symbol {}; /* 'X' ou 'O'*/
};

Player create_player();

std::string symbol_to_name(char c, Player player1, Player player2);
