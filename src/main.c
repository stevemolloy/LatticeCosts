#include <stdio.h>

#include "exe_lib.h"

#define SDM_LIB_IMPLEMENTATION
#include "sdm_lib.h"

static sdm_arena_t main_arena = {0};
static sdm_arena_t *active_arena = &main_arena;

void *active_alloc(size_t size)              { return sdm_arena_alloc(active_arena, size); }
void *active_realloc(void *ptr, size_t size) { return sdm_arena_realloc(active_arena, ptr, size); }

int main(void) {
  int retval = 0;

  const char *latt_summ_filename = "data/LatticeSummaries.xlsx";
  // const char *maglimits_filename = "MagnetStrengthLimits.xlsx";

  // Get data from lattice summary spreadsheet
  FamilyDefns fam_defns = {0};
  if (get_lattice_summaries(latt_summ_filename, &fam_defns) < 0)
    REPORT_AND_DIE("Error opening .xlsx file: %s\n", latt_summ_filename);
  printf("Found %zu lattices in %s\n", fam_defns.length, latt_summ_filename);

dealloc_and_return:
  sdm_arena_free(&main_arena);
  return retval;
}

