#pragma once 
/*liste des déclarations des fonctions et structs*/

#include <string>

struct Player
{
    std::string name {};
    std::string symbol {}; /* 'X' ou 'O'*/

};

Player create_player();
