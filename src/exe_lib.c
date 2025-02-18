#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <xlsxio_read.h>

#include <sys/types.h>
#include <dirent.h>

#include "exe_lib.h"
#include "sdm_lib.h"

extern LatticeDefinition global_latt_defns[LATT_COUNT];

void set_lattice_definitions(void) {
  int a01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int a01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q};
  int a01_u2_indices[] = {MAG_Q4, MAG_S4, MAG_D2, MAG_D2Q};
  int a01_u3_indices[] = {MAG_Q4, MAG_S5, MAG_S3, MAG_D2, MAG_D2Q};
  int a01_u4_indices[] = {MAG_Q4, MAG_S4, MAG_D2, MAG_D2Q};
  int a01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q};
  int a01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(a01_m1_indices); i++) global_latt_defns[LATT_A01][BLOCK_M1][a01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a01_u1_indices); i++) global_latt_defns[LATT_A01][BLOCK_U1][a01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a01_u2_indices); i++) global_latt_defns[LATT_A01][BLOCK_U2][a01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a01_u3_indices); i++) global_latt_defns[LATT_A01][BLOCK_U3][a01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a01_u4_indices); i++) global_latt_defns[LATT_A01][BLOCK_U4][a01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a01_u5_indices); i++) global_latt_defns[LATT_A01][BLOCK_U5][a01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a01_m2_indices); i++) global_latt_defns[LATT_A01][BLOCK_M2][a01_m2_indices[i]] = true;

  int b03_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int b03_u1_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q};
  int b03_u2_indices[] = {MAG_Q4, MAG_S4, MAG_S3, MAG_D2, MAG_D2Q};
  int b03_u3_indices[] = {MAG_R1, MAG_S5, MAG_S3, MAG_D3, MAG_D3Q};
  int b03_u4_indices[] = {MAG_Q4, MAG_S4, MAG_S3, MAG_D2, MAG_D2Q};
  int b03_u5_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q};
  int b03_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(b03_m1_indices); i++) global_latt_defns[LATT_B03][BLOCK_M1][b03_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b03_u1_indices); i++) global_latt_defns[LATT_B03][BLOCK_U1][b03_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b03_u2_indices); i++) global_latt_defns[LATT_B03][BLOCK_U2][b03_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b03_u3_indices); i++) global_latt_defns[LATT_B03][BLOCK_U3][b03_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b03_u4_indices); i++) global_latt_defns[LATT_B03][BLOCK_U4][b03_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b03_u5_indices); i++) global_latt_defns[LATT_B03][BLOCK_U5][b03_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b03_m2_indices); i++) global_latt_defns[LATT_B03][BLOCK_M2][b03_m2_indices[i]] = true;
}

int print_sheet_name(const char *name, void *callbackdata) {
  (void)callbackdata;
  printf("name = %s\n", name);
  return 0;
}

