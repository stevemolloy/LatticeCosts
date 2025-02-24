#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <xlsxio_read.h>

#include <sys/types.h>
#include <dirent.h>

#include "exe_lib.h"
#include "sdm_lib.h"

extern LatticeDefinition global_latt_defns[LATT_COUNT];
extern double block_costs[BLOCK_COUNT];
extern double block_mass[BLOCK_COUNT];
extern double sek_per_kg_steel;
const double EUR2SEK = 11.5;
const double EUR_PER_METRICTONNE_STEEL = 1000;

static void set_block_masses(void) {
  block_mass[BLOCK_M1] = 2.5e3; // kg
  block_mass[BLOCK_M2] = 2.5e3; // kg
  block_mass[BLOCK_U1] = 2.5e3; // kg
  block_mass[BLOCK_U2] = 2.5e3; // kg
  block_mass[BLOCK_U4] = 2.5e3; // kg
  block_mass[BLOCK_U5] = 2.5e3; // kg
  block_mass[BLOCK_U3] = 2.5e3; // kg
}

void set_block_costs(void) {
  set_block_masses();

  sek_per_kg_steel = (EUR_PER_METRICTONNE_STEEL / 1000.0) * EUR2SEK;

  block_costs[BLOCK_M1] = 2.1e6 + block_mass[BLOCK_M1] * sek_per_kg_steel;
  block_costs[BLOCK_M2] = 2.1e6 + block_mass[BLOCK_M2] * sek_per_kg_steel;
  block_costs[BLOCK_U1] = 1.4e6 + block_mass[BLOCK_U1] * sek_per_kg_steel;
  block_costs[BLOCK_U2] = 1.4e6 + block_mass[BLOCK_U2] * sek_per_kg_steel;
  block_costs[BLOCK_U4] = 1.4e6 + block_mass[BLOCK_U4] * sek_per_kg_steel;
  block_costs[BLOCK_U5] = 1.4e6 + block_mass[BLOCK_U5] * sek_per_kg_steel;
  block_costs[BLOCK_U3] = 3.5e6 + block_mass[BLOCK_U3] * sek_per_kg_steel;
}

