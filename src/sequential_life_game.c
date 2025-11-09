#include <sequential_life_game.h>
#include <stdio.h>

#define lives(_C) ( (_C) == 1)

static void set_neighbors_matrix(CMatrix const state, CMatrix nm) {
  cmatrix_set_all(nm, 0);
  char * const fline_nm = cmatrix_access(nm, 0, 0);
  char * const fline_state = cmatrix_access(state, 0, 0);
  char * const sline_nm = cmatrix_access(nm, 1, 0);
  char * const sline_state = cmatrix_access(state, 1, 0);
  char * const pnline_nm = cmatrix_access(nm, nm.m_lines - 2, 0);
  char * const pnline_state = cmatrix_access(state, state.m_lines - 2, 0);
  char * const lline_nm = cmatrix_access(nm, nm.m_lines - 1, 0);
  char * const lline_state = cmatrix_access(state, state.m_lines - 1, 0);
  for(size_t ci = 1; ci < state.m_columns - 1; ci += 1) {
    if(fline_state[ci]) {
      sline_nm[ci - 1] += 1;
      sline_nm[ci    ] += 1;
      sline_nm[ci + 1] += 1;
      fline_nm[ci - 1] += 1;
      fline_nm[ci + 1] += 1;
    }
    if(lline_state[ci]) {
      pnline_nm[ci - 1] += 1;
      pnline_nm[ci    ] += 1;
      pnline_nm[ci + 1] += 1;
      lline_nm[ci - 1] += 1;
      lline_nm[ci + 1] += 1;
    }
  }
  for(size_t li = 1; li < state.m_lines - 1; li += 1) {
    if(*cmatrix_access(state, li, 0)) {
      *cmatrix_access(nm, li - 1, 1) = *cmatrix_access(nm, li - 1, 1) + 1;
      *cmatrix_access(nm, li    , 1) = *cmatrix_access(nm, li    , 1) + 1;
      *cmatrix_access(nm, li + 1, 1) = *cmatrix_access(nm, li + 1, 1) + 1;
      *cmatrix_access(nm, li - 1, 0) = *cmatrix_access(nm, li - 1, 0) + 1;
      *cmatrix_access(nm, li + 1, 0) = *cmatrix_access(nm, li + 1, 0) + 1;
    }
    if(*cmatrix_access(state, li, state.m_columns - 1)) {
      *cmatrix_access(nm, li - 1, state.m_columns - 2) = *cmatrix_access(nm, li - 1, state.m_columns - 2) + 1;
      *cmatrix_access(nm, li    , state.m_columns - 2) = *cmatrix_access(nm, li    , state.m_columns - 2) + 1;
      *cmatrix_access(nm, li + 1, state.m_columns - 2) = *cmatrix_access(nm, li + 1, state.m_columns - 2) + 1;
      *cmatrix_access(nm, li - 1, state.m_columns - 1) = *cmatrix_access(nm, li - 1, state.m_columns - 1) + 1;
      *cmatrix_access(nm, li + 1, state.m_columns - 1) = *cmatrix_access(nm, li + 1, state.m_columns - 1) + 1;
    }
  }
  if(fline_state[0]) {
    fline_nm[1] += 1;
    sline_nm[1] += 1;
    sline_nm[0] += 1;
  }
  if(fline_state[state.m_columns - 1]) {
    fline_nm[nm.m_columns - 2] += 1;
    sline_nm[nm.m_columns - 2] += 1;
    sline_nm[nm.m_columns - 1] += 1;
  }
  if(lline_state[0]) {
    lline_nm[1] += 1;
    pnline_nm[1] += 1;
    pnline_nm[0] += 1;
  }
  if(lline_state[state.m_columns - 1]) {
    lline_nm[nm.m_columns - 2] += 1;
    pnline_nm[nm.m_columns - 2] += 1;
    pnline_nm[nm.m_columns - 1] += 1;
  }
  char *line_ptr_nm, *line_ptr_state, *line_before_nm, *line_next_nm;
  for(size_t li = 1; li < state.m_lines - 1; li += 1) {
    line_ptr_nm = cmatrix_access(nm, li, 0);
    line_ptr_state = cmatrix_access(state, li, 0);
    line_before_nm = cmatrix_access(nm, li - 1, 0);
    line_next_nm = cmatrix_access(nm, li + 1, 0);
    for(size_t ci = 1; ci < state.m_columns - 1; ci += 1) {
      if(! line_ptr_state[ci])
        continue;
      line_ptr_nm[ci - 1] += 1;
      line_ptr_nm[ci + 1] += 1;
      line_before_nm[ci + 1] += 1;
      line_before_nm[ci    ] += 1;
      line_before_nm[ci - 1] += 1;
      line_next_nm[ci    ] += 1;
      line_next_nm[ci + 1] += 1;
      line_next_nm[ci - 1] += 1;
    }
  }
}