int get_lattice_summaries(const char *latt_summ_filename, FamilyDefns *fam_defns) {
  const char *sheetname = "Summaries";
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

  if (strcmp(value, "D1")==0) {
    if (fam_locs->D1_value == 0) {
      fam_locs->D1_value  = col;
      fam_locs->D1q_value = col + 1;
    } else {
      fam_locs->D1_cl  = col;
      fam_locs->D1q_cl = col + 1;
    }
  }
  else if (strcmp(value, "D2")==0) {
    if (fam_locs->D2_value == 0) {
      fam_locs->D2_value  = col;
      fam_locs->D2q_value = col + 1;
    } else {
      fam_locs->D2_cl  = col;
      fam_locs->D2q_cl = col + 1;
    }
  }
  else if (strcmp(value, "D3")==0) {
    if (fam_locs->D3_value == 0) {
      fam_locs->D3_value  = col;
      fam_locs->D3q_value = col + 1;
    } else {
      fam_locs->D3_cl  = col;
      fam_locs->D3q_cl = col + 1;
    }
  }
  else if (strcmp(value, "Q1")==0) {
    if (fam_locs->Q1_value == 0) fam_locs->Q1_value = col;
    else fam_locs->Q1_cl = col;
  }
  else if (strcmp(value, "Q2")==0) {
    if (fam_locs->Q2_value == 0) fam_locs->Q2_value = col;
    else fam_locs->Q2_cl = col;
  }
  else if (strcmp(value, "Q3")==0) {
    if (fam_locs->Q3_value == 0) fam_locs->Q3_value = col;
    else fam_locs->Q3_cl = col;
  }
  else if (strcmp(value, "Q4")==0) {
    if (fam_locs->Q4_value == 0) fam_locs->Q4_value = col;
    else fam_locs->Q4_cl = col;
  }
  else if (strcmp(value, "Q5")==0) {
    if (fam_locs->Q5_value == 0) fam_locs->Q5_value = col;
    else fam_locs->Q5_cl = col;
  }
  else if (strcmp(value, "Q6")==0) {
    if (fam_locs->Q6_value == 0) fam_locs->Q6_value = col;
    else fam_locs->Q6_cl = col;
  }
  else if (strcmp(value, "R1")==0) {
    if (fam_locs->R1_value == 0) fam_locs->R1_value = col;
    else fam_locs->R1_cl = col;
  }
  else if (strcmp(value, "R2")==0) {
    if (fam_locs->R2_value == 0) fam_locs->R2_value = col;
    else fam_locs->R2_cl = col;
  }
  else if (strcmp(value, "R3")==0) {
    if (fam_locs->R3_value == 0) fam_locs->R3_value = col;
    else fam_locs->R3_cl = col;
  }
  else if (strcmp(value, "S1")==0) {
    if (fam_locs->S1_value == 0) fam_locs->S1_value = col;
    else fam_locs->S1_cl = col;
  }
  else if (strcmp(value, "S2")==0) {
    if (fam_locs->S2_value == 0) fam_locs->S2_value = col;
    else fam_locs->S2_cl = col;
  }
  else if (strcmp(value, "S3")==0) {
    if (fam_locs->S3_value == 0) fam_locs->S3_value = col;
    else fam_locs->S3_cl = col;
  }
  else if (strcmp(value, "S4")==0) {
    if (fam_locs->S4_value == 0) fam_locs->S4_value = col;
    else fam_locs->S4_cl = col;
  }
  else if (strcmp(value, "S5")==0) {
    if (fam_locs->S5_value == 0) fam_locs->S5_value = col;
    else fam_locs->S5_cl = col;
  }
  else if (strcmp(value, "S6")==0) {
    if (fam_locs->S6_value == 0) fam_locs->S6_value = col;
    else fam_locs->S6_cl = col;
  }
  else if (strcmp(value, "O1")==0) {
    if (fam_locs->O1_value == 0) fam_locs->O1_value = col;
    else fam_locs->O1_cl = col;
  }
  else if (strcmp(value, "O2")==0) {
    if (fam_locs->O2_value == 0) fam_locs->O2_value = col;
    else fam_locs->O2_cl = col;
  }
  else if (strcmp(value, "O3")==0) {
    if (fam_locs->O3_value == 0) fam_locs->O3_value = col;
    else fam_locs->O3_cl = col;
  }
  else if (strcmp(value, "T1")==0) {
    if (fam_locs->T1_value == 0) fam_locs->T1_value = col;
    else fam_locs->T1_cl = col;
  }
  else if (strcmp(value, "T2")==0) {
    if (fam_locs->T2_value == 0) fam_locs->T2_value = col;
    else fam_locs->T2_cl = col;
  }
  else if (strcmp(value, "S1_combined")==0) {
    if (fam_locs->S1_combined_value == 0) fam_locs->S1_combined_value = col;
    else fam_locs->S1_combined_cl = col;
  }
  else if (strcmp(value, "S3_combined")==0) {
    if (fam_locs->S3_combined_value == 0) fam_locs->S3_combined_value = col;
    else fam_locs->S3_combined_cl = col;
  }
  else if (strcmp(value, "S6_combined")==0) {
    if (fam_locs->S6_combined_value == 0) fam_locs->S6_combined_value = col;
    else fam_locs->S6_combined_cl = col;
  }

  return 0;
}

