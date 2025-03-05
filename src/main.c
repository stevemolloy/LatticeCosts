#include <stdio.h>

#include "exe_lib.h"

#define SDM_LIB_IMPLEMENTATION
#include "sdm_lib.h"

double block_costs[BLOCK_COUNT] = {0};
double block_mass[BLOCK_COUNT] = {0};
double cooling_costs[COOLING_COUNT];
CostType cooling_cost_types[COOLING_COUNT];
double EUR_PER_METRICTONNE_STEEL;

LatticeDefinition global_latt_defns[LATT_COUNT];

static sdm_arena_t main_arena = {0};
static sdm_arena_t *active_arena = &main_arena;

void *active_alloc(size_t size)              { return sdm_arena_alloc(active_arena, size); }
void *active_realloc(void *ptr, size_t size) { return sdm_arena_realloc(active_arena, ptr, size); }

int main(int argc, char *argv[]) {
  int retval = 0;

  char *programname = sdm_shift_args(&argc, &argv);
  if (argc < 1) REPORT_AND_DIE("Incorrect usage:\n%s <xls-file>\n", programname);

  char *latt_summ_filename = NULL;
  char *out_filename = NULL;

  while (argc > 0) {
    const char *input_arg = sdm_shift_args(&argc, &argv);
    if (strcmp(input_arg, "-o")==0) {
      if (argc < 1) REPORT_AND_DIE("ERROR: %s flag should be followed by a filename\n", input_arg);
      out_filename = sdm_shift_args(&argc, &argv);
    } else {
      latt_summ_filename = (char*)input_arg;
    }
  }

  set_lattice_definitions();
  set_block_costs();
  set_cooling_costs();

  // Get data from lattice summary spreadsheet
  FamilyDefns fam_defns = {0};
  Info info = create_info_struct();
  if (get_lattice_summaries(latt_summ_filename, &fam_defns, &info) < 0)
    REPORT_AND_DIE("Error opening .xlsx file: %s\n", latt_summ_filename);

  // Calculate costs from this data
  double *block_work_costs = SDM_MALLOC(fam_defns.length * sizeof(double));
  double *cooling_work_costs = SDM_MALLOC(fam_defns.length * sizeof(double));
  BlockWork *block_work_details = SDM_MALLOC(fam_defns.length * BLOCK_COUNT * sizeof(BlockWork));
  for (size_t i=0; i<fam_defns.length; i++) {
    FamilyDefn fam = fam_defns.data[i];
    if (!get_blocks_work_details(fam, &block_work_details[i*BLOCK_COUNT], BLOCK_COUNT)) continue;
    block_work_costs[i] = total_block_work_costs(fam, &block_work_details[i*BLOCK_COUNT], block_costs, BLOCK_COUNT);
    cooling_work_costs[i] = total_cooling_work_costs(&block_work_details[i*BLOCK_COUNT], cooling_costs, cooling_cost_types, COOLING_COUNT);
  }
  
  Costs all_costs = {0};
  SDM_ARRAY_PUSH(all_costs, block_work_costs);
  SDM_ARRAY_PUSH(all_costs, cooling_work_costs);
  FILE *sink = stdout;
  if (out_filename != NULL) {
    sink = fopen(out_filename, "w");
    if (sink == NULL)
      REPORT_AND_DIE("ERROR: Could not open %s for writing\n", out_filename);
  }
  print_file_summary(sink, latt_summ_filename, &fam_defns, &info);
  print_header(sink);
  for (size_t i=0; i<fam_defns.length; i++)
    print_lattice_details(sink, fam_defns.data[i].name, block_work_costs[i], cooling_work_costs[i], &block_work_details[i*BLOCK_COUNT], BLOCK_COUNT);

dealloc_and_return:
  sdm_arena_free(&main_arena);
  return retval;
}

