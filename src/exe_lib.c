#include <stdio.h>

#include "exe_lib.h"
#include "matrix.h"

Matrix get_double_array_field(mxArray *ma, const char *fieldname) {
  Matrix retval = {0};

  mxArray *array = mxGetField(ma, 0, fieldname);
  assert(mxIsDouble(array) && "This function should only be called on fields containing an array of doubles");
  retval.m = mxGetM(array);
  retval.n = mxGetN(array);
  retval.data = mxGetDoubles(array);

  return retval;
}

void print_matrix(Matrix mat) {
  for (int i=0; i<mat.m; i++) {
    for (int j=0; j<mat.n; j++) {
      printf("%lf, ", mat.data[i*mat.n + j]);
    }
    printf("\n");
  }
}