int get_fam_strengths_callback(size_t row, size_t col, const char* value, void* callbackdata) {
  FamilyDefns *fam_defns = (FamilyDefns*)callbackdata;
  if (value == NULL) return 0;
  if (row < 7) return 0;

  if (col == 2) {
    // printf("Found a new family: '%s'\n", value);
    FamilyDefn new_family = {0};
    new_family.name = SDM_MALLOC(strlen(value) + 1);
    strcpy(new_family.name, value);
    SDM_ARRAY_PUSH(*fam_defns, new_family);
    return 0;
  }

  size_t index_of_last = fam_defns->length - 1;

  if      (col == fam_defns->fam_locs.D1_value) fam_defns->data[index_of_last].values[MAG_D1] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D2_value) fam_defns->data[index_of_last].values[MAG_D2] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D3_value) fam_defns->data[index_of_last].values[MAG_D3] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D1q_value) fam_defns->data[index_of_last].values[MAG_D1Q] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D2q_value) fam_defns->data[index_of_last].values[MAG_D2Q] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D3q_value) fam_defns->data[index_of_last].values[MAG_D3Q] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q1_value) fam_defns->data[index_of_last].values[MAG_Q1] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q2_value) fam_defns->data[index_of_last].values[MAG_Q2] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q3_value) fam_defns->data[index_of_last].values[MAG_Q3] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q4_value) fam_defns->data[index_of_last].values[MAG_Q4] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q5_value) fam_defns->data[index_of_last].values[MAG_Q5] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q6_value) fam_defns->data[index_of_last].values[MAG_Q6] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R1_value) fam_defns->data[index_of_last].values[MAG_R1] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R2_value) fam_defns->data[index_of_last].values[MAG_R2] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R3_value) fam_defns->data[index_of_last].values[MAG_R3] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S1_value) fam_defns->data[index_of_last].values[MAG_S1] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S2_value) fam_defns->data[index_of_last].values[MAG_S2] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S3_value) fam_defns->data[index_of_last].values[MAG_S3] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S4_value) fam_defns->data[index_of_last].values[MAG_S4] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S5_value) fam_defns->data[index_of_last].values[MAG_S5] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S6_value) fam_defns->data[index_of_last].values[MAG_S6] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.O1_value) fam_defns->data[index_of_last].values[MAG_O1] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.O2_value) fam_defns->data[index_of_last].values[MAG_O2] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.O3_value) fam_defns->data[index_of_last].values[MAG_O3] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.T1_value) fam_defns->data[index_of_last].values[MAG_T1] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.T2_value) fam_defns->data[index_of_last].values[MAG_T2] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S1_combined_value) fam_defns->data[index_of_last].values[MAG_S1_COMBINED] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S3_combined_value) fam_defns->data[index_of_last].values[MAG_S3_COMBINED] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S6_combined_value) fam_defns->data[index_of_last].values[MAG_S6_COMBINED] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D1_cl) fam_defns->data[index_of_last].cls[MAG_D1] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.D2_cl) fam_defns->data[index_of_last].cls[MAG_D2] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.D3_cl) fam_defns->data[index_of_last].cls[MAG_D3] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.D1q_cl) fam_defns->data[index_of_last].cls[MAG_D1Q] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.D2q_cl) fam_defns->data[index_of_last].cls[MAG_D2Q] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.D3q_cl) fam_defns->data[index_of_last].cls[MAG_D3Q] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.Q1_cl) fam_defns->data[index_of_last].cls[MAG_Q1] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.Q2_cl) fam_defns->data[index_of_last].cls[MAG_Q2] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.Q3_cl) fam_defns->data[index_of_last].cls[MAG_Q3] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.Q4_cl) fam_defns->data[index_of_last].cls[MAG_Q4] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.Q5_cl) fam_defns->data[index_of_last].cls[MAG_Q5] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.Q6_cl) fam_defns->data[index_of_last].cls[MAG_Q6] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R1_cl) fam_defns->data[index_of_last].cls[MAG_R1] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R2_cl) fam_defns->data[index_of_last].cls[MAG_R2] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R3_cl) fam_defns->data[index_of_last].cls[MAG_R3] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S1_cl) fam_defns->data[index_of_last].cls[MAG_S1] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S2_cl) fam_defns->data[index_of_last].cls[MAG_S2] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S3_cl) fam_defns->data[index_of_last].cls[MAG_S3] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S4_cl) fam_defns->data[index_of_last].cls[MAG_S4] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S5_cl) fam_defns->data[index_of_last].cls[MAG_S5] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S6_cl) fam_defns->data[index_of_last].cls[MAG_S6] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.O1_cl) fam_defns->data[index_of_last].cls[MAG_O1] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.O2_cl) fam_defns->data[index_of_last].cls[MAG_O2] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.O3_cl) fam_defns->data[index_of_last].cls[MAG_O3] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.T1_cl) fam_defns->data[index_of_last].cls[MAG_T1] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.T2_cl) fam_defns->data[index_of_last].cls[MAG_T2] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S1_combined_cl) fam_defns->data[index_of_last].cls[MAG_S1_COMBINED] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S3_combined_cl) fam_defns->data[index_of_last].cls[MAG_S3_COMBINED] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S6_combined_cl) fam_defns->data[index_of_last].cls[MAG_S6_COMBINED] = strtol(value, NULL, 10);

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

