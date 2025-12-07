#include <string>
#include <iostream>
#include <array>

#include "Game.hpp"

void draw_game_board(const std::array<std::array<char, number_columns>, number_rows>& board)
{
    /*
    pré-condition : 
        board : référence vers un tableau statique (array) constant contenant 9 elts de type char
        > représente le plateau de jeu
        > elts : 'O' ou 'X' ou '.' si aucun joueur n'a encore joué dans cette case
    post-condition : aucune
    effet de bord : affiche le plateau de jeu
    */

    for (int i {0}; i < 3 ; i++)
    {
        for (int j {0}; j < 3 ; j++)
        {
            std::cout << "| " << board[i][j];
        }
        std::cout << " |" << std::endl;
    }
}

std::array<std::array<char, number_columns>, number_rows> init_board()
{
    /*
    pré-condition : aucune
    post-condition : renvoie un tableau statique initialisé par des '.'
    */

    std::array<std::array<char, number_columns>, number_rows> board {};    

    for (std::array<char, number_columns> row : board)
    {
        row.fill('.');
    }
    return board;
}

std::string test_victory(std::array< std::array<char, number_columns>, number_rows>& board, Player player1, Player player2)
{
    char winner {};
    for (int i {0} ; i < number_rows ; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            winner = board[i][0];
        }

        if (board[0][i] == board[1][i] && board[2][i] == board[0][i])
        {
            winner = board[0][i];
        }
    }

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        winner = board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        winner = board[0][2];
    }

    if (winner == player1.symbol)
    {
        return "player1";
    }
    else if (winner == player2.symbol)
    {
       return "player2";
    }
    return ".";
}

void two_players_round(std::array<std::array<char, number_columns>, number_rows>& board, Player player1, Player player2)
{
    std::cout << "player 1 choose a move: " << std::endl;
    int row1 {};
    std::cin >> row1;
    int column1 {};
    std::cin >> column1;

    board[row1][column1] = player1.symbol;

    std::cout << "player 2 choose a move: " << std::endl;
    int row2 {};
    std::cin >> row2;
    int column2 {};
    std::cin >> column2;

    board[row2][column2] = player2.symbol;
}

void two_players_mode()
{
    /* création des joueurs : */
    std::cout << "player 1 : " << std::endl;
    Player player1 { create_player() };
    std::cout << "player 2 : " << std::endl;
    Player player2 { create_player() };

    std::array<std::array<char, number_columns>, number_rows> board {init_board()};
    
    int nb_tours {0};

    while (test_victory(board, player1, player2) == "." || nb_tours < 9)
    {
        two_players_round(board, player1, player2);
        test_victory(board, player1, player2);

        nb_tours++;
    }

    if (test_victory(board, player1, player2) != ".")
    {
        std::cout << test_victory(board, player1, player2) << std::endl;
    }
    else 
    {
        std::cout << "it's a tie" << std::endl;
    }
}


void AI_mode()
{

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