#ifndef _EXE_LIB_H
#define _EXE_LIB_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM_ACHROMATS 20
#define NUM_K25PUMPS 6
#define NUM_K9PUMPS 4
#define NUM_PRESSURE_REGS 2

#define ARRAY_LEN(arr) sizeof((arr)) / sizeof((arr)[0])

#define RETURN_DEFER(VAL)    \
  do {                       \
    retval=(VAL);            \
    goto dealloc_and_return; \
  } while (0)

#define REPORT_AND_DIE(err_msg, ...)         \
  do {                                       \
    fprintf(stderr, (err_msg), __VA_ARGS__); \
    RETURN_DEFER(1);                         \
  } while (0)

typedef enum {
  MAG_D1=0, MAG_D1Q, MAG_D2, MAG_D2Q, MAG_D3, MAG_D3Q,
  MAG_Q1, MAG_Q2, MAG_Q3, MAG_Q4, MAG_Q5, MAG_Q6,
  MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_R3Q, MAG_R3D, MAG_R3OFFS,
  MAG_S1, MAG_S2, MAG_S3, MAG_S4, MAG_S5, MAG_S6,
  MAG_O1, MAG_O2, MAG_O3,
  MAG_T1, MAG_T2,
  MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_S6_COMBINEDS, MAG_S6_COMBINEDQ,
  MAG_COUNT
} MagType;

typedef enum {
  BLOCK_M1=0,
  BLOCK_U1, BLOCK_U2, BLOCK_U3, BLOCK_U4, BLOCK_U5,
  BLOCK_M2,
  BLOCK_COUNT
} BlockType;

typedef enum {
  LATT_UNKNOWN=0,
  LATT_A01, LATT_A02, 
  LATT_B01, LATT_B02, LATT_B03,
  LATT_C01, LATT_D01, LATT_E01,
  LATT_F01, LATT_F02,
  LATT_G01,
  LATT_H01, LATT_H02,
  LATT_I01,
  LATT_COUNT
} LatticeType;

typedef bool BlockDefinition[MAG_COUNT];
typedef BlockDefinition LatticeDefinition[BLOCK_COUNT];

typedef struct {
  size_t D1_value, D2_value, D3_value;
  size_t D1q_value, D2q_value, D3q_value;
  size_t Q1_value, Q2_value, Q3_value, Q4_value, Q5_value, Q6_value;
  size_t R1q_value, R1d_value, R1offs_value, R2q_value, R2d_value, R2offs_value, R3q_value, R3d_value, R3offs_value;
  size_t S1_value, S2_value, S3_value, S4_value, S5_value, S6_value;
  size_t O1_value, O2_value, O3_value;
  size_t T1_value, T2_value;
  size_t S1_combineds_value, S1_combinedq_value, S3_combineds_value, S3_combinedq_value, S6_combineds_value, S6_combinedq_value;
  size_t D1_cl, D2_cl, D3_cl;
  size_t D1q_cl, D2q_cl, D3q_cl;
  size_t Q1_cl, Q2_cl, Q3_cl, Q4_cl, Q5_cl, Q6_cl;
  size_t R1q_cl, R1d_cl, R1offs_cl, R2q_cl, R2d_cl, R2offs_cl, R3q_cl, R3d_cl, R3offs_cl;
  size_t S1_cl, S2_cl, S3_cl, S4_cl, S5_cl, S6_cl;
  size_t O1_cl, O2_cl, O3_cl;
  size_t T1_cl, T2_cl;
  size_t S1_combineds_cl, S1_combinedq_cl, S3_combineds_cl, S3_combinedq_cl, S6_combineds_cl, S6_combinedq_cl;
  size_t HW_check;
} FamilyLocations;

typedef struct {
  char *name;
  double values[MAG_COUNT];
  int cls[MAG_COUNT];
  bool HW_check;
} FamilyDefn;

typedef struct {
  size_t capacity;
  size_t length;
  FamilyDefn *data;
  FamilyLocations fam_locs;
} FamilyDefns;

#define DEFAULT_INFO_BUFF_LEN 128
typedef struct {
  int date;
  char *version;
  char *by;
  char *description;
} Info;

typedef struct {
  size_t capacity;
  size_t length;
  char **data;
} CstringArray;

typedef struct {
  double min;
  double max;
} MagLimits;

typedef struct {
  size_t capacity;
  size_t length;
  MagLimits *data;
} MagLimitsArray;

typedef struct {
  size_t capacity;
  size_t length;
  MagLimitsArray *data;
} MagLimitsArrayArray;

typedef enum {
  BLK_WORK_NONE = 0,
  BLK_WORK_MOD,
  BLK_WORK_REPLACE,
} BlockWork;

typedef enum {
  COOLING_K25PUMPS,
  COOLING_K9PUMPS,
  COOLING_BLK_DIST,
  COOLING_MANIFOLD,
  COOLING_PRESSURE_REG,
  COOLING_LARGE_HEATX,
  COOLING_COUNT,
} CoolingWork;

typedef enum {
  COSTTYPE_INDEPENDENT,
  COSTTYPE_PERACHRO,
  COSTTYPE_PERBLK,
  COSTTYPE_PERACHRO_IF_CHNGD,
  COSTTYPE_PERBLK_IF_CHNGD,
  COSTTYPE_COUNT,
} CostType;

typedef struct {
  size_t capacity;
  size_t length;
  double **data;
} Costs;

void set_lattice_definitions(void);
void set_block_masses(void);
void set_block_build_costs(void);
void set_block_costs(void);
void set_cooling_costs(void);
bool get_blocks_work_details(FamilyDefn fam, BlockWork *blocks_replaced_array, size_t num_blocks);
double total_block_work_costs(FamilyDefn fam, BlockWork *block_work, double *costs, size_t block_count);
double total_cooling_work_costs(BlockWork *block_work, double *costs, CostType *cost_types, size_t costs_length);
int print_sheet_name(const char *name, void *callbackdata);
int get_lattice_summaries(const char *latt_summ_filename, FamilyDefns *fam_defns, Info *info);
int get_fam_locs_callback(size_t row, size_t col, const char* value, void* callbackdata);
int row_callback(size_t row, size_t maxcol, void* callbackdata);
int get_fam_strengths_callback(size_t row, size_t col, const char* value, void* callbackdata);
int get_info_details_callback(size_t row, size_t col, const char* value, void* callbackdata);
const char *block_type_string(BlockType t);
bool any_equal_to(BlockWork *array, size_t len, BlockWork needle);
BlockWork work_due_to_mag(int cl);
LatticeType get_lattice_type_from_name(const char *name);
void print_file_summary(FILE *sink, const char *latt_summ_filename, const FamilyDefns *fam_defns, const Info *info);
void print_lattice_details(FILE *sink, const char *lattice_name, double block_work_cost, double cooling_work_cost, BlockWork *block_work_details, size_t num_blocks);
void print_header(FILE *sink);
void print_block_work_info(FILE *sink, BlockWork *blocks_replaced, size_t num_blocks);
void print_block_replacement_info(FILE *sink, BlockWork *blocks_replaced, size_t num_blocks);
void print_block_modification_info(FILE *sink, BlockWork *blocks_replaced, size_t num_blocks);
Info create_info_struct(void);

void concat_strings(const char *str1, const char *str2, char *buffer, size_t buff_len);
bool ends_with(const char *str, const char *suffix);
char* days_to_date(int days);

#endif // !_EXE_LIB_H

