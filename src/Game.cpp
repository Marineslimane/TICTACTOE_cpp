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

    /* affichage des indices pour faciliter la compréhension : */
    std::cout << "  ";
    for (int j {0}; j < 3 ; j++)
    {

       std::cout << "  " << j << " ";
    }
    std::cout << "\n";


    for (int i {0}; i < 3 ; i++)
    {
        std::cout << i << " "; /*de même, affichage des indices*/

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
    post-condition : renvoie le nom du joueur gagnant ou "none" si pas de gagnant à ce stade 
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

    return "none"; /* pas de gagnant à ce stade de la partie*/
}

void player_move(std::array<std::array<char, 3>, 3>& board, const Player& player)
{
    /*
    pré-conditions : 
        > board : ref of array of arrays of char
        > player : const ref struct Player
    post-condition : aucune
    effet de bord : demande à l'utilisateur de rentrer des valeurs pour le coup à jouer et modifie les elts de board en fonction de ce coup
    */

    std::cout << "Please choose a move. To choose a move, enter the index of the row and then the index of the column :" << std::endl;
    std::cout << "Enter row index : " << std::endl;
    std::cout << "\n";

    int row {};
    int column {};
    std::string line {};

    /*vérification de l'input associé à row*/
    while (true)
    {
        std::getline(std::cin, line); /* récupération de la ligne entière de l'input*/

        if ((line.size() == 1) && (line[0] >= '0' && line[0] <= '2'))
        {
            row = line[0] - '0'; /* input valide, on le stocke dans row*/
            /* conversion de line[0] en int*/
            break;
        }

        std::cout << "Invalid input. Please try again." << std::endl;
    }

    std::cout << "And column index : " << std::endl;
    std::cout << "\n";

    /*vérification de l'input associé à column*/
    while (true)
    {
        std::getline(std::cin, line); /* récupération de la ligne entière de l'input*/

        if ((line.size() == 1) && (line[0] >= '0' && line[0] <= '2'))
        {
            column = line[0] - '0'; /* input valide, on le stocke dans column*/
            break;
        }

        std::cout << "Invalid input. Please try again." << std::endl;
    }

    if (board[row][column] != '.') /* vérification de la validité de la case choisie */
    {
        std::cout << "That position is already taken! Try again." << std::endl;
        player_move(board, player);
        return; /*pour éviter d'avoir des problèmes avec le rappel de la fonction du style les symboles qui changent*/
    }

    board[row][column] = player.symbol;
}

std::vector<std::array<int, 2>> possible_moves(const std::array<std::array<char, 3>, 3>& board)
{
    /*
    pré-conditions : 
        > board : const ref of array of arrays of char
    post-condition : renvoie tous les coups possibles ie les cases vides sous forme de vector of arrays of int
    */

    std::vector<std::array<int, 2>> empty_squares {}; /* tableau des duos d'indices correspondant à des cases vides */

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

    return empty_squares;
}

void winner_announcement(const std::array<std::array<char, 3>, 3>& board, Player& player1, Player& player2)
{
    /*
    pré-conditions : 
        > board : const ref of array of arrays of char
        > player1, player2 : const ref Player
    post-condition : aucune
    effet de bord : affiche le nom du gagnant ou annonce l'égalité si égalité
    */

    std::string winner {test_victory(board, player1, player2)};

    if (winner != "none")
    {
        std::cout << "\n";
        std::cout << "The WINNER is : " << winner << std::endl;
    }
    else 
    {
        std::cout << "\n";
        std::cout << "It's a tie !" << std::endl;
    }
}

void same_symbol_verification(const Player& player1, Player& player2)
{
    /*
    pré-conditions : 
        > player1 : const ref struct Player
        > player 2 : ref struct Player
    post-condition : aucune
    effet de bord : affiche du texte, demande à player2 de rerentrer un nom et un symbol si le symbole choisi est identique à celui de player1
    */

    while (player1.symbol == player2.symbol)
    {
        std::cout << "Please don't use the same symbol. Try again : " << std::endl;
        std::cout << "\n";

        if (player1.name != "AI")
        {
            std::cout << "-- PLAYER 2 -- " << std::endl;
        }
        else
        {
            std::cout << "-- PLAYER -- " << std::endl;
        }
        player2 = create_player();
    }
}

