#include <stdio.h>

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

  printf("\nFrom %s\n", latt_summ_filename);
  for (size_t i=0; i<fam_defns.length; i++)
    printf("%s\n", fam_defns.data[i].name);

  // Working with the mat files in the candidate lattice folder
  CstringArray list_of_lattice_files = {0};
  get_list_of_lattice_files(cand_latt_dirname, &list_of_lattice_files );

  printf("\nFound the following in the candidate lattice folder (%s):\n", cand_latt_dirname);
  for (size_t i=0; i<list_of_lattice_files.length; i++)
    printf("%s\n", list_of_lattice_files.data[i]);

dealloc_and_return:
  sdm_arena_free(&main_arena);
  return retval;
}

