#ifndef SEQUENTIAL_LIFE_GAME_H
#define SEQUENTIAL_LIFE_GAME_H

#include <bool_matrix.h>
#include <init_parser.h>
#include <stdbool.h>

bool_matrix_t life_game_start(InitInfo const init_configs);
bool life_game_advance(bool_matrix_t current_state, uint32_t const gens);
void life_game_print(bool_matrix_t current_state);

#endif // SEQUENTIAL_LIFE_GAME_H