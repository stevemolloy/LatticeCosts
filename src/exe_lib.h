#ifndef _EXE_LIB_H
#define _EXE_LIB_H

#include "matrix.h"

#define RETURN_DEFER(VAL)    \
  do {                       \
    retval=(VAL);            \
    goto dealloc_and_return; \
  } while (0)

#define REPORT_AND_DIE(err_msg, ...)         \
  do {                                       \
    fprintf(stderr, (err_msg), __VA_ARGS__); \
    RETURN_DEFER(1);                         \
  } while (0)

typedef struct {
  double *data;
  int m;
  int n;
} Matrix;

Matrix get_double_array_field(mxArray *ma, const char *fieldname);
void print_matrix(Matrix mat);

#endif // !_EXE_LIB_H