void set_lattice_definitions(void) {
  int a01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int a01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q};
  int a01_u2_indices[] = {MAG_Q4, MAG_S4, MAG_D2, MAG_D2Q};
  int a01_u3_indices[] = {MAG_Q4, MAG_S5, MAG_S3, MAG_D2, MAG_D2Q};
  int a01_u4_indices[] = {MAG_Q4, MAG_S4, MAG_D2, MAG_D2Q};
  int a01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q};
  int a01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(a01_m1_indices); i++) global_latt_defns[LATT_A01][BLOCK_M1][a01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a01_u1_indices); i++) global_latt_defns[LATT_A01][BLOCK_U1][a01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a01_u2_indices); i++) global_latt_defns[LATT_A01][BLOCK_U2][a01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a01_u3_indices); i++) global_latt_defns[LATT_A01][BLOCK_U3][a01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a01_u4_indices); i++) global_latt_defns[LATT_A01][BLOCK_U4][a01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a01_u5_indices); i++) global_latt_defns[LATT_A01][BLOCK_U5][a01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a01_m2_indices); i++) global_latt_defns[LATT_A01][BLOCK_M2][a01_m2_indices[i]] = true;

  int a02_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int a02_u1_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q};
  int a02_u2_indices[] = {MAG_Q4, MAG_S4, MAG_S3, MAG_D2, MAG_D2Q};
  int a02_u3_indices[] = {MAG_Q5, MAG_S5, MAG_S3, MAG_D2, MAG_D2Q};
  int a02_u4_indices[] = {MAG_Q4, MAG_S4, MAG_S3, MAG_D2, MAG_D2Q};
  int a02_u5_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q};
  int a02_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(a02_m1_indices); i++) global_latt_defns[LATT_A02][BLOCK_M1][a02_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a02_u1_indices); i++) global_latt_defns[LATT_A02][BLOCK_U1][a02_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a02_u2_indices); i++) global_latt_defns[LATT_A02][BLOCK_U2][a02_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a02_u3_indices); i++) global_latt_defns[LATT_A02][BLOCK_U3][a02_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a02_u4_indices); i++) global_latt_defns[LATT_A02][BLOCK_U4][a02_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a02_u5_indices); i++) global_latt_defns[LATT_A02][BLOCK_U5][a02_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(a02_m2_indices); i++) global_latt_defns[LATT_A02][BLOCK_M2][a02_m2_indices[i]] = true;

  int b01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int b01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_Q4, MAG_S3, MAG_D2, MAG_D2Q};
  int b01_u2_indices[] = {MAG_Q5, MAG_S4, MAG_Q6, MAG_S3, MAG_D2, MAG_D2Q};
  int b01_u3_indices[] = {MAG_R1, MAG_S5, MAG_R2, MAG_S3, MAG_D3, MAG_D3Q};
  int b01_u4_indices[] = {MAG_Q5, MAG_S4, MAG_Q6, MAG_S3, MAG_D2, MAG_D2Q};
  int b01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_Q4, MAG_S3, MAG_D2, MAG_D2Q};
  int b01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(b01_m1_indices); i++) global_latt_defns[LATT_B01][BLOCK_M1][b01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b01_u1_indices); i++) global_latt_defns[LATT_B01][BLOCK_U1][b01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b01_u2_indices); i++) global_latt_defns[LATT_B01][BLOCK_U2][b01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b01_u3_indices); i++) global_latt_defns[LATT_B01][BLOCK_U3][b01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b01_u4_indices); i++) global_latt_defns[LATT_B01][BLOCK_U4][b01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b01_u5_indices); i++) global_latt_defns[LATT_B01][BLOCK_U5][b01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b01_m2_indices); i++) global_latt_defns[LATT_B01][BLOCK_M2][b01_m2_indices[i]] = true;

  int b02_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int b02_u1_indices[] = {MAG_Q3, MAG_S2, MAG_Q4, MAG_S3, MAG_D2, MAG_D2Q};
  int b02_u2_indices[] = {MAG_Q5, MAG_S4, MAG_Q6, MAG_S3, MAG_D2, MAG_D2Q};
  int b02_u3_indices[] = {MAG_R1, MAG_S5, MAG_R2, MAG_S6, MAG_D3, MAG_D3Q};
  int b02_u4_indices[] = {MAG_Q5, MAG_S4, MAG_Q6, MAG_S3, MAG_D2, MAG_D2Q};
  int b02_u5_indices[] = {MAG_Q3, MAG_S2, MAG_Q4, MAG_S3, MAG_D2, MAG_D2Q};
  int b02_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(b02_m1_indices); i++) global_latt_defns[LATT_B02][BLOCK_M1][b02_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b02_u1_indices); i++) global_latt_defns[LATT_B02][BLOCK_U1][b02_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b02_u2_indices); i++) global_latt_defns[LATT_B02][BLOCK_U2][b02_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b02_u3_indices); i++) global_latt_defns[LATT_B02][BLOCK_U3][b02_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b02_u4_indices); i++) global_latt_defns[LATT_B02][BLOCK_U4][b02_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b02_u5_indices); i++) global_latt_defns[LATT_B02][BLOCK_U5][b02_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b02_m2_indices); i++) global_latt_defns[LATT_B02][BLOCK_M2][b02_m2_indices[i]] = true;

  int b03_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int b03_u1_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q};
  int b03_u2_indices[] = {MAG_Q4, MAG_S4, MAG_S3, MAG_D2, MAG_D2Q};
  int b03_u3_indices[] = {MAG_R1, MAG_S5, MAG_S3, MAG_D3, MAG_D3Q};
  int b03_u4_indices[] = {MAG_Q4, MAG_S4, MAG_S3, MAG_D2, MAG_D2Q};
  int b03_u5_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q};
  int b03_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(b03_m1_indices); i++) global_latt_defns[LATT_B03][BLOCK_M1][b03_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b03_u1_indices); i++) global_latt_defns[LATT_B03][BLOCK_U1][b03_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b03_u2_indices); i++) global_latt_defns[LATT_B03][BLOCK_U2][b03_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b03_u3_indices); i++) global_latt_defns[LATT_B03][BLOCK_U3][b03_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b03_u4_indices); i++) global_latt_defns[LATT_B03][BLOCK_U4][b03_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b03_u5_indices); i++) global_latt_defns[LATT_B03][BLOCK_U5][b03_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(b03_m2_indices); i++) global_latt_defns[LATT_B03][BLOCK_M2][b03_m2_indices[i]] = true;

  int c01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int c01_u1_indices[] = {MAG_R1, MAG_S2, MAG_R2, MAG_S3, MAG_D2, MAG_D2Q};
  int c01_u2_indices[] = {MAG_R3, MAG_S4, MAG_S3, MAG_D2, MAG_D2Q};
  int c01_u3_indices[] = {MAG_R3, MAG_S5, MAG_S3, MAG_D2, MAG_D2Q};
  int c01_u4_indices[] = {MAG_R3, MAG_S4, MAG_S3, MAG_D2, MAG_D2Q};
  int c01_u5_indices[] = {MAG_R1, MAG_S2, MAG_R2, MAG_S3, MAG_D2, MAG_D2Q};
  int c01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(c01_m1_indices); i++) global_latt_defns[LATT_C01][BLOCK_M1][c01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(c01_u1_indices); i++) global_latt_defns[LATT_C01][BLOCK_U1][c01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(c01_u2_indices); i++) global_latt_defns[LATT_C01][BLOCK_U2][c01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(c01_u3_indices); i++) global_latt_defns[LATT_C01][BLOCK_U3][c01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(c01_u4_indices); i++) global_latt_defns[LATT_C01][BLOCK_U4][c01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(c01_u5_indices); i++) global_latt_defns[LATT_C01][BLOCK_U5][c01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(c01_m2_indices); i++) global_latt_defns[LATT_C01][BLOCK_M2][c01_m2_indices[i]] = true;

  int d01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int d01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_T1, MAG_D2, MAG_D2Q};
  int d01_u2_indices[] = {MAG_Q4, MAG_S4, MAG_S3, MAG_T1, MAG_D2, MAG_D2Q};
  int d01_u3_indices[] = {MAG_R1, MAG_S5, MAG_S3, MAG_T2, MAG_D3, MAG_D3Q};
  int d01_u4_indices[] = {MAG_Q4, MAG_S4, MAG_S3, MAG_T1, MAG_D2, MAG_D2Q};
  int d01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_T1, MAG_D2, MAG_D2Q};
  int d01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(d01_m1_indices); i++) global_latt_defns[LATT_D01][BLOCK_M1][d01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(d01_u1_indices); i++) global_latt_defns[LATT_D01][BLOCK_U1][d01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(d01_u2_indices); i++) global_latt_defns[LATT_D01][BLOCK_U2][d01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(d01_u3_indices); i++) global_latt_defns[LATT_D01][BLOCK_U3][d01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(d01_u4_indices); i++) global_latt_defns[LATT_D01][BLOCK_U4][d01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(d01_u5_indices); i++) global_latt_defns[LATT_D01][BLOCK_U5][d01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(d01_m2_indices); i++) global_latt_defns[LATT_D01][BLOCK_M2][d01_m2_indices[i]] = true;

  int e01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int e01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_T1, MAG_D2, MAG_D2Q};
  int e01_u2_indices[] = {MAG_Q4, MAG_S4, MAG_S3, MAG_T1, MAG_D2};
  int e01_u3_indices[] = {MAG_R1, MAG_S5, MAG_S3, MAG_T2, MAG_D3, MAG_D3Q};
  int e01_u4_indices[] = {MAG_Q4, MAG_S4, MAG_S3, MAG_T1, MAG_D2};
  int e01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_S3, MAG_T1, MAG_D2, MAG_D2Q};
  int e01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(e01_m1_indices); i++) global_latt_defns[LATT_E01][BLOCK_M1][e01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(e01_u1_indices); i++) global_latt_defns[LATT_E01][BLOCK_U1][e01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(e01_u2_indices); i++) global_latt_defns[LATT_E01][BLOCK_U2][e01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(e01_u3_indices); i++) global_latt_defns[LATT_E01][BLOCK_U3][e01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(e01_u4_indices); i++) global_latt_defns[LATT_E01][BLOCK_U4][e01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(e01_u5_indices); i++) global_latt_defns[LATT_E01][BLOCK_U5][e01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(e01_m2_indices); i++) global_latt_defns[LATT_E01][BLOCK_M2][e01_m2_indices[i]] = true;

  int f01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int f01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_R1, MAG_S3, MAG_D2, MAG_D2Q};
  int f01_u2_indices[] = {MAG_R1, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q, MAG_S3};
  int f01_u3_indices[] = {MAG_R1, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q};
  int f01_u4_indices[] = {MAG_R1, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q, MAG_S3};
  int f01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_R1, MAG_S3, MAG_D2, MAG_D2Q};
  int f01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(f01_m1_indices); i++) global_latt_defns[LATT_F01][BLOCK_M1][f01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f01_u1_indices); i++) global_latt_defns[LATT_F01][BLOCK_U1][f01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f01_u2_indices); i++) global_latt_defns[LATT_F01][BLOCK_U2][f01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f01_u3_indices); i++) global_latt_defns[LATT_F01][BLOCK_U3][f01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f01_u4_indices); i++) global_latt_defns[LATT_F01][BLOCK_U4][f01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f01_u5_indices); i++) global_latt_defns[LATT_F01][BLOCK_U5][f01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f01_m2_indices); i++) global_latt_defns[LATT_F01][BLOCK_M2][f01_m2_indices[i]] = true;

  int f02_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int f02_u1_indices[] = {MAG_Q3, MAG_S2, MAG_R1, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int f02_u2_indices[] = {MAG_R1, MAG_S4, MAG_R2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int f02_u3_indices[] = {MAG_R2, MAG_S5, MAG_R3, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int f02_u4_indices[] = {MAG_R1, MAG_S4, MAG_R2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int f02_u5_indices[] = {MAG_Q3, MAG_S2, MAG_R1, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int f02_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(f02_m1_indices); i++) global_latt_defns[LATT_F02][BLOCK_M1][f02_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f02_u1_indices); i++) global_latt_defns[LATT_F02][BLOCK_U1][f02_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f02_u2_indices); i++) global_latt_defns[LATT_F02][BLOCK_U2][f02_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f02_u3_indices); i++) global_latt_defns[LATT_F02][BLOCK_U3][f02_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f02_u4_indices); i++) global_latt_defns[LATT_F02][BLOCK_U4][f02_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f02_u5_indices); i++) global_latt_defns[LATT_F02][BLOCK_U5][f02_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f02_m2_indices); i++) global_latt_defns[LATT_F02][BLOCK_M2][f02_m2_indices[i]] = true;

  int g01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINED};
  int g01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_R1, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int g01_u2_indices[] = {MAG_R1, MAG_S4, MAG_R2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int g01_u3_indices[] = {MAG_R2, MAG_S5, MAG_R3, MAG_S3_COMBINED, MAG_D3, MAG_D3Q};
  int g01_u4_indices[] = {MAG_R1, MAG_S4, MAG_R2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int g01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_R1, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int g01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINED};
  for (size_t i=0; i<ARRAY_LEN(g01_m1_indices); i++) global_latt_defns[LATT_G01][BLOCK_M1][g01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(g01_u1_indices); i++) global_latt_defns[LATT_G01][BLOCK_U1][g01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(g01_u2_indices); i++) global_latt_defns[LATT_G01][BLOCK_U2][g01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(g01_u3_indices); i++) global_latt_defns[LATT_G01][BLOCK_U3][g01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(g01_u4_indices); i++) global_latt_defns[LATT_G01][BLOCK_U4][g01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(g01_u5_indices); i++) global_latt_defns[LATT_G01][BLOCK_U5][g01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(g01_m2_indices); i++) global_latt_defns[LATT_G01][BLOCK_M2][g01_m2_indices[i]] = true;

  int h01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINED};
  int h01_u1_indices[] = {MAG_R1, MAG_S2, MAG_R2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int h01_u2_indices[] = {MAG_R2, MAG_S2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int h01_u3_indices[] = {MAG_R2, MAG_S2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int h01_u4_indices[] = {MAG_R2, MAG_S2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int h01_u5_indices[] = {MAG_R1, MAG_S2, MAG_R2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int h01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINED};
  for (size_t i=0; i<ARRAY_LEN(h01_m1_indices); i++) global_latt_defns[LATT_H01][BLOCK_M1][h01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h01_u1_indices); i++) global_latt_defns[LATT_H01][BLOCK_U1][h01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h01_u2_indices); i++) global_latt_defns[LATT_H01][BLOCK_U2][h01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h01_u3_indices); i++) global_latt_defns[LATT_H01][BLOCK_U3][h01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h01_u4_indices); i++) global_latt_defns[LATT_H01][BLOCK_U4][h01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h01_u5_indices); i++) global_latt_defns[LATT_H01][BLOCK_U5][h01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h01_m2_indices); i++) global_latt_defns[LATT_H01][BLOCK_M2][h01_m2_indices[i]] = true;

  int h02_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINED};
  int h02_u1_indices[] = {MAG_R1, MAG_S2, MAG_R2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int h02_u2_indices[] = {MAG_R2, MAG_S4, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int h02_u3_indices[] = {MAG_R2, MAG_S4, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int h02_u4_indices[] = {MAG_R2, MAG_S4, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int h02_u5_indices[] = {MAG_R1, MAG_S2, MAG_R2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int h02_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINED};
  for (size_t i=0; i<ARRAY_LEN(h02_m1_indices); i++) global_latt_defns[LATT_H02][BLOCK_M1][h02_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h02_u1_indices); i++) global_latt_defns[LATT_H02][BLOCK_U1][h02_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h02_u2_indices); i++) global_latt_defns[LATT_H02][BLOCK_U2][h02_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h02_u3_indices); i++) global_latt_defns[LATT_H02][BLOCK_U3][h02_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h02_u4_indices); i++) global_latt_defns[LATT_H02][BLOCK_U4][h02_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h02_u5_indices); i++) global_latt_defns[LATT_H02][BLOCK_U5][h02_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h02_m2_indices); i++) global_latt_defns[LATT_H02][BLOCK_M2][h02_m2_indices[i]] = true;

  int i01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINED};
  int i01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int i01_u2_indices[] = {MAG_Q4, MAG_S4, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int i01_u3_indices[] = {MAG_R1, MAG_S5, MAG_S6_COMBINED, MAG_D3, MAG_D3Q};
  int i01_u4_indices[] = {MAG_Q4, MAG_S4, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int i01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_S3_COMBINED, MAG_D2, MAG_D2Q};
  int i01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINED};
  for (size_t i=0; i<ARRAY_LEN(i01_m1_indices); i++) global_latt_defns[LATT_I01][BLOCK_M1][i01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(i01_u1_indices); i++) global_latt_defns[LATT_I01][BLOCK_U1][i01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(i01_u2_indices); i++) global_latt_defns[LATT_I01][BLOCK_U2][i01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(i01_u3_indices); i++) global_latt_defns[LATT_I01][BLOCK_U3][i01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(i01_u4_indices); i++) global_latt_defns[LATT_I01][BLOCK_U4][i01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(i01_u5_indices); i++) global_latt_defns[LATT_I01][BLOCK_U5][i01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(i01_m2_indices); i++) global_latt_defns[LATT_I01][BLOCK_M2][i01_m2_indices[i]] = true;
}

