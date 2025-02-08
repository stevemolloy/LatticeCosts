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

typedef struct {
  size_t D1, D2, D3;
  size_t Q1, Q2, Q3, Q4, Q5, Q6;
  size_t R1, R2, R3;
  size_t S1, S2, S3, S4, S5, S6;
  size_t O1, O2, O3;
  size_t T1, T2;
  size_t S1_combined, S3_combined, S6_combined;
} FamilyLocations;

typedef struct {
  char *name;
  double D1, D2, D3;
  double Q1, Q2, Q3, Q4, Q5, Q6;
  double R1, R2, R3;
  double S1, S2, S3, S4, S5, S6;
  double O1, O2, O3;
  double T1, T2;
  double S1_combined, S3_combined, S6_combined;
} FamilyDefn;

typedef struct {
  size_t capacity;
  size_t length;
  FamilyDefn *data;
  FamilyLocations fam_locs;
} FamilyDefns;

Matrix get_double_array_field(mxArray *ma, const char *fieldname);
void print_matrix(Matrix mat);

int get_lattice_summaries(const char *latt_summ_filename, const char *sheetname, FamilyDefns *fam_defns);
int print_sheet_name(const char *name, void *callbackdata);
int get_fam_locs_callback(size_t row, size_t col, const char* value, void* callbackdata);
int get_fam_strengths_callback(size_t row, size_t col, const char* value, void* callbackdata);
int row_callback(size_t row, size_t maxcol, void* callbackdata);

#endif // !_EXE_LIB_H

