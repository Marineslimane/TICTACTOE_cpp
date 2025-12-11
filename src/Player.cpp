#include <string>
#include <iostream>
#include "Player.hpp"

Player create_player()
{
    /*
    pré-condition : aucune
    post-condition : renvoie une struct Player contenant les informations rentrées par le joueur
    effet de bord : affiche et demande à l'utilisateur d'entrer du texte
    */

    std::string name {};
    char symbol {};

    std::cout << "please enter your name: " << std::endl;
    std::cin >> name;
    std::cout << "what symbol would you like to use ? " << std::endl;
    std::cin >> symbol;

    Player player {name, symbol};
    return player;
}

std::string symbol_to_name(char c, Player player1, Player player2)
{
    if (c == player1.symbol)
    {
        return player1.name;
    }
    else if (c == player2.symbol)
    {
       return player2.name;
    }
    return ".";
}