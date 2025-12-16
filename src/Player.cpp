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

    std::string line {};
    std::string name {};
    char symbol {};

    std::cout << "Please enter your NAME: " << std::endl;
    std::cin >> name;
 
    std::cout << "\n";
    std::cout << "Please choose a SYMBOL : " << std::endl;
    
    std::cin.ignore(1000, '\n');
    while (true)
    {
        std::getline(std::cin, line); /* récupération de la ligne entière de l'input*/

        if (line.size() == 1)
        {
            symbol = line[0]; /* input valide, on le stocke dans symbol */
            break;
        }

        std::cout << "\n";
        std::cout << "Invalid input. Please try again." << std::endl;
    }

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