bool get_blocks_replaced(FamilyDefn fam, bool *blocks_replaced_array, size_t num_blocks) {
  LatticeType lat_type = get_lattice_type_from_name(fam.name);
  if (lat_type == LATT_UNKNOWN) {
    printf("WARNING: Layout of \"%s\" is unknown.\n", fam.name);
    return false;
  }

  for (size_t block_ind=0; block_ind<num_blocks; block_ind++) {
    for (size_t mag_ind=0; mag_ind<MAG_COUNT; mag_ind++) {
      if (global_latt_defns[lat_type][block_ind][mag_ind] && replace_due_to_mag(fam.cls[mag_ind])) {
        blocks_replaced_array[block_ind] = true;
        break;
      }
    }
  }
  return true;
}

bool any_true(bool *array, size_t len) {
  for (size_t i=0; i<len; i++)
    if (array[i]) return true;
  return false;
}

bool replace_due_to_mag(int cl) {
  return cl >= 10;
}

double total_block_replacement_costs(bool *blocks_replaced, double *costs, size_t block_count) {
  double cost = 0;
  for (size_t block_ind=0; block_ind<block_count; block_ind++)
    if (blocks_replaced[block_ind]) cost += costs[block_ind];
  return cost;
}

LatticeType get_lattice_type_from_name(const char *name) {
  if (strcmp(name, "m4 Standard Lattice") == 0) return LATT_A01;
  if (strlen(name) < 10) return LATT_UNKNOWN;
  if (strncmp(name+7, "a01", 3) == 0) return LATT_A01;
  if (strncmp(name+7, "a02", 3) == 0) return LATT_A02;
  if (strncmp(name+7, "b01", 3) == 0) return LATT_B01;
  if (strncmp(name+7, "b02", 3) == 0) return LATT_B02;
  if (strncmp(name+7, "b03", 3) == 0) return LATT_B03;
  if (strncmp(name+7, "c01", 3) == 0) return LATT_C01;
  if (strncmp(name+7, "d01", 3) == 0) return LATT_D01;
  if (strncmp(name+7, "e01", 3) == 0) return LATT_E01;
  if (strncmp(name+7, "f01", 3) == 0) return LATT_F01;
  if (strncmp(name+7, "f02", 3) == 0) return LATT_F02;
  if (strncmp(name+7, "g01", 3) == 0) return LATT_G01;
  if (strncmp(name+7, "h01", 3) == 0) return LATT_H01;
  if (strncmp(name+7, "h02", 3) == 0) return LATT_H02;
  if (strncmp(name+7, "i01", 3) == 0) return LATT_I01;
  return LATT_UNKNOWN;
}

