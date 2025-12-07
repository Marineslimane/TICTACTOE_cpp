#pragma once 

#include <array>

#include "Player.hpp"

/* variables globales définies dans Game.cpp */
inline constexpr int number_rows {3};
inline constexpr int number_columns {3};
inline constexpr int size_board {number_rows*number_columns};

void draw_game_board(const std::array<std::array<char, number_columns>, number_rows>& board);

std::array<std::array<char, number_columns>, number_rows> init_board();

std::string test_victory(std::array< std::array<char, number_columns>, number_rows>& board, Player player1, Player player2);

void two_players_round(std::array<std::array<char, number_columns>, number_rows>& board, Player player1, Player player2);

void two_players_mode();

void AI_mode();



void start_menu();