/* FONCTIONS 2 PLAYERS MODE */
void two_players_round(std::array<std::array<char, 3>, 3>& board, const Player& player1, const Player& player2)
{
    /*
    pré-conditions : 
        > board : ref of array of arrays of char
        > player1, player 2 : const ref struct Player
    post-condition : aucune
    effet de bord : modifie les elts de board en fonction des coups des joueurs et affiche le plateau de jeu après chaque coup
    note : je considère un "round" comme les 2 joueurs qui jouent leur coup pas juste un joueur
    */
    
    player_move(board, player1);
    draw_game_board(board);

    if (test_victory(board, player1, player2) == "none") /*player2 joue seulement si le coup de player1 n'était pas gagnant*/
    {
        player_move(board, player2);
        draw_game_board(board);
    }
}

void two_players_mode()
{
    /* gère le mode de jeu 2 joueurs */

    /* création des joueurs : */
    std::cout << "\n";
    std::cout << "-- PLAYER 1 --" << std::endl;
    std::cout << "\n";
    Player player1 { create_player() };
    std::cout << "-- PLAYER 2 -- " << std::endl;
    Player player2 { create_player() };

    same_symbol_verification(player1, player2);

    std::cout << "\n";
    std::cout << "---------------------" << std::endl;
    std::cout << "\n";

    std::cout << player1.name << " will start" << std::endl;
    std::cout << "\n";

    std::array<std::array<char, 3>, 3> board {init_board()};
    draw_game_board(board);
    
    while (test_victory(board, player1, player2) == "none" && !possible_moves(board).empty()) /* le jeu continue tant qu'il n'y a pas de gagnant et tant que le plateau n'est pas plein */
    {
        two_players_round(board, player1, player2);
    }

    winner_announcement(board, player1, player2);
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

    std::vector<std::array<int, 2>> empty_squares {possible_moves(board)};

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
    /* gère le mode IA simple */

    /* création des joueurs : */
    std::cout << "-- PLAYER -- : " << std::endl;
    Player player { create_player() };
    Player AI { "AI", 'A' };

    same_symbol_verification(AI, player);

    std::array<std::array<char, 3>, 3> board {init_board()};
    draw_game_board(board);
    
    while (test_victory(board, player, AI) == "none" && !possible_moves(board).empty())
    {
        AI_round(board, player, AI);
    }

    winner_announcement(board, player, AI);
}

/* AMÉLIORATIONS - IA avec algorithme d'élagage alpha-bêta */
int get_score(std::array<std::array<char, 3>, 3>& board, const Player& player, const Player& AI)
{
    /*
    pré-conditions : 
        > board : ref of array of arrays of char
        > player, AI : const ref struct Player
    post-condition : renvoie un score (int) de 
        > 1 si l'IA gagne
        > -1 si l'IA perd
        > 0 si égalité
        > -1000 (symbolise moins l'infini) si pas encore de gagnant

    >> cette fonction sert de fonction d'évaluation dans l'algorithme d'élagage alpha-bêta
    */

    if (test_victory(board, AI, player) == AI.name)
    {
        return 1;
    }

    else if (test_victory(board, AI, player) == player.name)
    {
        return -1;
    }

    else if (test_victory(board, AI, player) == "none" && possible_moves(board).empty())
    {
        return 0;
    }

    return -1000; /* la partie continue */
}

