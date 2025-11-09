
#ifndef CMATRIX_H
#define CMATRIX_H

#include <sys/types.h>

typedef struct CMatrix {
  size_t m_lines, m_columns;
  char * m_data;
} CMatrix;

CMatrix cmatrix_init(size_t l, size_t c);
CMatrix cmatrix_init_val(size_t l, size_t c, char val);
void cmatrix_set_all(CMatrix cm, char val);
void cmatrix_set_line(CMatrix cm, size_t l, char val);
void cmatrix_set_column(CMatrix cm, size_t c, char val);
char * cmatrix_access(CMatrix const cm, size_t l, size_t c);
void cmatrix_free(CMatrix cm);
char cmatrix_is_null(CMatrix const cm);

#endif // CMATRIX_H
