#ifndef _EXE_LIB_H
#define _EXE_LIB_H

#include <stdbool.h>
#include <stdlib.h>

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
  MAG_R1, MAG_R2, MAG_R3,
  MAG_S1, MAG_S2, MAG_S3, MAG_S4, MAG_S5, MAG_S6,
  MAG_O1, MAG_O2, MAG_O3,
  MAG_T1, MAG_T2,
  MAG_S1_COMBINED, MAG_S3_COMBINED, MAG_S6_COMBINED,
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
  size_t R1_value, R2_value, R3_value;
  size_t S1_value, S2_value, S3_value, S4_value, S5_value, S6_value;
  size_t O1_value, O2_value, O3_value;
  size_t T1_value, T2_value;
  size_t S1_combined_value, S3_combined_value, S6_combined_value;
  size_t D1_cl, D2_cl, D3_cl;
  size_t D1q_cl, D2q_cl, D3q_cl;
  size_t Q1_cl, Q2_cl, Q3_cl, Q4_cl, Q5_cl, Q6_cl;
  size_t R1_cl, R2_cl, R3_cl;
  size_t S1_cl, S2_cl, S3_cl, S4_cl, S5_cl, S6_cl;
  size_t O1_cl, O2_cl, O3_cl;
  size_t T1_cl, T2_cl;
  size_t S1_combined_cl, S3_combined_cl, S6_combined_cl;
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

void set_lattice_definitions(void);
void set_block_masses(void);
void set_block_costs(void);
bool get_blocks_replaced(FamilyDefn fam, bool *blocks_replaced_array, size_t num_blocks);
double total_block_replacement_costs(bool *blocks_replaced, double *costs, size_t block_count);
int print_sheet_name(const char *name, void *callbackdata);
int get_lattice_summaries(const char *latt_summ_filename, FamilyDefns *fam_defns, Info *info);
int get_fam_locs_callback(size_t row, size_t col, const char* value, void* callbackdata);
int row_callback(size_t row, size_t maxcol, void* callbackdata);
int get_fam_strengths_callback(size_t row, size_t col, const char* value, void* callbackdata);
int get_info_details_callback(size_t row, size_t col, const char* value, void* callbackdata);
const char *block_type_string(BlockType t);
bool any_true(bool *array, size_t len);
bool replace_due_to_mag(int cl);
LatticeType get_lattice_type_from_name(const char *name);

void concat_strings(const char *str1, const char *str2, char *buffer, size_t buff_len);
bool ends_with(const char *str, const char *suffix);
char* days_to_date(int days);

#endif // !_EXE_LIB_H

