#include <string>
#include <iostream> 
#include <array>

/*pour random :*/
#include <cstdlib>
#include <ctime>

#include "Game.hpp"

/* FONCTIONS D'AFFICHAGE */
void draw_game_board(const std::array<std::array<char, 3>, 3>& board)
{
    /*
    pré-condition : 
        board : const ref of array of arrays of char
        > représente le plateau de jeu
        > board[i][j] == '.' si aucun joueur n'a joué dans la case
    post-condition : aucune
    effet de bord : affiche le plateau de jeu
    */

    for (int i {0}; i < 3 ; i++)
    {
        for (int j {0}; j < 3 ; j++)
        {
            std::cout << "| " << board[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }
}





std::array<std::array<char, 3>, 3> init_board()
{
    /*
    pré-condition : aucune
    post-condition : renvoie un array of arrays initialisé avec des '.'
    */

    std::array<std::array<char, 3>, 3> board {};    

    for (std::array<char, 3>& row : board)
    {
        row.fill('.');
    }

    return board;
}

/* FONCTIONS SANS AFFICHAGE */
std::string test_victory(const std::array< std::array<char, 3>, 3>& board, const Player& player1, const Player& player2)
{
    /*
    pré-conditions : 
        > board : const ref of array of arrays of char
        > player1, player2 : const ref struct Player
    post-condition : renvoie le nom du joueur gagnant ou "none" si pas de gagnant
    */

    for (int i {0} ; i < 3 ; i++)
    {
        /*regarde sur les lignes*/
        if (board[i][0] != '.' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            return symbol_to_name(board[i][0], player1, player2);
        }

        /*regarde sur les colonnes*/
        if (board[0][i] != '.' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            return symbol_to_name(board[0][i], player1, player2);
        }
    }

    /*regarde sur les diagonales*/
    if (board[0][0] != '.' && board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return symbol_to_name(board[0][0], player1, player2);
    }
    if (board[0][2] != '.' && board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return symbol_to_name(board[1][1], player1, player2);
    }

    return "none";
}

void player_move(std::array<std::array<char, 3>, 3>& board, const Player& player)
{
    /*
    pré-conditions : 
    > board : ref of array of arrays of char
    > player : const ref struct Player
    post-condition : aucune
    effet de bord : demande à l'utilisateur de rentrer des valeurs et modifie les elts de board
    */

    std::cout << "please choose a move: " << std::endl;

    int row {};
    int column {};
    std::cin >> row >> column;

    board[row][column] = player.symbol;
}

void two_players_round(std::array<std::array<char, 3>, 3>& board, const Player& player1, const Player& player2)
{
    /*
    pré-conditions : 
    > board : ref of array of arrays of char
    > player1, player 2 : const ref struct Player
    post-condition : aucune
    effet de bord : modifie les elts de board
    */
    
    player_move(board, player1);
    draw_game_board(board);

    /*player2 joue seulement si le coup de player1 n'était pas gagnant*/
    if (test_victory(board, player1, player2) == "none")
    {
        player_move(board, player2);
    }
}

void two_players_mode()
{
    /* création des joueurs : */
    std::cout << "player 1 : " << std::endl;
    Player player1 { create_player() };
    std::cout << "player 2 : " << std::endl;
    Player player2 { create_player() };


    std::array<std::array<char, 3>, 3> board {init_board()};
    
    int nb_tours {0};

    while (test_victory(board, player1, player2) == "none" && nb_tours < 9)
    {
        draw_game_board(board);
        two_players_round(board, player1, player2);
        nb_tours++;
    }

    if (test_victory(board, player1, player2) != "none")
    {
        std::cout << "the winner is :" << test_victory(board, player1, player2) << std::endl;
    }
    else 
    {
        std::cout << "it's a tie" << std::endl;
    }
}

void AI_mode()
{
    /* création des joueurs : */
    std::cout << "player : " << std::endl;
    Player player { create_player() };
    Player AI { "AI", 'O' };


    std::array<std::array<char, 3>, 3> board {init_board()};
    
    int nb_tours {0};

}

void AI_round()
{
    /*random generate puis IA amelioree avec algo alpha beta
    -->> faire verification des cin pour pas avoir des trucs impossibles
    -->> indication sur la manière de rentrer les valeurs i,j
    */
}

void start_menu()
{
    std::cout << "Menu démarrage : " << std::endl;
    std::cout << "Choisir mode de jeu : " << std::endl;
    std::cout << " 1 > 2 joueurs " << std::endl;
    std::cout << " 2 > 1 joeur et IA " << std::endl;

    char answer {};
    std::cin >> answer;

    switch (answer)
    {
        case '1' :
            two_players_mode();
            break;
        case '2' :
            AI_mode();
            break;
    }
}