/*     0  1  2  3
    0 [ ][ ][ ][ ]
    1 [ ][ ][ ][ ]
    2 [ ][ ][ ][ ]
    3 [ ][ ][ ][ ]

    */

void matrix_print(const CMatrix m){
    /*
    For Testing
    */
    
    printf("\033[36m  ║ \033[0m");

    for(size_t i = 0; i < m.m_columns; i++)
        printf("\033[33;1m%-2lu \033[0m", i);
        printf("\n");

    printf("\033[36m==•\033[0m");

    for(size_t i = 0; i < m.m_columns*3; i++)
        printf("\033[36m=\033[0m");
        printf("\n");

    for(size_t i = 0; i < m.m_lines; i++){
        printf("\033[33;1m%lu\033[0;36m ║\033[0m", i);
        for(int j = 0; j < m.m_columns; j++){
            printf(" %-2d", *cmatrix_access(m, i, j));
        }
        printf("\n");
    }
}

void print_info(InitInfo info){
    /*
    For Testing
    */
  printf(
    "• \033[36mInfo\033[0m\nGens: \033[15G%d\nLines: \033[15G%ld\nColumns: \033[15G%ld\nAlive Cells: \033[15G%ld\n",
    info.m_gens, info.m_lines, info.m_columns, info.m_num_alive
  );
  if(info.m_num_alive){
    printf("\n• Pairs:\n");
    for(int i = 0; i < info.m_num_alive; i++){
    printf(
      "  - (%2ld ,%2ld )\n",
      info.m_alive_index[i].x,
      info.m_alive_index[i].y
    );
    }
  }

  else{
    printf("\n→ No alive cells.\n");
  }
}

void print_output(InitInfo info, CMatrix matrix){
    printf("N_GEN:%d\nL:%ld\nC:%ld\nN:%ld\n", info.m_gens, info.m_lines, info.m_columns, info.m_lines);

    for(size_t i = 0; i < matrix.m_lines; i++){
        for(size_t j = 0; j < matrix.m_columns; j++){
            if(*cmatrix_access(matrix, i, j) == 1){
                printf("%ld, %ld\n", i, j);
            }
        }
    }
}

CMatrix life_game_start(InitInfo const init_configs){
    printf("before init cmatrix\n");
    CMatrix state = cmatrix_init_val(init_configs.m_lines, init_configs.m_columns, 0);
    
    printf("before first val sets\n");
    for(ssize_t i = 0; i < init_configs.m_num_alive; i++){
        *cmatrix_access(state, init_configs.m_alive_index[i].x, init_configs.m_alive_index[i].y) = 1;
    }
    
    printf("\n• \033[36;1mStart State\033[0m\n\n");
    matrix_print(state);
    life_game_advance(state, init_configs.m_gens);

    printf("\n• \033[36;1mEnd State\033[0m\n\n");
    matrix_print(state);
    printf("\n");

    //print_output(init_configs, state);
    
    return state;
}

bool life_game_advance(CMatrix current_state, uint32_t const gens){
    CMatrix neighbors = cmatrix_init(current_state.m_lines, current_state.m_columns);
    
    for(uint32_t g = 0; g< gens; g++){    
        set_neighbors_matrix(current_state, neighbors);

        size_t i, j;
        for(i = 0; i < current_state.m_lines; i++){
            for(j=0; j < current_state.m_columns; j++){
                char neighbors_count = *cmatrix_access(neighbors, i, j);
                char current_cell = *cmatrix_access(current_state, i, j);
                if(neighbors_count < 2 || neighbors_count > 3) *cmatrix_access(current_state, i, j) = 0;
                if(neighbors_count == 3) *cmatrix_access(current_state, i, j) = 1;
            }
        }
    }
    cmatrix_free(neighbors);
}