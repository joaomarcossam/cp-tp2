#ifndef SEQUENTIAL_LIFE_GAME_H
#define SEQUENTIAL_LIFE_GAME_H

#include <cmatrix.h>
#include <init_parser.h>
#include <stdbool.h>


CMatrix life_game_start(InitInfo const init_configs);
bool life_game_advance(CMatrix current_state, uint32_t const gens);
void life_game_print(CMatrix current_state);

CMatrix gen_neighbors_matrix(CMatrix const state);
void update_neighbors(CMatrix neighbors_matrix);


/* Testing */
void print_info(InitInfo info);
void matrix_print(const CMatrix m);

#endif // SEQUENTIAL_LIFE_GAME_H