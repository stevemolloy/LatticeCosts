#include <stdio.h>

#include "exe_lib.h"

#define SDM_LIB_IMPLEMENTATION
#include "sdm_lib.h"

#define NUM_ACHROMATS 20

double block_costs[BLOCK_COUNT] = {0};
double block_mass[BLOCK_COUNT] = {0};
double EUR_PER_METRICTONNE_STEEL;

LatticeDefinition global_latt_defns[LATT_COUNT];

static sdm_arena_t main_arena = {0};
static sdm_arena_t *active_arena = &main_arena;

void *active_alloc(size_t size)              { return sdm_arena_alloc(active_arena, size); }
void *active_realloc(void *ptr, size_t size) { return sdm_arena_realloc(active_arena, ptr, size); }

int main(void) {
  int retval = 0;

  const char *latt_summ_filename = "data/LatticeSummaries.xlsx";

  set_lattice_definitions();
  set_block_costs();

  // Get data from lattice summary spreadsheet
  FamilyDefns fam_defns = {0};
  Info info = create_info_struct();
  if (get_lattice_summaries(latt_summ_filename, &fam_defns, &info) < 0)
    REPORT_AND_DIE("Error opening .xlsx file: %s\n", latt_summ_filename);

  print_file_summary(latt_summ_filename, &fam_defns, &info);
  for (size_t i=0; i<fam_defns.length; i++) {
    FamilyDefn fam = fam_defns.data[i];
    if (!fam.HW_check) continue;

    bool blocks_replaced[BLOCK_COUNT] = {false};
    if (!get_blocks_replaced(fam, blocks_replaced, BLOCK_COUNT)) continue;

    double cost = total_block_replacement_costs(blocks_replaced, block_costs, BLOCK_COUNT);

    printf("%s :: ", fam.name);
    print_block_replacement_info(blocks_replaced, BLOCK_COUNT);
    printf("TOTAL COST = %0.1f M.SEK\n", NUM_ACHROMATS * cost/1e6);
  }

dealloc_and_return:
  sdm_arena_free(&main_arena);
  return retval;
}

