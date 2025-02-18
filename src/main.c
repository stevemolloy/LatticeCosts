#include <stdio.h>

#include "exe_lib.h"

#define SDM_LIB_IMPLEMENTATION
#include "sdm_lib.h"

LatticeDefinition global_latt_defns[LATT_COUNT];

static sdm_arena_t main_arena = {0};
static sdm_arena_t *active_arena = &main_arena;

void *active_alloc(size_t size)              { return sdm_arena_alloc(active_arena, size); }
void *active_realloc(void *ptr, size_t size) { return sdm_arena_realloc(active_arena, ptr, size); }

int main(void) {
  int retval = 0;

  const char *latt_summ_filename = "data/LatticeSummaries.xlsx";

  set_lattice_definitions();

  // Get data from lattice summary spreadsheet
  FamilyDefns fam_defns = {0};
  if (get_lattice_summaries(latt_summ_filename, &fam_defns) < 0)
    REPORT_AND_DIE("Error opening .xlsx file: %s\n", latt_summ_filename);
  printf("Found %zu lattices in %s\n", fam_defns.length, latt_summ_filename);
  for (size_t i=0; i<fam_defns.length; i++) {
    FamilyDefn fam = fam_defns.data[i];
    printf("%s :: ", fam.name);

    LatticeType lat_type = get_lattice_type_from_name(fam.name);
    if (lat_type == LATT_UNKNOWN) {
      printf("WARNING: Layout of \"%s\" is unknown.\n", fam.name);
      continue;
    }

    bool blocks_replaced[BLOCK_COUNT] = {false};
    bool any_blocks_replaced = false;
    for (size_t block_ind=0; block_ind<BLOCK_COUNT; block_ind++) {
      for (size_t mag_ind=0; mag_ind<MAG_COUNT; mag_ind++) {
        if (global_latt_defns[lat_type][block_ind][mag_ind] && replace_due_to_mag(fam.cls[mag_ind])) {
          blocks_replaced[block_ind] = true;
          any_blocks_replaced = true;
          break;
        }
      }
    }

    printf("\tThe following blocks need to be replaced:  ");
    for (size_t block_ind=0; block_ind<BLOCK_COUNT; block_ind++) {
      if (blocks_replaced[block_ind]) {
        printf("%s, ", block_type_string(block_ind));
      }
    }
    if (!any_blocks_replaced) printf("-");

    printf("\n");
  }

dealloc_and_return:
  sdm_arena_free(&main_arena);
  return retval;
}

