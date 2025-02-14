#include <stdio.h>

#include "mat.h"

#include "exe_lib.h"

char *mag_fam_names[] = {
  "dipm_d", "dipm_q", "dip_d", "dip_q",
  "Qfend", "Qdend", "Qfm_1", "Qfm_2", "Qf_U2_1", "Qf_U2_2", "Qf_U3_1", "Qf_U3_2",
  "Rb_U1_1", "Rb_U1_2", "Rb_U3_1", "Rb_U3_2",
  "Sdend", "Sfm", "Sd", "Sfo", "Sfi",
  "Oxx", "Oxy", "Oyy",
  "Sdendcomb_s", "Sdendcomb_q", "Sdcomb_s", "Sdcomb_q", "SextTrimsQ",
};
#define NUM_FAMS_WITH_LIMS sizeof(mag_fam_names)/sizeof(mag_fam_names[0])

char temp_buffer[TEMPBUFFLENGTH] = {0};

#define SDM_LIB_IMPLEMENTATION
#include "sdm_lib.h"

static sdm_arena_t main_arena = {0};
static sdm_arena_t *active_arena = &main_arena;

void *active_alloc(size_t size)              { return sdm_arena_alloc(active_arena, size); }
void *active_realloc(void *ptr, size_t size) { return sdm_arena_realloc(active_arena, ptr, size); }

int main(void) {
  int retval = 0;
  char **contents = NULL;
  MATFile *lattice_file = NULL;
  mxArray *cLopts = NULL;
  MATFile *cLopts_file = NULL;

  const char *latt_summ_filename = "data/LatticeSummaries.xlsx";
  const char *mag_lims_filename = "data/IntMagnetStrengthLimits.mat";
  const char *cand_latt_dirname = "data/CandidateLattices/";

  // Get magnet limits
  MagLimitsArrayArray mag_limits = {0};
  if (get_mag_lims(mag_lims_filename, &mag_limits) < 0)
    RETURN_DEFER(1);

  // Get data from lattice summary spreadsheet
  FamilyDefns fam_defns = {0};
  if (get_lattice_summaries(latt_summ_filename, &fam_defns) < 0)
    REPORT_AND_DIE("Error opening .xlsx file: %s\n", latt_summ_filename);
  printf("Found %zu lattices in %s\n", fam_defns.length, latt_summ_filename);

  // Working with the mat files in the candidate lattice folder
  CstringArray list_of_lattice_folders = {0};
  get_list_of_lattice_folders(cand_latt_dirname, &list_of_lattice_folders );
  printf("Found %zu lattices in the candidate lattice folder (%s):\n", list_of_lattice_folders.length, cand_latt_dirname);
  for (size_t i=0; i<list_of_lattice_folders.length; i++) {
    size_t filename_len = strlen(list_of_lattice_folders.data[i]) + strlen("cLoptions.mat") + 10;
    char *filename = SDM_MALLOC(filename_len);
    concat_strings(list_of_lattice_folders.data[i], "cLoptions.mat", filename, filename_len);
    printf("%s\n", filename);

    cLopts_file = matOpen(filename, "r");
    if (cLopts_file == NULL)
      REPORT_AND_DIE("ERROR: Unable to open %s\n", filename);

    cLopts = matGetVariable(cLopts_file, "cLoptions");
    if (cLopts == NULL)
      REPORT_AND_DIE("ERROR: Unable to read variable %s\n", "cLoptions");
    if (!mxIsStruct(cLopts))
      REPORT_AND_DIE("Variable %s is not a structure.\n", "cLoptions");

    mxArray *sumTabfams = mxGetField(cLopts, 0, "sumTabfams");
    if (sumTabfams != NULL) {
      int M = mxGetM(sumTabfams);
      for (int j=0; j<M; j++) {
        mxArray *cell = mxGetCell(sumTabfams, j);
        printf("\tchars = %s\n", mxArrayToString(cell));
      }
    } else {
      fprintf(stderr, "WARNING: Not sumTabfams in %s\n", filename);
    }

    mxDestroyArray(cLopts); cLopts = NULL;
    matClose(cLopts_file); cLopts_file = NULL;
  }

dealloc_and_return:
  if (cLopts) mxDestroyArray(cLopts);
  if (cLopts_file) matClose(cLopts_file);
  if (contents) mxFree(contents);
  if (lattice_file) matClose(lattice_file);
  sdm_arena_free(&main_arena);
  return retval;
}

