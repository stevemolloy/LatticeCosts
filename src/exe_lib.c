#include <stdio.h>
#include <string.h>

#include <xlsxio_read.h>
#include "matrix.h"

#include "exe_lib.h"
#include "sdm_lib.h"

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

int print_sheet_name(const char *name, void *callbackdata) {
  (void)callbackdata;
  printf("name = %s\n", name);
  return 0;
}

int get_lattice_summaries(const char *latt_summ_filename, const char *sheetname, FamilyDefns *fam_defns) {
  xlsxioreader xlsxioread = xlsxioread_open(latt_summ_filename);
  if (xlsxioread == NULL)
    return -1;

  xlsxioread_process(xlsxioread, sheetname, XLSXIOREAD_SKIP_NONE, &get_fam_locs_callback, &row_callback, &(fam_defns->fam_locs));
  xlsxioread_process(xlsxioread, sheetname, XLSXIOREAD_SKIP_NONE, &get_fam_strengths_callback, &row_callback, fam_defns);
  xlsxioread_close(xlsxioread);

  return 0;
}

int get_fam_locs_callback(size_t row, size_t col, const char* value, void* callbackdata) {
  FamilyLocations *fam_locs = (FamilyLocations*)callbackdata;

  if (value == NULL) return 0;
  if (row != 2) return 0;

  if      (strcmp(value, "D1")==0 && fam_locs->D1 == 0) fam_locs->D1 = col;
  else if (strcmp(value, "D2")==0 && fam_locs->D2 == 0) fam_locs->D2 = col;
  else if (strcmp(value, "D3")==0 && fam_locs->D3 == 0) fam_locs->D3 = col;
  else if (strcmp(value, "Q1")==0 && fam_locs->Q1 == 0) fam_locs->Q1 = col;
  else if (strcmp(value, "Q2")==0 && fam_locs->Q2 == 0) fam_locs->Q2 = col;
  else if (strcmp(value, "Q3")==0 && fam_locs->Q3 == 0) fam_locs->Q3 = col;
  else if (strcmp(value, "Q4")==0 && fam_locs->Q4 == 0) fam_locs->Q4 = col;
  else if (strcmp(value, "Q5")==0 && fam_locs->Q5 == 0) fam_locs->Q5 = col;
  else if (strcmp(value, "Q6")==0 && fam_locs->Q6 == 0) fam_locs->Q6 = col;
  else if (strcmp(value, "R1")==0 && fam_locs->R1 == 0) fam_locs->R1 = col;
  else if (strcmp(value, "R2")==0 && fam_locs->R2 == 0) fam_locs->R2 = col;
  else if (strcmp(value, "R3")==0 && fam_locs->R3 == 0) fam_locs->R3 = col;
  else if (strcmp(value, "S1")==0 && fam_locs->S1 == 0) fam_locs->S1 = col;
  else if (strcmp(value, "S2")==0 && fam_locs->S2 == 0) fam_locs->S2 = col;
  else if (strcmp(value, "S3")==0 && fam_locs->S3 == 0) fam_locs->S3 = col;
  else if (strcmp(value, "S4")==0 && fam_locs->S4 == 0) fam_locs->S4 = col;
  else if (strcmp(value, "S5")==0 && fam_locs->S5 == 0) fam_locs->S5 = col;
  else if (strcmp(value, "S6")==0 && fam_locs->S6 == 0) fam_locs->S6 = col;
  else if (strcmp(value, "O1")==0 && fam_locs->O1 == 0) fam_locs->O1 = col;
  else if (strcmp(value, "O2")==0 && fam_locs->O2 == 0) fam_locs->O2 = col;
  else if (strcmp(value, "O3")==0 && fam_locs->O3 == 0) fam_locs->O3 = col;
  else if (strcmp(value, "T1")==0 && fam_locs->T1 == 0) fam_locs->T1 = col;
  else if (strcmp(value, "T2")==0 && fam_locs->T2 == 0) fam_locs->T2 = col;
  else if (strcmp(value, "S1_combined")==0 && fam_locs->S1_combined == 0) fam_locs->S1_combined = col;
  else if (strcmp(value, "S3_combined")==0 && fam_locs->S3_combined == 0) fam_locs->S3_combined = col;
  else if (strcmp(value, "S6_combined")==0 && fam_locs->S6_combined == 0) fam_locs->S6_combined = col;

  return 0;
}

int get_fam_strengths_callback(size_t row, size_t col, const char* value, void* callbackdata) {
  FamilyDefns *fam_defns = (FamilyDefns*)callbackdata;
  if (value == NULL) return 0;
  if (row < 7) return 0;

  if (col == 2) {
    // printf("Found a new family: '%s'\n", value);
    FamilyDefn new_family = {0};
    new_family.name = malloc(strlen(value) + 1);
    strcpy(new_family.name, value);
    SDM_ARRAY_PUSH(*fam_defns, new_family);
    return 0;
  }

  size_t index_of_last = fam_defns->length - 1;

  if      (col == fam_defns->fam_locs.D1) fam_defns->data[index_of_last].D1 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D2) fam_defns->data[index_of_last].D2 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D3) fam_defns->data[index_of_last].D3 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q1) fam_defns->data[index_of_last].Q1 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q2) fam_defns->data[index_of_last].Q2 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q3) fam_defns->data[index_of_last].Q3 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q4) fam_defns->data[index_of_last].Q4 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q5) fam_defns->data[index_of_last].Q5 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q6) fam_defns->data[index_of_last].Q6 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R1) fam_defns->data[index_of_last].R1 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R2) fam_defns->data[index_of_last].R2 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R3) fam_defns->data[index_of_last].R3 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S1) fam_defns->data[index_of_last].S1 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S2) fam_defns->data[index_of_last].S2 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S3) fam_defns->data[index_of_last].S3 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S4) fam_defns->data[index_of_last].S4 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S5) fam_defns->data[index_of_last].S5 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S6) fam_defns->data[index_of_last].S6 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.O1) fam_defns->data[index_of_last].O1 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.O2) fam_defns->data[index_of_last].O2 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.O3) fam_defns->data[index_of_last].O3 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.T1) fam_defns->data[index_of_last].T1 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.T2) fam_defns->data[index_of_last].T2 = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S1_combined) fam_defns->data[index_of_last].S1_combined = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S3_combined) fam_defns->data[index_of_last].S3_combined = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S6_combined) fam_defns->data[index_of_last].S6_combined = strtod(value, NULL);

  return 0;
}

int row_callback(size_t row, size_t maxcol, void* callbackdata) {
  (void)callbackdata;
  (void)maxcol;
  (void)row;
  return 0;
}

void concat_strings(const char *str1, const char *str2, char *buffer, size_t buff_len) {
  assert(strlen(str1) + strlen(str2) < buff_len && "Your buffer is too small");
  memset(buffer, 0, buff_len);
  strcpy(buffer, str1);
  strcpy(buffer+strlen(str1), str2);
}

bool ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr) return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}


