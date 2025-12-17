#pragma once 

#include <array>
#include <vector>

#include "Player.hpp"


/* FONCTIONS GÉNÉRALES */
void draw_game_board(const std::array<std::array<char, 3>, 3>& board);

std::array<std::array<char, 3>, 3> init_board();

std::string test_victory(const std::array< std::array<char, 3>, 3>& board, const Player& player1, const Player& player2);

void player_move(std::array<std::array<char, 3>, 3>& board, const Player& player);

std::vector<std::array<int, 2>> possible_moves(std::array<std::array<char, 3>, 3>& board);

void winner_announcement(const std::array<std::array<char, 3>, 3>& board, Player& player1, Player& player2);

void same_symbol_verification(const Player& player1, Player& player2);


/* FONCTIONS 2 PLAYERS MODE */
void two_players_round(std::array<std::array<char, 3>, 3>& board, const Player& player1, const Player& player2);

void two_players_mode();


/* FONCTIONS AI MODE (random) */
void unbiased_random_move(std::array<std::array<char, 3>, 3>& board, const Player& AI);

void AI_round(std::array<std::array<char, 3>, 3>& board, const Player& player, const Player& AI);

void AI_mode();


/* AMÉLIORATIONS - IA avec algorithme d'élagage alpha-bêta */
int get_score(std::array<std::array<char, 3>, 3>& board, const Player& player, const Player& AI);

int alpha_beta_pruning(std::array<std::array<char, 3>, 3>& board, const Player& player, const Player& AI, int alpha, int beta, bool AI_turn);

std::array<int, 2> find_best_AI_move(std::array<std::array<char, 3>, 3>& board, const Player& player, const Player& AI);

void upgraded_AI_round(std::array<std::array<char, 3>, 3>& board, const Player& player, const Player& AI);

void upgraded_AI_mode();


/* FONCTION DE DÉMARRAGE */
void start_menu();