int print_sheet_name(const char *name, void *callbackdata) {
  (void)callbackdata;
  printf("name = %s\n", name);
  return 0;
}

int get_lattice_summaries(const char *latt_summ_filename, FamilyDefns *fam_defns) {
  const char *sheetname = "Summaries";
  xlsxioreader xlsxioread = xlsxioread_open(latt_summ_filename);
  if (xlsxioread == NULL)
    return -1;

  xlsxioread_process(xlsxioread, sheetname, XLSXIOREAD_SKIP_NONE, &get_fam_locs_callback, &row_callback, &(fam_defns->fam_locs));
  xlsxioread_process(xlsxioread, sheetname, XLSXIOREAD_SKIP_NONE, &get_fam_strengths_callback, &row_callback, fam_defns);
  xlsxioread_close(xlsxioread);

  return 0;
}

int get_fam_locs_callback(size_t row, size_t col, const char* value, void* callbackdata) {
  FamilyLocations *fam_locs = (FamilyLocations*)callbackdata;

  if (value == NULL) return 0;
  if (row != 2) return 0;

  if (strcmp(value, "Hardware Check\n?")==0) {
    fam_locs->HW_check = col;
  } else if (strcmp(value, "D1")==0) {
    if (fam_locs->D1_value == 0) {
      fam_locs->D1_value  = col;
      fam_locs->D1q_value = col + 1;
    } else {
      fam_locs->D1_cl  = col;
      fam_locs->D1q_cl = col + 1;
    }
  }
  else if (strcmp(value, "D2")==0) {
    if (fam_locs->D2_value == 0) {
      fam_locs->D2_value  = col;
      fam_locs->D2q_value = col + 1;
    } else {
      fam_locs->D2_cl  = col;
      fam_locs->D2q_cl = col + 1;
    }
  }
  else if (strcmp(value, "D3")==0) {
    if (fam_locs->D3_value == 0) {
      fam_locs->D3_value  = col;
      fam_locs->D3q_value = col + 1;
    } else {
      fam_locs->D3_cl  = col;
      fam_locs->D3q_cl = col + 1;
    }
  }
  else if (strcmp(value, "Q1")==0) {
    if (fam_locs->Q1_value == 0) fam_locs->Q1_value = col;
    else fam_locs->Q1_cl = col;
  }
  else if (strcmp(value, "Q2")==0) {
    if (fam_locs->Q2_value == 0) fam_locs->Q2_value = col;
    else fam_locs->Q2_cl = col;
  }
  else if (strcmp(value, "Q3")==0) {
    if (fam_locs->Q3_value == 0) fam_locs->Q3_value = col;
    else fam_locs->Q3_cl = col;
  }
  else if (strcmp(value, "Q4")==0) {
    if (fam_locs->Q4_value == 0) fam_locs->Q4_value = col;
    else fam_locs->Q4_cl = col;
  }
  else if (strcmp(value, "Q5")==0) {
    if (fam_locs->Q5_value == 0) fam_locs->Q5_value = col;
    else fam_locs->Q5_cl = col;
  }
  else if (strcmp(value, "Q6")==0) {
    if (fam_locs->Q6_value == 0) fam_locs->Q6_value = col;
    else fam_locs->Q6_cl = col;
  }
  else if (strcmp(value, "R1")==0) {
    if (fam_locs->R1_value == 0) fam_locs->R1_value = col;
    else fam_locs->R1_cl = col + 1;
  }
  else if (strcmp(value, "R2")==0) {
    if (fam_locs->R2_value == 0) fam_locs->R2_value = col;
    else fam_locs->R2_cl = col + 1;
  }
  else if (strcmp(value, "R3")==0) {
    if (fam_locs->R3_value == 0) fam_locs->R3_value = col;
    else fam_locs->R3_cl = col + 1;
  }
  else if (strcmp(value, "S1")==0) {
    if (fam_locs->S1_value == 0) fam_locs->S1_value = col;
    else fam_locs->S1_cl = col;
  }
  else if (strcmp(value, "S2")==0) {
    if (fam_locs->S2_value == 0) fam_locs->S2_value = col;
    else fam_locs->S2_cl = col;
  }
  else if (strcmp(value, "S3")==0) {
    if (fam_locs->S3_value == 0) fam_locs->S3_value = col;
    else fam_locs->S3_cl = col;
  }
  else if (strcmp(value, "S4")==0) {
    if (fam_locs->S4_value == 0) fam_locs->S4_value = col;
    else fam_locs->S4_cl = col;
  }
  else if (strcmp(value, "S5")==0) {
    if (fam_locs->S5_value == 0) fam_locs->S5_value = col;
    else fam_locs->S5_cl = col;
  }
  else if (strcmp(value, "S6")==0) {
    if (fam_locs->S6_value == 0) fam_locs->S6_value = col;
    else fam_locs->S6_cl = col;
  }
  else if (strcmp(value, "O1")==0) {
    if (fam_locs->O1_value == 0) fam_locs->O1_value = col;
    else fam_locs->O1_cl = col;
  }
  else if (strcmp(value, "O2")==0) {
    if (fam_locs->O2_value == 0) fam_locs->O2_value = col;
    else fam_locs->O2_cl = col;
  }
  else if (strcmp(value, "O3")==0) {
    if (fam_locs->O3_value == 0) fam_locs->O3_value = col;
    else fam_locs->O3_cl = col;
  }
  else if (strcmp(value, "T1")==0) {
    if (fam_locs->T1_value == 0) fam_locs->T1_value = col;
    else fam_locs->T1_cl = col;
  }
  else if (strcmp(value, "T2")==0) {
    if (fam_locs->T2_value == 0) fam_locs->T2_value = col;
    else fam_locs->T2_cl = col;
  }
  else if (strcmp(value, "S1_combined")==0) {
    if (fam_locs->S1_combined_value == 0) fam_locs->S1_combined_value = col;
    else fam_locs->S1_combined_cl = col;
  }
  else if (strcmp(value, "S3_combined")==0) {
    if (fam_locs->S3_combined_value == 0) fam_locs->S3_combined_value = col;
    else fam_locs->S3_combined_cl = col;
  }
  else if (strcmp(value, "S6_combined")==0) {
    if (fam_locs->S6_combined_value == 0) fam_locs->S6_combined_value = col;
    else fam_locs->S6_combined_cl = col;
  }

  return 0;
}

