#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

#define MATRIX_HEADER_DEFS(T) \
struct __##T##_matrix_t { \
  T * const m_data; \
  size_t m_lines, m_columns; \
}; \
typedef struct __##T##_matrix_t T##_matrix_t; \
T##_matrix_t T##_matrix_init(size_t const lines, size_t const columns); \
T##_matrix_t T##_matrix_init_val(size_t const lines, size_t const columns, T const val); \
T T##_matrix_get_val(T##_matrix_t const m, size_t const line, size_t const column); \
void T##_matrix_set_val(T##_matrix_t m, size_t const line, size_t const column, T const value); \
void T##_matrix_free(T##_matrix_t ptr_to_auto_var); \
void T##_matrix_set_line(T##_matrix_t m, size_t const line, T const value); \
void T##_matrix_set_column(T##_matrix_t m, size_t const column, T const value); \
void T##_matrix_set_all(T##_matrix_t m, T const value); \

#define MATRIX_HEADER_IMPL(T) \
inline T##_matrix_t T##_matrix_init(size_t const lines, size_t const columns) { \
  return (T##_matrix_t) { \
    .m_data = malloc(lines * columns * sizeof(T)), \
    .m_lines = lines, \
    .m_columns = columns}; \
} \
T##_matrix_t T##_matrix_init_val(size_t const lines, size_t const columns, T const val) { \
  T##_matrix_t ret = { \
    .m_data = malloc(lines * columns * sizeof(T)), \
    .m_lines = lines, \
    .m_columns = columns}; \
  if(IS_NULL_MATRIX(ret)) \
    return ret; \
  for(ssize_t i = 0; i < (ssize_t)lines * columns; i += 1) \
    ret.m_data[i] = val; \
  return ret; \
} \
inline T T##_matrix_get_val(T##_matrix_t const m, size_t const line, size_t const column) { \
  return *(m.m_data + ((ssize_t)line * m.m_columns + 1) + column); \
} \
\
inline void T##_matrix_set_val(T##_matrix_t m, size_t const line, size_t const column, T const value) { \
  *(m.m_data + ((ssize_t)line * m.m_columns + 1) + column) = value; \
} \
inline void T##_matrix_set_line(T##_matrix_t m, size_t const line, T const value) { \
  for(size_t ci = 0; ci < m.m_columns; ci += 1) \
    T##_matrix_set_val(m, line, ci, value); \
} \
inline void T##matrix_set_column(T##_matrix_t m, size_t const column, T const value) { \
  for(size_t li = 0; li < m.m_lines; li += 1) \
    T##_matrix_set_val(m, li, column, value); \
} \
inline void T##_matrix_set_all(T##_matrix_t m, const T value) { \
  for(size_t li = 0; li < m.m_lines; li += 1) \
    for(size_t ci = 0; ci < m.m_columns; ci += 1) \
      T##_matrix_set_val(m, li, ci, value); \
} \
inline void T##_matrix_free(T##_matrix_t ptr_to_auto_var) { \
  free(ptr_to_auto_var.m_data); \
} \

#define IS_NULL_MATRIX(M) (M.m_data == NULL)
#endif // MATRIX_H