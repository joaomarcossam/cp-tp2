#include <bits/posix1_lim.h>
#include <init_parser.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

/*
struct __init_info_t {
  uint32_t m_gens;
  size_t m_lines, m_columns;
  ssize_t m_num_alive;
  SizePair * const m_alive_index;
};

N_GEN:10
L:10
C:10
N:3
0,1
1,1
2,5

*/

static char * str_aux_copy_until(char const * const str, char const character, size_t * char_read) {
  size_t buffer_insert = 0;
  size_t buffer_cap = 16;
  char * buffer = malloc(buffer_cap);
  char * temp_ptr = NULL;
  if(! buffer)
    return NULL;
  for(size_t i = 0; str[i] != '\0'; i += 1) {
    if(str[i] == character)
      break;
    if(buffer_insert == buffer_cap) {
      buffer_cap *= 2;
      temp_ptr = realloc(buffer, buffer_cap);
      if(! temp_ptr) {
        free(buffer);
        return NULL;
      }
      buffer = temp_ptr;
    }
    buffer[buffer_insert++] = str[i];
  }
  if(buffer_insert == buffer_cap) {
    temp_ptr = realloc(buffer, buffer_cap + 1);
    if(! temp_ptr) {
      free(buffer);
      return NULL;
    }
    buffer = temp_ptr;
  }
  buffer[buffer_insert] = '\0';
  *char_read = buffer_insert;
  return buffer;
}

static inline ssize_t cast_ssize(char const * const str) {
  char * temp;
  unsigned long long ret = strtoull(str, &temp, 10);
  if(ret == ULLONG_MAX
    || temp == str
    || *temp != '\0')
    return SSIZE_MAX;
  return ret;
}

static inline size_t cast_size(char const * const str) {
  char * temp;
  unsigned long ret = strtoul(str, &temp, 10);
  if(ret == ULONG_MAX
    || temp == str
    || *temp != '\0')
    return SIZE_MAX;
  return ret;
}

#define PARSE_ERROR (InitInfo){0, 0, 0, 0, NULL}
#define RET(val) do { \
  free(retval.m_alive_index); \
  retval = val; \
  goto Cleanup; \
} while(false)

InitInfo init_parser_parse(char const * const path) {
  FILE * init_file = fopen(path, "r");
  if(! init_file)
    return PARSE_ERROR;
  InitInfo retval         = PARSE_ERROR;
  size_t temp_size        = 0;
  ssize_t temp_ssize      = 0;
  char * temp_char_ptr    = NULL;
  char * line_read        = NULL; //NEED_FREE
  char * header_param_str = NULL; //NEED_FREE
  char * header_arg_str   = NULL; //NEED_FREE
  char * first_size_pair  = NULL; //NEED_FREE
  char * second_size_pair = NULL; //NEED_FREE
  bool ngen_set           = false;
  bool l_set              = false;
  bool c_set              = false;
  bool n_set              = false;

  for(char op_line = 0; op_line < 4; op_line += 1) {
    if(getline(&line_read, &temp_size, init_file) == -1)
      RET(PARSE_ERROR);
    free(header_param_str);
    free(header_arg_str);
    header_param_str = str_aux_copy_until(line_read, ':', &temp_size);
    header_arg_str = str_aux_copy_until(line_read + temp_size + 1, '\n', &temp_size);
    if(! header_param_str || ! header_arg_str)
      RET(PARSE_ERROR);
    if(! ngen_set && strncmp(header_param_str, "N_GEN", 5) == 0) {
      if((temp_ssize = cast_size(header_arg_str)) == SIZE_MAX)
        RET(PARSE_ERROR);
      retval.m_gens = temp_ssize;
      ngen_set = true;
    }
    else if(! l_set && strncmp(header_param_str, "L", 2) == 0) {
      if((temp_ssize = cast_size(header_arg_str)) == SIZE_MAX)
        RET(PARSE_ERROR);
      retval.m_lines = temp_ssize;
      l_set = true;
    }
    else if(! c_set && strncmp(header_param_str, "C", 2) == 0) {
      if((temp_ssize = cast_size(header_arg_str)) == SIZE_MAX)
        RET(PARSE_ERROR);
      retval.m_columns = temp_ssize;
      c_set = true;
    }
    else if(! n_set && strncmp(header_param_str, "N", 2) == 0) {
      if((temp_ssize = cast_ssize(header_arg_str)) == SSIZE_MAX)
        RET(PARSE_ERROR);
      retval.m_num_alive = temp_ssize;
      n_set = true;
    }
    else
      RET(PARSE_ERROR);
  }

  retval.m_alive_index = malloc(sizeof(SizePair) * retval.m_num_alive);
  if(! retval.m_alive_index)
    RET(PARSE_ERROR);
  for(uint32_t i = 0; i < retval.m_num_alive; i += 1) {
    if(getline(&line_read, &temp_size, init_file) == -1 && i != retval.m_num_alive - 1)
      RET(PARSE_ERROR);
    free(first_size_pair);
    free(second_size_pair);
    first_size_pair = str_aux_copy_until(line_read, ',', &temp_size);
    second_size_pair = str_aux_copy_until(line_read + temp_size + 1, '\n', &temp_size);
    if(! first_size_pair || ! second_size_pair)
      RET(PARSE_ERROR);
    if((retval.m_alive_index[i].x = cast_size(first_size_pair)) == SIZE_MAX)
      RET(PARSE_ERROR);
    if((retval.m_alive_index[i].y = cast_size(second_size_pair)) == SIZE_MAX)
      RET(PARSE_ERROR);
  }

  Cleanup:
  fclose(init_file);
  free(line_read);
  free(header_param_str);
  free(header_arg_str);
  free(first_size_pair);
  free(second_size_pair);
  return retval;
}
#undef PARSE_ERROR
#undef RET

void init_parser_free(InitInfo info) {
  free(info.m_alive_index);
}