int alpha_beta_pruning(std::array<std::array<char, 3>, 3>& board, const Player& player, const Player& AI, int alpha, int beta, bool AI_turn)
{
    /*
    pré-conditions : 
        > board : ref of array of arrays of char
        > player, AI : const ref struct Player
        > alpha, beta : int, représentent respectivement la meilleure valeur garantie pour l'IA et pour le joueur
        > AI_turn : bool 
    post-condition : renvoie le meilleur score possible pour l'IA selon l'algorithme en fonction de l'état du jeu

    >> implémentation de l'algorithme pour 2 joueurs
    */

    int score = get_score(board, player, AI);

    if (score != -1000) /* cas de base : si on a atteint un état final ie une feuille de l'arbre alors on s'arrête là*/
    {
        return score;
    }

    if (AI_turn)
    {
        int best_score {-1000}; /* valeur très petite pour représenter moins l'infini */

        std::vector<std::array<int, 2>> empty_squares {possible_moves(board)};

        for (const std::array<int, 2>& square : empty_squares)  /* pour chaque coup possible pour l'IA :*/
        {
            board[square[0]][square[1]] = AI.symbol; /* on teste le coup */
            
            best_score = std::max(best_score, alpha_beta_pruning(board, player, AI, alpha, beta, false)); /* on regarde si ce coup maximise les chances de gagner en rappelant la fonction sur le tour du joueur */
            board[square[0]][square[1]] = '.';  /* on annule le coup, c'était juste un test */

            if (best_score >= beta) /* le score de l'IA après ce coup est supérieur à la meilleure valeur garantie de score pour le joueur*/
            {
                return best_score; /* alors, on s'arrête là */
            }

            alpha = std::max(alpha, best_score); /* si ce n'est pas le cas, on regarde si le score après ce coup est mieux que la meilleure valeur de score garantie jusqu'à présent pour l'IA */
        }

        return best_score;
    }

    else /* si c'est au joueur de jouer : */
    {
        int best_score {1000}; /* valeur très grande pour représenter plus l'infini*/

        std::vector<std::array<int, 2>> empty_squares {possible_moves(board)};

        for (const std::array<int, 2>& square : empty_squares)  /* pour chaque coup possible pour player */
        {
            board[square[0]][square[1]] = player.symbol; /* on teste le coup */
            
            best_score = std::min(best_score, alpha_beta_pruning(board, player, AI, alpha, beta, true));
            board[square[0]][square[1]] = '.';  /* on annule le coup, c'était juste un test */

            if (best_score <= alpha)
            {
                return best_score;
            }

            beta = std::min(beta, best_score);
        }

        return best_score;
    }
}

std::array<int, 2> find_best_AI_move(std::array<std::array<char, 3>, 3>& board, const Player& player, const Player& AI)
{
    /*
    pré-conditions : 
        > board : ref of array of arrays of char
        > player, AI : const ref struct Player
    post-condition : renvoie le meilleur coup possible pour l'IA en fonction de l'état du jeu, selon l'algorithme, et sous forme de array of 2 int (représente les indices de la case)
    */
    
    int best_score {-1000}; /* toujours pour représenter moins l'infini */

    std::array<int, 2> best_move {};

    std::vector<std::array<int, 2>> empty_squares {possible_moves(board)};

    for (const std::array<int, 2>& square : empty_squares) /* pour chaque coup possible */
    {
        board[square[0]][square[1]] = AI.symbol; /* on teste le coup */
        int score = alpha_beta_pruning(board, player, AI, -1000, 1000, false); /* on calcule le score avec le meilleur score possible avec ce coup */
        board[square[0]][square[1]] = '.';

        if (score > best_score) /* si ce score est meilleur que le meilleure score qu'on a trouvé jusqu'à présent alors on met à jour le meilleur score et donc le meilleur coup associé */
        {
            best_score = score;
            best_move = square;
        }
    }

    return best_move;
}

void upgraded_AI_round(std::array<std::array<char, 3>, 3>& board, const Player& player, const Player& AI)
{
    /*
    pré-conditions : 
        > board : ref of array of arrays of char
        > player, AI : const ref struct Player
    post-condition : aucune
    effet de bord : modifie board en fonction des coups choisis et affiche du texte
    */

    player_move(board, player);
    draw_game_board(board);

    /*AI joue seulement si le coup de player n'était pas gagnant*/
    if (test_victory(board, player, AI) == "none")
    {
        /* l'IA joue le meilleur coup possible*/
        std::array<int, 2> best_move { find_best_AI_move(board, player, AI) };
        board[best_move[0]][best_move[1]] = AI.symbol;

        std::cout << " " << std::endl;
        std::cout << "AI move : " << std::endl;
        std::cout << " " << std::endl;
        draw_game_board(board);
    }
}

void upgraded_AI_mode()
{
    /* gère le mode AI avancé */

    /* création des joueurs : */

    std::cout << "In this mode you will battle against an AI. Please note that the AI's symbol is 'A' so don't use the same one !" << std::endl;
    std::cout << "\n";

    std::cout << "-- PLAYER -- : " << std::endl;
    Player player { create_player() };
    Player AI { "AI", 'A' };

    same_symbol_verification(AI, player);

    std::array<std::array<char, 3>, 3> board {init_board()};
    draw_game_board(board);
    
    while (test_victory(board, player, AI) == "none" && !possible_moves(board).empty())
    {
        upgraded_AI_round(board, player, AI);
    }

    winner_announcement(board, player, AI);
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
            upgraded_AI_mode(); /* MODIFIER ICI pour le TYPE d'IA : simple (random) ou upgraded (alpha beta pruning) */
            /* AI_mode();*/ /* mode IA random */
            break;
    }
}