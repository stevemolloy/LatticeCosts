#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

#include "exe_lib.h"

#include "mat.h"
#include "matrix.h"

char *mag_fam_names[] = {
  "dipm_d", "dipm_q", "dip_d", "dip_q",
  "Qfend", "Qdend", "Qfm_1", "Qfm_2", "Qf_U2_1", "Qf_U2_2", "Qf_U3_1", "Qf_U3_2",
  "Rb_U1_1", "Rb_U1_2", "Rb_U3_1", "Rb_U3_2",
  "Sdend", "Sfm", "Sd", "Sfo", "Sfi",
  "Oxx", "Oxy", "Oyy",
  "Sdendcomb_s", "Sdendcomb_q", "Sdcomb_s", "Sdcomb_q", "SextTrimsQ",
};
#define NUM_FAMS_WITH_LIMS sizeof(mag_fam_names)/sizeof(mag_fam_names[0])

#define TEMPBUFFLENGTH 1024

#define SDM_LIB_IMPLEMENTATION
#include "sdm_lib.h"

static sdm_arena_t main_arena = {0};
static sdm_arena_t *active_arena = &main_arena;

void *active_alloc(size_t size)              { return sdm_arena_alloc(active_arena, size); }
void *active_realloc(void *ptr, size_t size) { return sdm_arena_realloc(active_arena, ptr, size); }

int main(void) {
  int retval = 0;
  MATFile *mag_lims_file = NULL;
  mxArray *mag_lims_struct = NULL;

  const char *latt_summ_filename = "data/LatticeSummaries.xlsx";
  const char *sheetname = "Summaries";
  const char *mag_lims_filename = "data/IntMagnetStrengthLimits.mat";
  const char *cand_latt_dirname = "data/CandidateLattices/";
  char temp_buffer[TEMPBUFFLENGTH] = {0};

  // Get magnet limits
  MagLimitsArrayArray mag_limits = {0};
  if (get_mag_lims(mag_lims_filename, &mag_limits) < 0) {
    retval = 1;
    goto dealloc_and_return;
  }
  for (size_t i=0; i<mag_limits.length; i++) {
    printf("%s: last_max = %f\n", mag_fam_names[i], mag_limits.data[i].data[mag_limits.data[i].length-1].max);
  }

  goto dealloc_and_return;

  // Working with the mat files in the candidate lattice folder
  DIR *cand_latt_dir = opendir(cand_latt_dirname);
  struct dirent *cand_latt_file_data;
  while ((cand_latt_file_data = readdir(cand_latt_dir)) != NULL) {
    if (cand_latt_file_data->d_type != DT_DIR || strncmp(cand_latt_file_data->d_name, ".", 1) == 0)
      continue;
    char *lattice_name = cand_latt_file_data->d_name;

    concat_strings(cand_latt_dirname, lattice_name, temp_buffer, TEMPBUFFLENGTH);
    struct dirent *lattice_file_data;
    DIR *lattice_dir = opendir(temp_buffer);
    while ((lattice_file_data = readdir(lattice_dir)) != NULL) {
      if (lattice_file_data->d_type != DT_REG || strncmp(lattice_file_data->d_name, ".", 1)==0 || !ends_with(lattice_file_data->d_name, ".mat"))
        continue;
      char *filename = lattice_file_data->d_name;
      concat_strings(lattice_name, ".mat", temp_buffer, TEMPBUFFLENGTH);
      if (strcmp(filename, temp_buffer)!=0)
        continue;
      printf("%s: %s\n", lattice_name, filename);
    }
    if (lattice_dir) closedir(lattice_dir);
  }
  if (cand_latt_dir) closedir(cand_latt_dir);

  // Get data from lattice summary spreadsheet
  FamilyDefns fam_defns = {0};
  if (get_lattice_summaries(latt_summ_filename, sheetname, &fam_defns) < 0)
    REPORT_AND_DIE("Error opening .xlsx file: %s\n", latt_summ_filename);
  printf("Found %zu families\n", fam_defns.length);

dealloc_and_return:
  for (size_t i=0; i<fam_defns.length; i++)
    if (fam_defns.data[i].name != NULL) free(fam_defns.data[i].name);
  if (fam_defns.data) SDM_ARRAY_FREE(fam_defns);
  if (mag_lims_struct) mxDestroyArray(mag_lims_struct);
  if (mag_lims_file) matClose(mag_lims_file);
  sdm_arena_free(&main_arena);
  return retval;
}

