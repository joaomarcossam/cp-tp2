#include <stdio.h>
#include <sequential_life_game.h>
#include <string.h>


int is_null(InitInfo info){
  return (
    info.m_gens == 0 &&
    info.m_lines == 0 &&
    info.m_columns == 0 &&
    info.m_num_alive == 0 &&
    info.m_alive_index == NULL
  );
}

int main(const int argc, const char** argv) {
  printf("Main\n");

  if(argc != 2){
    printf("Expected one file as parameter.\n");
    return -1;
  }

  InitInfo info = init_parser_parse(argv[1]);
  
  if(is_null(info)){
    printf("Failed to parse info\n");
    return -1;
  }

  print_info(info);
  printf("\n");

  life_game_start(info);

  return 0;
}