int get_fam_strengths_callback(size_t row, size_t col, const char* value, void* callbackdata) {
  FamilyDefns *fam_defns = (FamilyDefns*)callbackdata;
  if (value == NULL) return 0;
  if (row < 7) return 0;

  if (col == 2) {
    // printf("Found a new family: '%s'\n", value);
    FamilyDefn new_family = {0};
    new_family.name = SDM_MALLOC(strlen(value) + 1);
    strcpy(new_family.name, value);
    SDM_ARRAY_PUSH(*fam_defns, new_family);
    return 0;
  }

  size_t index_of_last = fam_defns->length - 1;

  if      (col == fam_defns->fam_locs.D1_value) fam_defns->data[index_of_last].values[MAG_D1] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D2_value) fam_defns->data[index_of_last].values[MAG_D2] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D3_value) fam_defns->data[index_of_last].values[MAG_D3] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D1q_value) fam_defns->data[index_of_last].values[MAG_D1Q] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D2q_value) fam_defns->data[index_of_last].values[MAG_D2Q] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D3q_value) fam_defns->data[index_of_last].values[MAG_D3Q] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q1_value) fam_defns->data[index_of_last].values[MAG_Q1] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q2_value) fam_defns->data[index_of_last].values[MAG_Q2] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q3_value) fam_defns->data[index_of_last].values[MAG_Q3] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q4_value) fam_defns->data[index_of_last].values[MAG_Q4] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q5_value) fam_defns->data[index_of_last].values[MAG_Q5] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.Q6_value) fam_defns->data[index_of_last].values[MAG_Q6] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R1_value) fam_defns->data[index_of_last].values[MAG_R1] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R2_value) fam_defns->data[index_of_last].values[MAG_R2] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R3_value) fam_defns->data[index_of_last].values[MAG_R3] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S1_value) fam_defns->data[index_of_last].values[MAG_S1] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S2_value) fam_defns->data[index_of_last].values[MAG_S2] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S3_value) fam_defns->data[index_of_last].values[MAG_S3] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S4_value) fam_defns->data[index_of_last].values[MAG_S4] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S5_value) fam_defns->data[index_of_last].values[MAG_S5] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S6_value) fam_defns->data[index_of_last].values[MAG_S6] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.O1_value) fam_defns->data[index_of_last].values[MAG_O1] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.O2_value) fam_defns->data[index_of_last].values[MAG_O2] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.O3_value) fam_defns->data[index_of_last].values[MAG_O3] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.T1_value) fam_defns->data[index_of_last].values[MAG_T1] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.T2_value) fam_defns->data[index_of_last].values[MAG_T2] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S1_combined_value) fam_defns->data[index_of_last].values[MAG_S1_COMBINED] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S3_combined_value) fam_defns->data[index_of_last].values[MAG_S3_COMBINED] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S6_combined_value) fam_defns->data[index_of_last].values[MAG_S6_COMBINED] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.D1_cl) fam_defns->data[index_of_last].cls[MAG_D1] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.D2_cl) fam_defns->data[index_of_last].cls[MAG_D2] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.D3_cl) fam_defns->data[index_of_last].cls[MAG_D3] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.D1q_cl) fam_defns->data[index_of_last].cls[MAG_D1Q] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.D2q_cl) fam_defns->data[index_of_last].cls[MAG_D2Q] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.D3q_cl) fam_defns->data[index_of_last].cls[MAG_D3Q] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.Q1_cl) fam_defns->data[index_of_last].cls[MAG_Q1] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.Q2_cl) fam_defns->data[index_of_last].cls[MAG_Q2] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.Q3_cl) fam_defns->data[index_of_last].cls[MAG_Q3] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.Q4_cl) fam_defns->data[index_of_last].cls[MAG_Q4] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.Q5_cl) fam_defns->data[index_of_last].cls[MAG_Q5] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.Q6_cl) fam_defns->data[index_of_last].cls[MAG_Q6] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R1_cl) fam_defns->data[index_of_last].cls[MAG_R1] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R2_cl) fam_defns->data[index_of_last].cls[MAG_R2] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R3_cl) fam_defns->data[index_of_last].cls[MAG_R3] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S1_cl) fam_defns->data[index_of_last].cls[MAG_S1] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S2_cl) fam_defns->data[index_of_last].cls[MAG_S2] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S3_cl) fam_defns->data[index_of_last].cls[MAG_S3] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S4_cl) fam_defns->data[index_of_last].cls[MAG_S4] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S5_cl) fam_defns->data[index_of_last].cls[MAG_S5] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S6_cl) fam_defns->data[index_of_last].cls[MAG_S6] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.O1_cl) fam_defns->data[index_of_last].cls[MAG_O1] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.O2_cl) fam_defns->data[index_of_last].cls[MAG_O2] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.O3_cl) fam_defns->data[index_of_last].cls[MAG_O3] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.T1_cl) fam_defns->data[index_of_last].cls[MAG_T1] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.T2_cl) fam_defns->data[index_of_last].cls[MAG_T2] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S1_combined_cl) fam_defns->data[index_of_last].cls[MAG_S1_COMBINED] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S3_combined_cl) fam_defns->data[index_of_last].cls[MAG_S3_COMBINED] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S6_combined_cl) fam_defns->data[index_of_last].cls[MAG_S6_COMBINED] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.HW_check) {
    if (value != NULL) {
      if (strncmp(value, "Y", 1) == 0) {
        fam_defns->data[index_of_last].HW_check = true;
      }
    }
  }

  return 0;
}

const char *block_type_string(BlockType t) {
  switch (t) {
    case BLOCK_M1: return "M1";
    case BLOCK_U1: return "U1";
    case BLOCK_U2: return "U2";
    case BLOCK_U3: return "U3";
    case BLOCK_U4: return "U4";
    case BLOCK_U5: return "U5";
    case BLOCK_M2: return "M2";
    case BLOCK_COUNT: {
      fprintf(stderr, "ERROR: Block type is ill-defined. This should be unreachable.\n");
      exit(1);
    }
  }
}

int row_callback(size_t row, size_t maxcol, void* callbackdata) {
  (void)callbackdata;
  (void)maxcol;
  (void)row;
  return 0;
}

void concat_strings(const char *str1, const char *str2, char *buffer, size_t buff_len) {
  assert(strlen(str1) + strlen(str2) < buff_len && "Your buffer is too small");
  memset(buffer, 0, buff_len);
  strcpy(buffer, str1);
  strcpy(buffer+strlen(str1), str2);
}

bool ends_with(const char *str, const char *suffix) {
    if (!str || !suffix) return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix >  lenstr) return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

