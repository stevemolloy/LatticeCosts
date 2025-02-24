#include <stdio.h>

#include "exe_lib.h"

#define SDM_LIB_IMPLEMENTATION
#include "sdm_lib.h"

#define NUM_ACHROMATS 20

double block_costs[BLOCK_COUNT] = {0};
double block_mass[BLOCK_COUNT] = {0};
double sek_per_kg_steel;

LatticeDefinition global_latt_defns[LATT_COUNT];

static sdm_arena_t main_arena = {0};
static sdm_arena_t *active_arena = &main_arena;

void *active_alloc(size_t size)              { return sdm_arena_alloc(active_arena, size); }
void *active_realloc(void *ptr, size_t size) { return sdm_arena_realloc(active_arena, ptr, size); }

double total_block_replacement_costs(bool *blocks_replaced, double *costs, size_t block_count) {
  double cost = 0;
  for (size_t block_ind=0; block_ind<block_count; block_ind++)
    if (blocks_replaced[block_ind]) cost += costs[block_ind];
  return cost;
}

int main(void) {
  int retval = 0;

  const char *latt_summ_filename = "data/LatticeSummaries.xlsx";

  set_lattice_definitions();
  set_block_costs();

  // Get data from lattice summary spreadsheet
  FamilyDefns fam_defns = {0};
  if (get_lattice_summaries(latt_summ_filename, &fam_defns) < 0)
    REPORT_AND_DIE("Error opening .xlsx file: %s\n", latt_summ_filename);
  printf("Found %zu lattices in %s\n", fam_defns.length, latt_summ_filename);

  for (size_t i=0; i<fam_defns.length; i++) {
    FamilyDefn fam = fam_defns.data[i];
    printf("%s :: ", fam.name);

    bool blocks_replaced[BLOCK_COUNT] = {false};
    if (!get_blocks_replaced(fam, blocks_replaced, BLOCK_COUNT)) continue;

    bool any_blocks_replaced = any_true(blocks_replaced, BLOCK_COUNT);

    printf("Blocks to replace:  ");
    double cost = total_block_replacement_costs(blocks_replaced, block_costs, BLOCK_COUNT);
    for (size_t block_ind=0; block_ind<BLOCK_COUNT; block_ind++)
      if (blocks_replaced[block_ind]) printf("%s, ", block_type_string(block_ind));
    if (!any_blocks_replaced) printf("-  ");
    printf("TOTAL COST = %0.1f M.SEK  ", NUM_ACHROMATS * cost/1e6);

    printf("\n");
  }

dealloc_and_return:
  sdm_arena_free(&main_arena);
  return retval;
}

