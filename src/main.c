#include <stdio.h>
#include <string.h>

#include "exe_lib.h"

#include "mat.h"
#include "matrix.h"

#define SDM_LIB_IMPLEMENTATION
#include "sdm_lib.h"

int main(void) {
  int retval = 0;
  MATFile *mag_lims_file = NULL;
  mxArray *mag_lims_struct = NULL;

  const char *latt_summ_filename = "data/LatticeSummaries.xlsx";
  const char *sheetname = "Summaries";
  const char *mag_lims_filename = "data/IntMagnetStrengthLimits.mat";
  const char *mag_lims_structname = "IntMagnetStrengthLimits";

  FamilyDefns fam_defns = {0};
  if (get_lattice_summaries(latt_summ_filename, sheetname, &fam_defns) < 0)
    REPORT_AND_DIE("Error opening .xlsx file: %s\n", latt_summ_filename);
  printf("Found %zu families\n", fam_defns.length);

  mag_lims_file = matOpen(mag_lims_filename, "r");
  if (mag_lims_file == NULL) REPORT_AND_DIE("ERROR: Unable to open MAT file: %s\n", mag_lims_filename);

  mag_lims_struct = matGetVariable(mag_lims_file, mag_lims_structname);
  if (mag_lims_struct == NULL) REPORT_AND_DIE("ERROR: Unable to read variable %s\n", mag_lims_structname);

  if (!mxIsStruct(mag_lims_struct)) REPORT_AND_DIE("Variable %s is not a structure.\n", mag_lims_structname);

  const char *submag_lims_structname = "Qfm_1";
  mxArray *Qfm_1 = mxGetField(mag_lims_struct, 0, submag_lims_structname);
  Matrix maxs = get_double_array_field(Qfm_1, "Maxs");
  print_matrix(maxs);

dealloc_and_return:
  for (size_t i=0; i<fam_defns.length; i++)
    if (fam_defns.data[i].name != NULL) free(fam_defns.data[i].name);
  if (fam_defns.data) SDM_ARRAY_FREE(fam_defns);
  if (mag_lims_struct) mxDestroyArray(mag_lims_struct);
  if (mag_lims_file) matClose(mag_lims_file);
  return retval;
}

