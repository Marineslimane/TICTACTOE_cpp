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
    
    std::cout << "Hi! What's your name ?" << std::endl;
    std::cin >> name;

    std::cout << "Welcome, " << name << ". Please choose a symbol :" << std::endl;
    std::cin >> symbol;

    Player player {name, symbol};
    return player;
}
