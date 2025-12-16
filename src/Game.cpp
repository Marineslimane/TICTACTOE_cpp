#include <string>
#include <iostream> 
#include <array>
#include <vector>

/*pour random :*/
#include <cstdlib>
#include <ctime>

#include "Game.hpp"

/* FONCTIONS GÉNÉRALES */
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

    /* affichage des indices pour faciliter la compréhension */
    std::cout << "  ";
    for (int j {0}; j < 3 ; j++)
    {

       std::cout << "  " << j << " ";
    }
    std::cout << "\n";


    for (int i {0}; i < 3 ; i++)
    {
        /* de même, affichage des indices*/
        std::cout << i << " ";


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
    effet de bord : demande à l'utilisateur de rentrer des valeurs pour le coup à jouer et modifie les elts de board
    */

    std::cout << "Please choose a move. To choose a move, enter the index of the row and then the index of the column :" << std::endl;
    std::cout << "Enter row index : " << std::endl;
    std::cout << "\n";

    int row {};
    int column {};
    std::string line {};

    while (true)
    {
        std::getline(std::cin, line); /* récupération de la ligne entière de l'input*/

        if ((line.size() == 1) && (line[0] >= '0' && line[0] <= '2'))
        {
            row = line[0] - '0'; /* input valide, on le stocke dans answer*/
            /* conversion de line[0] en int*/
            break;
        }

        std::cout << "Invalid input. Please try again." << std::endl;
    }

    std::cout << "And column index : " << std::endl;
    std::cout << "\n";

    while (true)
    {
        std::getline(std::cin, line); /* récupération de la ligne entière de l'input*/

        if ((line.size() == 1) && (line[0] >= '0' && line[0] <= '2'))
        {
            column = line[0] - '0'; /* input valide, on le stocke dans answer*/
            break;
        }

        std::cout << "Invalid input. Please try again." << std::endl;
    }

    if (board[row][column] != '.')
    {
        std::cout << "That position is already taken! Try again." << std::endl;
        player_move(board, player);
        return; /* pour éviter d'avoir des problèmes avec le rappel de la fonction du style les symboles qui changent*/
    }

    board[row][column] = player.symbol;
}

/* FONCTIONS 2 PLAYERS MODE */
void two_players_round(std::array<std::array<char, 3>, 3>& board, const Player& player1, const Player& player2)
{
    /*
    pré-conditions : 
    > board : ref of array of arrays of char
    > player1, player 2 : const ref struct Player
    post-condition : aucune
    effet de bord : modifie les elts de board, affiche le plateau de jeu
    */
    
    player_move(board, player1);
    draw_game_board(board);

    /*player2 joue seulement si le coup de player1 n'était pas gagnant*/
    if (test_victory(board, player1, player2) == "none")
    {
        player_move(board, player2);
        draw_game_board(board);
    }
}

void two_players_mode()
{
    /* création des joueurs : */
    std::cout << "\n";
    std::cout << "-- PLAYER 1 --" << std::endl;
    std::cout << "\n";
    Player player1 { create_player() };
    std::cout << "-- PLAYER 2 -- " << std::endl;
    Player player2 { create_player() };

    while (player1.symbol == player2.symbol)
    {
        std::cout << "Please don't use the same symbol. Try again : " << std::endl;

        std::cout << "\n";
        std::cout << "-- PLAYER 2 -- " << std::endl;
        player2 = create_player();
    }


    std::array<std::array<char, 3>, 3> board {init_board()};
    draw_game_board(board);
    
    /* je compte un round comme les 2 joueurs qui jouent*/
    int rounds {0};

    while (test_victory(board, player1, player2) == "none" && rounds < 5)
    {
        two_players_round(board, player1, player2);
        rounds++;
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

/* FONCTIONS AI MODE */
void unbiased_random_move(std::array<std::array<char, 3>, 3>& board, const Player& AI)
{
    /*
    pré-conditions : 
    > board : ref of array of arrays of char
    > AI : const ref struct Player
    post-condition : aucune
    effet de bord : modifie les elts de board

    >> coup random de l'IA avec la méthode "non biaisée" vue en cours : récupération des cases vides puis
    hasard sur la sélection de la case vide où jouer
    */

    /* tableau des duos d'indices correspondant à des cases vides  : */
    std::vector<std::array<int, 2>> empty_squares {};


    for (int i {0}; i < 3 ; i++)
    {
        for (int j {0}; j < 3 ; j++)
        {
            if (board[i][j] == '.')
            {
                empty_squares.push_back({i,j});
            }
        }
    }

    /* sélection random d'un duo d'indices (ici c'est l'indice du tableau des duos qui est généré): */
    int random_index {static_cast<int>(rand() % empty_squares.size())};

    /* récupération du duo d'indices grâce à l'indice random généré */
    std::array<int, 2> random_vector {empty_squares[random_index]};

    /* à la case random, l'IA joue (les indices sont rangés dans l'ordre ligne puis colonne) */
    board[random_vector[0]][random_vector[1]] = AI.symbol;
}

void AI_round(std::array<std::array<char, 3>, 3>& board, const Player& player, const Player& AI)
{
    /*
    pré-conditions : 
    > board : ref of array of arrays of char
    > player, AI : const ref struct Player
    post-condition : aucune
    effet de bord : modifie les elts de board, affiche le plateau
    */
    
    player_move(board, player);
    draw_game_board(board);

    /*AI joue seulement si le coup de player n'était pas gagnant*/
    if (test_victory(board, player, AI) == "none")
    {
        unbiased_random_move(board, AI);
        std::cout << " " << std::endl;
        std::cout << "AI move : " << std::endl;
        std::cout << " " << std::endl;
        draw_game_board(board);
    }
}

void AI_mode()
{
    /* création des joueurs : */
    std::cout << "player : " << std::endl;
    Player player { create_player() };
    Player AI { "AI", 'A' };


    std::array<std::array<char, 3>, 3> board {init_board()};
    draw_game_board(board);
    
    /* je compte un round comme les 2 joueurs qui jouent*/
    int rounds {0};

    while (test_victory(board, player, AI) == "none" && rounds < 5)
    {
        AI_round(board, player, AI);
        rounds++;
    }

    if (test_victory(board, player, AI) != "none")
    {
        std::cout << "the winner is :" << test_victory(board, player, AI) << std::endl;
    }
    else 
    {
        std::cout << "it's a tie" << std::endl;
    }
}


/* FONCTION DE DÉMARRAGE */
void start_menu()
{
    std::cout << "\n";
    std::cout << " ------------- START MENU ------------- " << std::endl;
    std::cout << "\n";
    std::cout << "       Please choose a GAMEMODE " << std::endl;
    std::cout << "\n";
    std::cout << "Enter the corresponding number to access the desired GAMEMODE " << std::endl;
    std::cout << " 1 : 2 PLAYERS MODE " << std::endl;
    std::cout << " 2 : AI vs PLAYER MODE " << std::endl;
    std::cout << "\n";

    /* vérification des inputs : */
    std::string line {};
    char answer {};
 
    while (true)
    {
        std::getline(std::cin, line); /* récupération de la ligne entière de l'input*/

        if (line.size() == 1 && (line[0] == '1' || line[0] == '2'))
        {
            answer = line[0]; /* input valide, on le stocke dans answer*/
            break;
        }

        std::cout << "Invalid input. Please try again." << std::endl;
    }

    switch (answer)
    {
        case '1' :
            two_players_mode();
            break;
        case '2' :
            srand(time(nullptr));
            AI_mode();
            break;
    }
}