#include <cmatrix.h>

#include <stdlib.h>
#include <string.h>

inline CMatrix cmatrix_init(size_t l, size_t c) {
  return (CMatrix){l, c, malloc(l * c)};
}

CMatrix cmatrix_init_val(size_t l, size_t c, char val) {
  CMatrix ret = {l, c, malloc(l * c)};
  if(! ret.m_data)
    return ret;
  memset(ret.m_data, val, l * c);
  return ret;  
}

inline void cmatrix_set_all(CMatrix cm, char val) {
  memset(cm.m_data, val, cm.m_lines * cm.m_columns + 1);
}

inline void cmatrix_set_line(CMatrix cm, size_t l, char val) {
  memset(cmatrix_access(cm, l, 0), val, cm.m_columns);
}

void cmatrix_set_column(CMatrix cm, size_t c, char val) {
  for(size_t l = 0; l < cm.m_lines; l += 1)
    *cmatrix_access(cm, l, c) = val;
}

inline char * cmatrix_access(CMatrix const cm, size_t l, size_t c) {
  return cm.m_data + ((ssize_t)l * cm.m_columns + 1) + c;
}

inline void cmatrix_free(CMatrix cm) {
  free(cm.m_data);
}

inline char cmatrix_is_null(CMatrix const cm) {
  return cm.m_data == NULL;
}
