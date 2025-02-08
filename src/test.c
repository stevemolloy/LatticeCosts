#include <stdio.h>
#include <string.h>

#include <xlsxio_read.h>
#include "exe_lib.h"

#include "mat.h"
#include "matrix.h"

#define SDM_LIB_IMPLEMENTATION
#include "sdm_lib.h"

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

int print_sheet_name(const char *name, void *callbackdata) {
  (void)callbackdata;
  printf("name = %s\n", name);
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

int main(void) {
  int retval = 0;
  MATFile *mag_lims_file = NULL;
  mxArray *mag_lims_struct = NULL;
  FamilyDefns fam_defns = {0};

  const char *latt_summ_filename = "LatticeSummaries.xlsx";
  const char *mag_lims_filename = "IntMagnetStrengthLimits.mat";
  const char *mag_lims_structname = "IntMagnetStrengthLimits";

  xlsxioreader xlsxioread = xlsxioread_open(latt_summ_filename);
  if (xlsxioread == NULL) {
    REPORT_AND_DIE("Error opening .xlsx file: %s\n", latt_summ_filename);
  }

  const char *sheetname = "Summaries";
  xlsxioread_process(xlsxioread, sheetname, XLSXIOREAD_SKIP_NONE, &get_fam_locs_callback, &row_callback, &(fam_defns.fam_locs));

  xlsxioread_process(xlsxioread, sheetname, XLSXIOREAD_SKIP_NONE, &get_fam_strengths_callback, &row_callback, &fam_defns);
  printf("Found %zu families\n", fam_defns.length);

  mag_lims_file = matOpen(mag_lims_filename, "r");
  if (mag_lims_file == NULL) 
    REPORT_AND_DIE("ERROR: Unable to open MAT file: %s\n", mag_lims_filename);

  mag_lims_struct = matGetVariable(mag_lims_file, mag_lims_structname);
  if (mag_lims_struct == NULL) 
    REPORT_AND_DIE("ERROR: Unable to read variable %s\n", mag_lims_structname);

  if (!mxIsStruct(mag_lims_struct))
    REPORT_AND_DIE("Variable %s is not a structure.\n", mag_lims_structname);

  const char *submag_lims_structname = "Qfm_1";
  mxArray *Qfm_1 = mxGetField(mag_lims_struct, 0, submag_lims_structname);
  Matrix maxs = get_double_array_field(Qfm_1, "Maxs");
  print_matrix(maxs);

dealloc_and_return:
  for (size_t i=0; i<fam_defns.length; i++)
    if (fam_defns.data[i].name != NULL) free(fam_defns.data[i].name);
  SDM_ARRAY_FREE(fam_defns);
  if (mag_lims_struct) mxDestroyArray(mag_lims_struct);
  if (mag_lims_file) matClose(mag_lims_file);
  xlsxioread_close(xlsxioread);
  return retval;
}

