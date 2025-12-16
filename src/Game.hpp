#pragma once 

#include <array>

#include "Player.hpp"


void draw_game_board(const std::array<std::array<char, 3>, 3>& board);

std::array<std::array<char, 3>, 3> init_board();

std::string test_victory(const std::array< std::array<char, 3>, 3>& board, const Player& player1, const Player& player2);

/* fonctions 2 players mode */
void player_move(std::array<std::array<char, 3>, 3>& board, const Player& player);

void two_players_round(std::array<std::array<char, 3>, 3>& board, const Player& player1, const Player& player2);

void two_players_mode();

/* fonction AI mode */
void unbiased_random_move(std::array<std::array<char, 3>, 3>& board, const Player& AI);

void AI_round(std::array<std::array<char, 3>, 3>& board, const Player& player, const Player& AI);

void AI_mode();


void start_menu();