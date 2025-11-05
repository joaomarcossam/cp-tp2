#ifndef INIT_PARSER_H
#define INIT_PARSER_H

#include <stdint.h>
#include <sys/types.h>

struct __size_t_pair {
  size_t x, y;
};

typedef struct __size_t_pair SizePair;

struct __init_info_t {
  uint32_t m_gens;
  size_t m_lines, m_columns;
  ssize_t m_num_alive;
  SizePair * m_alive_index;
};

typedef struct __init_info_t InitInfo;

InitInfo init_parser_parse(char const * const path);
void init_parser_free(InitInfo info);

#define IS_NULL_INIT_INFO(i) (i.m_alive_index == NULL)
#endif // INIT_PARSER_H