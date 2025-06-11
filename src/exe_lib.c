#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <xlsxio_read.h>

#include "exe_lib.h"
#include "sdm_lib.h"

extern LatticeDefinition global_latt_defns[LATT_COUNT];
extern double block_mass[BLOCK_COUNT];
extern double block_costs[BLOCK_COUNT];
extern double EUR_PER_METRICTONNE_STEEL;
double EUR2SEK;
double POLECOST;
double POLEFACESTRIPCOST;

void set_block_costs(void) {
  set_block_build_costs();
  set_block_masses();

  double sek_per_kg_steel = (EUR_PER_METRICTONNE_STEEL / 1000.0) * EUR2SEK;

  block_costs[BLOCK_M1] += block_mass[BLOCK_M1] * sek_per_kg_steel;
  block_costs[BLOCK_M2] += block_mass[BLOCK_M2] * sek_per_kg_steel;
  block_costs[BLOCK_U1] += block_mass[BLOCK_U1] * sek_per_kg_steel;
  block_costs[BLOCK_U2] += block_mass[BLOCK_U2] * sek_per_kg_steel;
  block_costs[BLOCK_U4] += block_mass[BLOCK_U4] * sek_per_kg_steel;
  block_costs[BLOCK_U5] += block_mass[BLOCK_U5] * sek_per_kg_steel;
  block_costs[BLOCK_U3] += block_mass[BLOCK_U3] * sek_per_kg_steel;
}

void set_block_masses(void) {
  block_mass[BLOCK_M1] = 2.5e3; // kg
  block_mass[BLOCK_M2] = 2.5e3; // kg
  block_mass[BLOCK_U1] = 2.5e3; // kg
  block_mass[BLOCK_U2] = 2.5e3; // kg
  block_mass[BLOCK_U4] = 2.5e3; // kg
  block_mass[BLOCK_U5] = 2.5e3; // kg
  block_mass[BLOCK_U3] = 2.5e3; // kg
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
  int b01_u3_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S5, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3, MAG_D3, MAG_D3Q};
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
  int b02_u3_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S5, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S6, MAG_D3, MAG_D3Q};
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
  int b03_u3_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S5, MAG_S3, MAG_D3, MAG_D3Q};
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
  int c01_u1_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S2, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3, MAG_D2, MAG_D2Q};
  int c01_u2_indices[] = {MAG_R3Q, MAG_R3D, MAG_R3OFFS, MAG_S4, MAG_S3, MAG_D2, MAG_D2Q};
  int c01_u3_indices[] = {MAG_R3Q, MAG_R3D, MAG_R3OFFS, MAG_S5, MAG_S3, MAG_D2, MAG_D2Q};
  int c01_u4_indices[] = {MAG_R3Q, MAG_R3D, MAG_R3OFFS, MAG_S4, MAG_S3, MAG_D2, MAG_D2Q};
  int c01_u5_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S2, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3, MAG_D2, MAG_D2Q};
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
  int d01_u3_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S5, MAG_S3, MAG_T2, MAG_D3, MAG_D3Q};
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
  int e01_u3_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S5, MAG_S3, MAG_T2, MAG_D3, MAG_D3Q};
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
  int f01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S3, MAG_D2, MAG_D2Q};
  int f01_u2_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q, MAG_S3};
  int f01_u3_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q};
  int f01_u4_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S2, MAG_S3, MAG_D2, MAG_D2Q, MAG_S3};
  int f01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S3, MAG_D2, MAG_D2Q};
  int f01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(f01_m1_indices); i++) global_latt_defns[LATT_F01][BLOCK_M1][f01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f01_u1_indices); i++) global_latt_defns[LATT_F01][BLOCK_U1][f01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f01_u2_indices); i++) global_latt_defns[LATT_F01][BLOCK_U2][f01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f01_u3_indices); i++) global_latt_defns[LATT_F01][BLOCK_U3][f01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f01_u4_indices); i++) global_latt_defns[LATT_F01][BLOCK_U4][f01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f01_u5_indices); i++) global_latt_defns[LATT_F01][BLOCK_U5][f01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f01_m2_indices); i++) global_latt_defns[LATT_F01][BLOCK_M2][f01_m2_indices[i]] = true;

  int f02_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  int f02_u1_indices[] = {MAG_Q3, MAG_S2, MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int f02_u2_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S4, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int f02_u3_indices[] = {MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S5, MAG_R3Q, MAG_R3D, MAG_R3OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int f02_u4_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S4, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int f02_u5_indices[] = {MAG_Q3, MAG_S2, MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int f02_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1};
  for (size_t i=0; i<ARRAY_LEN(f02_m1_indices); i++) global_latt_defns[LATT_F02][BLOCK_M1][f02_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f02_u1_indices); i++) global_latt_defns[LATT_F02][BLOCK_U1][f02_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f02_u2_indices); i++) global_latt_defns[LATT_F02][BLOCK_U2][f02_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f02_u3_indices); i++) global_latt_defns[LATT_F02][BLOCK_U3][f02_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f02_u4_indices); i++) global_latt_defns[LATT_F02][BLOCK_U4][f02_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f02_u5_indices); i++) global_latt_defns[LATT_F02][BLOCK_U5][f02_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(f02_m2_indices); i++) global_latt_defns[LATT_F02][BLOCK_M2][f02_m2_indices[i]] = true;

  int g01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  int g01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int g01_u2_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S4, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int g01_u3_indices[] = {MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S5, MAG_R3Q, MAG_R3D, MAG_R3OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D3, MAG_D3Q};
  int g01_u4_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S4, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int g01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int g01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  for (size_t i=0; i<ARRAY_LEN(g01_m1_indices); i++) global_latt_defns[LATT_G01][BLOCK_M1][g01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(g01_u1_indices); i++) global_latt_defns[LATT_G01][BLOCK_U1][g01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(g01_u2_indices); i++) global_latt_defns[LATT_G01][BLOCK_U2][g01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(g01_u3_indices); i++) global_latt_defns[LATT_G01][BLOCK_U3][g01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(g01_u4_indices); i++) global_latt_defns[LATT_G01][BLOCK_U4][g01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(g01_u5_indices); i++) global_latt_defns[LATT_G01][BLOCK_U5][g01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(g01_m2_indices); i++) global_latt_defns[LATT_G01][BLOCK_M2][g01_m2_indices[i]] = true;

  int h01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  int h01_u1_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S2, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int h01_u2_indices[] = {MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S2, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int h01_u3_indices[] = {MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S2, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int h01_u4_indices[] = {MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S2, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int h01_u5_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S2, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int h01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  for (size_t i=0; i<ARRAY_LEN(h01_m1_indices); i++) global_latt_defns[LATT_H01][BLOCK_M1][h01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h01_u1_indices); i++) global_latt_defns[LATT_H01][BLOCK_U1][h01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h01_u2_indices); i++) global_latt_defns[LATT_H01][BLOCK_U2][h01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h01_u3_indices); i++) global_latt_defns[LATT_H01][BLOCK_U3][h01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h01_u4_indices); i++) global_latt_defns[LATT_H01][BLOCK_U4][h01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h01_u5_indices); i++) global_latt_defns[LATT_H01][BLOCK_U5][h01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h01_m2_indices); i++) global_latt_defns[LATT_H01][BLOCK_M2][h01_m2_indices[i]] = true;

  int h02_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  int h02_u1_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S2, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int h02_u2_indices[] = {MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S4, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int h02_u3_indices[] = {MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S4, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int h02_u4_indices[] = {MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S4, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int h02_u5_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S2, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int h02_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  for (size_t i=0; i<ARRAY_LEN(h02_m1_indices); i++) global_latt_defns[LATT_H02][BLOCK_M1][h02_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h02_u1_indices); i++) global_latt_defns[LATT_H02][BLOCK_U1][h02_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h02_u2_indices); i++) global_latt_defns[LATT_H02][BLOCK_U2][h02_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h02_u3_indices); i++) global_latt_defns[LATT_H02][BLOCK_U3][h02_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h02_u4_indices); i++) global_latt_defns[LATT_H02][BLOCK_U4][h02_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h02_u5_indices); i++) global_latt_defns[LATT_H02][BLOCK_U5][h02_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(h02_m2_indices); i++) global_latt_defns[LATT_H02][BLOCK_M2][h02_m2_indices[i]] = true;

  int i01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  int i01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int i01_u2_indices[] = {MAG_Q4, MAG_S4, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int i01_u3_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S5, MAG_S6_COMBINEDS, MAG_S6_COMBINEDQ, MAG_D3, MAG_D3Q};
  int i01_u4_indices[] = {MAG_Q4, MAG_S4, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int i01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int i01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  for (size_t i=0; i<ARRAY_LEN(i01_m1_indices); i++) global_latt_defns[LATT_I01][BLOCK_M1][i01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(i01_u1_indices); i++) global_latt_defns[LATT_I01][BLOCK_U1][i01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(i01_u2_indices); i++) global_latt_defns[LATT_I01][BLOCK_U2][i01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(i01_u3_indices); i++) global_latt_defns[LATT_I01][BLOCK_U3][i01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(i01_u4_indices); i++) global_latt_defns[LATT_I01][BLOCK_U4][i01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(i01_u5_indices); i++) global_latt_defns[LATT_I01][BLOCK_U5][i01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(i01_m2_indices); i++) global_latt_defns[LATT_I01][BLOCK_M2][i01_m2_indices[i]] = true;

  int j01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  int j01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int j01_u2_indices[] = {MAG_Q4, MAG_S4, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int j01_u3_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S5, MAG_S6_COMBINEDS, MAG_S6_COMBINEDQ, MAG_D3, MAG_D3Q};
  int j01_u4_indices[] = {MAG_Q4, MAG_S4, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int j01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int j01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  for (size_t i=0; i<ARRAY_LEN(j01_m1_indices); i++) global_latt_defns[LATT_J01][BLOCK_M1][j01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(j01_u1_indices); i++) global_latt_defns[LATT_J01][BLOCK_U1][j01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(j01_u2_indices); i++) global_latt_defns[LATT_J01][BLOCK_U2][j01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(j01_u3_indices); i++) global_latt_defns[LATT_J01][BLOCK_U3][j01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(j01_u4_indices); i++) global_latt_defns[LATT_J01][BLOCK_U4][j01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(j01_u5_indices); i++) global_latt_defns[LATT_J01][BLOCK_U5][j01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(j01_m2_indices); i++) global_latt_defns[LATT_J01][BLOCK_M2][j01_m2_indices[i]] = true;

  int k01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  int k01_u1_indices[] = {MAG_Q3, MAG_S2, MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ, MAG_D2, MAG_D2Q, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ};
  int k01_u2_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S4, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q, MAG_S5_COMBINEDS, MAG_S5_COMBINEDQ,};
  int k01_u3_indices[] = {MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S6, MAG_S5_COMBINEDS, MAG_S5_COMBINEDQ, MAG_D3, MAG_D3Q};
  int k01_u4_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S4, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q, MAG_S5_COMBINEDS, MAG_S5_COMBINEDQ,};
  int k01_u5_indices[] = {MAG_Q3, MAG_S2, MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ, MAG_D2, MAG_D2Q, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ};
  int k01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  for (size_t i=0; i<ARRAY_LEN(k01_m1_indices); i++) global_latt_defns[LATT_K01][BLOCK_M1][k01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(k01_u1_indices); i++) global_latt_defns[LATT_K01][BLOCK_U1][k01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(k01_u2_indices); i++) global_latt_defns[LATT_K01][BLOCK_U2][k01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(k01_u3_indices); i++) global_latt_defns[LATT_K01][BLOCK_U3][k01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(k01_u4_indices); i++) global_latt_defns[LATT_K01][BLOCK_U4][k01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(k01_u5_indices); i++) global_latt_defns[LATT_K01][BLOCK_U5][k01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(k01_m2_indices); i++) global_latt_defns[LATT_K01][BLOCK_M2][k01_m2_indices[i]] = true;

  int l01_m1_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  int l01_u1_indices[] = {MAG_Q3, MAG_S2_COMBINEDS, MAG_S2_COMBINEDQ, MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int l01_u2_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S4_COMBINEDS, MAG_S4_COMBINEDQ, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int l01_u3_indices[] = {MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S5_COMBINEDS, MAG_S5_COMBINEDQ, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D3, MAG_D3Q};
  int l01_u4_indices[] = {MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S4_COMBINEDS, MAG_S4_COMBINEDQ, MAG_R2Q, MAG_R2D, MAG_R2OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int l01_u5_indices[] = {MAG_Q3, MAG_S2_COMBINEDS, MAG_S2_COMBINEDQ, MAG_R1Q, MAG_R1D, MAG_R1OFFS, MAG_S3_COMBINEDS, MAG_S3_COMBINEDQ, MAG_D2, MAG_D2Q};
  int l01_m2_indices[] = {MAG_O1, MAG_Q1, MAG_O2, MAG_Q2, MAG_D1, MAG_D1Q, MAG_O3, MAG_S1_COMBINEDS, MAG_S1_COMBINEDQ};
  for (size_t i=0; i<ARRAY_LEN(l01_m1_indices); i++) global_latt_defns[LATT_L01][BLOCK_M1][l01_m1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(l01_u1_indices); i++) global_latt_defns[LATT_L01][BLOCK_U1][l01_u1_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(l01_u2_indices); i++) global_latt_defns[LATT_L01][BLOCK_U2][l01_u2_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(l01_u3_indices); i++) global_latt_defns[LATT_L01][BLOCK_U3][l01_u3_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(l01_u4_indices); i++) global_latt_defns[LATT_L01][BLOCK_U4][l01_u4_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(l01_u5_indices); i++) global_latt_defns[LATT_L01][BLOCK_U5][l01_u5_indices[i]] = true;
  for (size_t i=0; i<ARRAY_LEN(l01_m2_indices); i++) global_latt_defns[LATT_L01][BLOCK_M2][l01_m2_indices[i]] = true;
}

bool get_blocks_work_details(FamilyDefn fam, BlockWork *blocks_replaced_array, size_t num_blocks) {
  LatticeType lat_type = get_lattice_type_from_name(fam.name);
  if (lat_type == LATT_UNKNOWN) {
    printf("WARNING: Layout of \"%s\" is unknown.\n", fam.name);
    return false;
  }

  for (size_t block_ind=0; block_ind<num_blocks; block_ind++) {
    for (size_t mag_ind=0; mag_ind<MAG_COUNT; mag_ind++) {
      if (global_latt_defns[lat_type][block_ind][mag_ind]) {
        BlockWork work_to_do = work_due_to_mag(fam.cls[mag_ind]);
        if (work_to_do == BLK_WORK_REPLACE) {
          blocks_replaced_array[block_ind] = BLK_WORK_REPLACE;
          break;
        } else if (work_to_do == BLK_WORK_MOD) {
          blocks_replaced_array[block_ind] = BLK_WORK_MOD;
        }
      }
    }
  }
  return true;
}

bool any_equal_to(BlockWork *array, size_t len, BlockWork needle) {
  for (size_t i=0; i<len; i++)
    if (array[i] == needle) return true;
  return false;
}

BlockWork work_due_to_mag(int cl) {
  if (cl >= 10) return BLK_WORK_REPLACE;
  if (cl >= 3) return BLK_WORK_MOD;
  if (cl >= 0) return BLK_WORK_NONE;
  fprintf(stderr, "ERROR: Challenge level of %d does not make sense\n", cl);
  exit(1);
}

double total_mag_ps_costs(bool *new_ps_needed, double *magPS_costs, CostType *cost_types, size_t mag_count) {
  double cost = 0;

  for (size_t i=0; i<mag_count; i++) {
    if (fake_magnet(i)) continue;
    if (!new_ps_needed[i]) continue;

    switch (cost_types[i]) {
      case COSTTYPE_INDEPENDENT:
      case COSTTYPE_PERACHRO: {
        cost += magPS_costs[i];
        break;
      }
      case COSTTYPE_PERBLK: {
        cost += magPS_costs[i] * BLOCK_COUNT;
        break;
      }
      case COSTTYPE_PERACHRO_IF_CHNGD:
      case COSTTYPE_PERBLK_IF_CHNGD: {
        fprintf(stderr, "ERROR: No magPS costs have this cost type\n");
        exit(1);
      }
      case COSTTYPE_COUNT: {
        fprintf(stderr, "UNREACHABLE\n");
        exit(1);
      }
    }
  }

  return cost;
}

double total_cooling_work_costs(BlockWork *block_work, double *costs, CostType *cost_types, size_t costs_length) {
  double cost = 0;
  for (size_t cost_ind=0; cost_ind<costs_length; cost_ind++) {
    switch (cost_types[cost_ind]) {
      case COSTTYPE_INDEPENDENT: {
        cost += costs[cost_ind];
      } break;
      case COSTTYPE_PERACHRO: {
        cost += costs[cost_ind];
      } break;
      case COSTTYPE_PERBLK: {
        cost += costs[cost_ind] * BLOCK_COUNT;
      } break;
      case COSTTYPE_PERACHRO_IF_CHNGD: {
        if (any_equal_to(block_work, BLOCK_COUNT, BLK_WORK_REPLACE)) {
          cost += costs[cost_ind];
        }
      } break;
      case COSTTYPE_PERBLK_IF_CHNGD: {
        for (size_t blk_ind=0; blk_ind<BLOCK_COUNT; blk_ind++) {
          if (block_work[blk_ind] == BLK_WORK_REPLACE) {
            cost += costs[cost_ind];
          }
        }
      } break;
      case COSTTYPE_COUNT: {
        fprintf(stderr, "ERROR: This case should be unreachable\n");
        exit(1);
      }
    }
  }

  return cost;
}

double total_block_work_costs(FamilyDefn fam, BlockWork *block_work, double *costs, size_t block_count) {
  LatticeType lat_type = get_lattice_type_from_name(fam.name);
  if (lat_type == LATT_UNKNOWN) {
    printf("WARNING: Layout of \"%s\" is unknown.\n", fam.name);
    return false;
  }

  double cost = 0;
  for (size_t block_ind=0; block_ind<block_count; block_ind++) {
    if (block_work[block_ind] == BLK_WORK_REPLACE)
      cost += costs[block_ind];
    if (block_work[block_ind] == BLK_WORK_MOD) {
      bool R1added=false, R2added=false, R3added=false;
      bool S1combadded=false, S2combadded=false, S3combadded=false, S4combadded=false, S5combadded=false, S6combadded=false;
      for (size_t mag_ind=0; mag_ind<MAG_COUNT; mag_ind++) {
        if (!global_latt_defns[lat_type][block_ind][mag_ind]) continue;
        BlockWork work_needed = work_due_to_mag(fam.cls[mag_ind]);
        if (work_needed == BLK_WORK_REPLACE) {
          fprintf(stderr, "ERROR: This is a bug. BLK_WORK_REPLACE is not possible here.\n");
          exit(1);
        } else if (work_needed == BLK_WORK_NONE) continue;
        switch ((MagType)mag_ind) {
          case MAG_D1: case MAG_D2: case MAG_D3: {
            fprintf(stderr, "ERROR: This is a bug. Dipoles should not be possible here.\n");
            exit(1);
          } break;
          case MAG_D1Q: case MAG_D2Q: case MAG_D3Q: {
            cost += 2 * POLEFACESTRIPCOST;
          } break;
          case MAG_Q1: case MAG_Q2: case MAG_Q3: case MAG_Q4: case MAG_Q5: case MAG_Q6: {
            cost += 4 * POLECOST;
            break;
          }
          case MAG_R1Q: case MAG_R1D: case MAG_R1OFFS: {
            if (R1added) break;
            R1added = true;
            cost += 4 * POLECOST;
            break;
          }
					case MAG_R2Q: case MAG_R2D: case MAG_R2OFFS: {
            if (R2added) break;
            R2added = true;
            cost += 4 * POLECOST;
            break;
          }
		  case MAG_R3Q: case MAG_R3D: case MAG_R3OFFS: {
            if (R3added) break;
            R3added = true;
            cost += 4 * POLECOST;
            break;
          }
          case MAG_S1: case MAG_S2: case MAG_S3: case MAG_S4: case MAG_S5: case MAG_S6: {
            cost += 6 * POLECOST;
            break;
          }
          case MAG_O1: case MAG_O2: case MAG_O3: {
            cost += 8 * POLECOST;
            break;
          }
          case MAG_T1: case MAG_T2: case MAG_S1_COMBINEDS: case MAG_S1_COMBINEDQ: {
            if (S1combadded) break;
            S1combadded = true;
            cost += 6 * POLECOST;
            break;
          }
          case MAG_S2_COMBINEDS: case MAG_S2_COMBINEDQ: {
            if (S2combadded) break;
            S2combadded = true;
            cost += 6 * POLECOST;
            break;
          }
          case MAG_S3_COMBINEDS: case MAG_S3_COMBINEDQ: {
            if (S3combadded) break;
            S3combadded = true;
            cost += 6 * POLECOST;
            break;
          }
          case MAG_S4_COMBINEDS: case MAG_S4_COMBINEDQ: {
            if (S4combadded) break;
            S4combadded = true;
            cost += 6 * POLECOST;
            break;
          }
          case MAG_S5_COMBINEDS: case MAG_S5_COMBINEDQ: {
            if (S5combadded) break;
            S5combadded = true;
            cost += 6 * POLECOST;
            break;
          }
          case MAG_S6_COMBINEDS: case MAG_S6_COMBINEDQ: {
            if (S6combadded) break;
            S6combadded = true;
            cost += 6 * POLECOST;
            break;
          }
          case MAG_COUNT: {
            fprintf(stderr, "ERROR: This is a bug. MAG_COUNT should be unreachable.\n");
            exit(1);
          }
        }
      }
    }
  }
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
  if (strncmp(name+7, "j01", 3) == 0) return LATT_J01;
  if (strncmp(name+7, "k01", 3) == 0) return LATT_K01;
  if (strncmp(name+7, "l01", 3) == 0) return LATT_L01;
  return LATT_UNKNOWN;
}

int print_sheet_name(const char *name, void *callbackdata) {
  (void)callbackdata;
  printf("name = %s\n", name);
  return 0;
}

int get_lattice_summaries(const char *latt_summ_filename, FamilyDefns *fam_defns, Info *info) {
  xlsxioreader xlsxioread = xlsxioread_open(latt_summ_filename);
  if (xlsxioread == NULL)
    return -1;

  const char *datasheet_name = "Summaries";
  const char *infosheet_name = "Info";

  xlsxioread_process(xlsxioread, datasheet_name, XLSXIOREAD_SKIP_NONE, &get_fam_locs_callback, &row_callback, &(fam_defns->fam_locs));
  xlsxioread_process(xlsxioread, datasheet_name, XLSXIOREAD_SKIP_NONE, &get_fam_strengths_callback, &row_callback, fam_defns);

  size_t count = 0;
  for (size_t i=0; i<fam_defns->length; i++) {
    if (fam_defns->data[i].HW_check) {
      SDM_ARRAY_SWAP((*fam_defns), i, count);
      count++;
    }
  }
  fam_defns->length = count;

  xlsxioread_process(xlsxioread, infosheet_name, XLSXIOREAD_SKIP_NONE, &get_info_details_callback, &row_callback, info);
  xlsxioread_close(xlsxioread);

  return 0;
}

int get_circuits_per_family(const char *circuit_def_filename, CircuitsInFamilyDefn *circuits_data) {
  xlsxioreader xlsxioread = xlsxioread_open(circuit_def_filename);

  const char *datasheet_name = "FullAchromat";

  size_t lattice_col[2 * LATT_COUNT] = {0};
  MagType current_magnet = MAG_COUNT;
  char *value;
  xlsxioreadersheet datasheet = xlsxioread_sheet_open(xlsxioread, datasheet_name, XLSXIOREAD_SKIP_ALL_EMPTY);
  while (xlsxioread_sheet_next_row(datasheet)) {
    size_t col = 0;
    while ((value = xlsxioread_sheet_next_cell(datasheet)) != NULL) {
      if (strcmp(value, "TOTAL") == 0) { col++; free(value); break; }
      else if (strcmp(value, "D1") == 0) { current_magnet = MAG_D1;  col++; free(value); continue; }
      else if (strcmp(value, "D2") == 0) { current_magnet = MAG_D2;  col++; free(value); continue; }
      else if (strcmp(value, "D3") == 0) { current_magnet = MAG_D3;  col++; free(value); continue; }
      else if (strcmp(value, "Q1") == 0) { current_magnet = MAG_Q1;  col++; free(value); continue; }
      else if (strcmp(value, "Q2") == 0) { current_magnet = MAG_Q2;  col++; free(value); continue; }
      else if (strcmp(value, "Q3") == 0) { current_magnet = MAG_Q3;  col++; free(value); continue; }
      else if (strcmp(value, "Q4") == 0) { current_magnet = MAG_Q4;  col++; free(value); continue; }
      else if (strcmp(value, "Q5") == 0) { current_magnet = MAG_Q5;  col++; free(value); continue; }
      else if (strcmp(value, "Q6") == 0) { current_magnet = MAG_Q6;  col++; free(value); continue; }
      else if (strcmp(value, "R1") == 0) { current_magnet = MAG_R1Q; col++; free(value); continue; }
      else if (strcmp(value, "R2") == 0) { current_magnet = MAG_R2Q; col++; free(value); continue; }
      else if (strcmp(value, "R3") == 0) { current_magnet = MAG_R3Q; col++; free(value); continue; }
      else if (strcmp(value, "S1") == 0) { current_magnet = MAG_S1;  col++; free(value); continue; }
      else if (strcmp(value, "S2") == 0) { current_magnet = MAG_S2;  col++; free(value); continue; }
      else if (strcmp(value, "S3") == 0) { current_magnet = MAG_S3;  col++; free(value); continue; }
      else if (strcmp(value, "S4") == 0) { current_magnet = MAG_S4;  col++; free(value); continue; }
      else if (strcmp(value, "S5") == 0) { current_magnet = MAG_S5;  col++; free(value); continue; }
      else if (strcmp(value, "S6") == 0) { current_magnet = MAG_S6;  col++; free(value); continue; }
      else if (strcmp(value, "O1") == 0) { current_magnet = MAG_O1;  col++; free(value); continue; }
      else if (strcmp(value, "O2") == 0) { current_magnet = MAG_O2;  col++; free(value); continue; }
      else if (strcmp(value, "O3") == 0) { current_magnet = MAG_O3;  col++; free(value); continue; }
      else if (strcmp(value, "T1") == 0) { current_magnet = MAG_T1;  col++; free(value); continue; }
      else if (strcmp(value, "T2") == 0) { current_magnet = MAG_T2;  col++; free(value); continue; }
      else if (strcmp(value, "S1_comb") == 0) { current_magnet = MAG_S1_COMBINEDS; col++; free(value); continue; }
      else if (strcmp(value, "S2_comb") == 0) { current_magnet = MAG_S2_COMBINEDS; col++; free(value); continue; }
      else if (strcmp(value, "S3_comb") == 0) { current_magnet = MAG_S3_COMBINEDS; col++; free(value); continue; }
      else if (strcmp(value, "S4_comb") == 0) { current_magnet = MAG_S4_COMBINEDS; col++; free(value); continue; }
      else if (strcmp(value, "S5_comb") == 0) { current_magnet = MAG_S5_COMBINEDS; col++; free(value); continue; }
      else if (strcmp(value, "S6_comb") == 0) { current_magnet = MAG_S6_COMBINEDS; col++; free(value); continue; }

      else if (strcmp(value, "a01") == 0) {lattice_col[col] = LATT_A01; col++; free(value); continue;}
      else if (strcmp(value, "a02") == 0) {lattice_col[col] = LATT_A02; col++; free(value); continue;}
      else if (strcmp(value, "b01") == 0) {lattice_col[col] = LATT_B01; col++; free(value); continue;}
      else if (strcmp(value, "b02") == 0) {lattice_col[col] = LATT_B02; col++; free(value); continue;}
      else if (strcmp(value, "b03") == 0) {lattice_col[col] = LATT_B03; col++; free(value); continue;}
      else if (strcmp(value, "c01") == 0) {lattice_col[col] = LATT_C01; col++; free(value); continue;}
      else if (strcmp(value, "d01") == 0) {lattice_col[col] = LATT_D01; col++; free(value); continue;}
      else if (strcmp(value, "e01") == 0) {lattice_col[col] = LATT_E01; col++; free(value); continue;}
      else if (strcmp(value, "f01") == 0) {lattice_col[col] = LATT_F01; col++; free(value); continue;}
      else if (strcmp(value, "f02") == 0) {lattice_col[col] = LATT_F02; col++; free(value); continue;}
      else if (strcmp(value, "g01") == 0) {lattice_col[col] = LATT_G01; col++; free(value); continue;}
      else if (strcmp(value, "h01") == 0) {lattice_col[col] = LATT_H01; col++; free(value); continue;}
      else if (strcmp(value, "h02") == 0) {lattice_col[col] = LATT_H02; col++; free(value); continue;}
      else if (strcmp(value, "i01") == 0) {lattice_col[col] = LATT_I01; col++; free(value); continue;}
      else if (strcmp(value, "j01") == 0) {lattice_col[col] = LATT_J01; col++; free(value); continue;}
      else if (strcmp(value, "k01") == 0) {lattice_col[col] = LATT_K01; col++; free(value); continue;}
      else if (strcmp(value, "l01") == 0) {lattice_col[col] = LATT_L01; col++; free(value); continue;}

      if (current_magnet == MAG_COUNT) {
        col++;
        free(value);
        continue;
      }

      circuits_data->circuits[lattice_col[col]][current_magnet] = atoi(value);

      col++;
      free(value);
    }
  }
  xlsxioread_sheet_close(datasheet);

  xlsxioread_close(xlsxioread);

  return 0;
}

const char *string_from_magtype(MagType type) {
  switch (type) {
    case MAG_D1: return "D1";
	case MAG_D1Q: return "D1Q";
	case MAG_D2: return "D2";
	case MAG_D2Q: return "D2Q";
	case MAG_D3: return "D3";
	case MAG_D3Q: return "D3Q";
    case MAG_Q1: return "Q1";
	case MAG_Q2: return "Q2";
	case MAG_Q3: return "Q3";
	case MAG_Q4: return "Q4";
	case MAG_Q5: return "Q5";
	case MAG_Q6: return "Q6";
    case MAG_R1Q: return "R1Q";
	case MAG_R1D: return "R1D";
	case MAG_R1OFFS: return "R1OFFS";
	case MAG_R2Q: return "R2Q";
	case MAG_R2D: return "R2D";
	case MAG_R2OFFS: return "R2OFFS";
	case MAG_R3Q: return "R3Q";
	case MAG_R3D: return "R3D";
	case MAG_R3OFFS: return "R3OFFS";
    case MAG_S1: return "S1";
	case MAG_S2: return "S2";
	case MAG_S3: return "S3";
	case MAG_S4: return "S4";
	case MAG_S5: return "S5";
	case MAG_S6: return "S6";
    case MAG_O1: return "O1";
	case MAG_O2: return "O2";
	case MAG_O3: return "O3";
    case MAG_T1: return "T1";
	case MAG_T2: return "T2";
    case MAG_S1_COMBINEDS: return "S1_COMBINEDS";
	case MAG_S1_COMBINEDQ: return "S1_COMBINEDQ";
    case MAG_S2_COMBINEDS: return "S2_COMBINEDS";
	case MAG_S2_COMBINEDQ: return "S2_COMBINEDQ";
	case MAG_S3_COMBINEDS: return "S3_COMBINEDS";
	case MAG_S3_COMBINEDQ: return "S3_COMBINEDQ";
	case MAG_S4_COMBINEDS: return "S4_COMBINEDS";
	case MAG_S4_COMBINEDQ: return "S4_COMBINEDQ";
	case MAG_S5_COMBINEDS: return "S5_COMBINEDS";
	case MAG_S5_COMBINEDQ: return "S5_COMBINEDQ";
	case MAG_S6_COMBINEDS: return "S6_COMBINEDS";
	case MAG_S6_COMBINEDQ: return "S6_COMBINEDQ";
    case MAG_COUNT: return "COUNT";
  }
}

int get_info_details_callback(size_t row, size_t col, const char* value, void* callbackdata) {
  (void)row;
  if (value == NULL) return 0;
  Info *info = (Info*)callbackdata;

  size_t sz = strlen(value);
  sz = sz > DEFAULT_INFO_BUFF_LEN ? DEFAULT_INFO_BUFF_LEN : sz;
  if (col == 2) {
    info->date = strtol(value, NULL, 10);
  } else if (col == 3) {
    memset(info->version, 0, DEFAULT_INFO_BUFF_LEN);
    memcpy(info->version, value, sz);
  } else if (col == 4) {
    memset(info->by, 0, DEFAULT_INFO_BUFF_LEN);
    memcpy(info->by, value, sz);
  } else if (col == 5) {
    memset(info->description, 0, DEFAULT_INFO_BUFF_LEN);
    memcpy(info->description, value, sz);
    for (size_t i=0; i<sz; i++)
      if (info->description[i] == ',') info->description[i] = ' ';
  }

  return 0;
}

int get_fam_locs_callback(size_t row, size_t col, const char* value, void* callbackdata) {
  FamilyLocations *fam_locs = (FamilyLocations*)callbackdata;

  if (value == NULL) return 0;
  if (row != 2) return 0;

  if (strcmp(value, "Hardware Check\n?")==0) {
    fam_locs->HW_check = col;
  } else if (strcmp(value, "Last Updated")==0) {
    fam_locs->LastUpdated = col;
  } else if (strcmp(value, "Magnet Limits Date")==0) {
    fam_locs->MagLimitsDate = col;
  } else if (strcmp(value, "Description")==0) {
    fam_locs->Description = col;
  } else if (strcmp(value, "Comment")==0) {
    fam_locs->Comment = col;
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
    if (fam_locs->R1d_value == 0) fam_locs->R1d_value = col;
    else fam_locs->R1d_cl = col;
    if (fam_locs->R1q_value == 0) fam_locs->R1q_value = col + 1;
    else fam_locs->R1q_cl = col + 1;
    if (fam_locs->R1offs_value == 0) fam_locs->R1offs_value = col + 2;
    else fam_locs->R1offs_cl = col + 2;
  }
  else if (strcmp(value, "R2")==0) {
    if (fam_locs->R2d_value == 0) fam_locs->R2d_value = col;
    else fam_locs->R2d_cl = col;
    if (fam_locs->R2q_value == 0) fam_locs->R2q_value = col + 1;
    else fam_locs->R2q_cl = col + 1;
    if (fam_locs->R2offs_value == 0) fam_locs->R2offs_value = col + 2;
    else fam_locs->R2offs_cl = col + 2;
  }
  else if (strcmp(value, "R3")==0) {
    if (fam_locs->R3d_value == 0) fam_locs->R3d_value = col;
    else fam_locs->R3d_cl = col;
    if (fam_locs->R3q_value == 0) fam_locs->R3q_value = col + 1;
    else fam_locs->R3q_cl = col + 1;
    if (fam_locs->R3offs_value == 0) fam_locs->R3offs_value = col + 2;
    else fam_locs->R3offs_cl = col + 2;
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
    if (fam_locs->S1_combineds_value == 0) fam_locs->S1_combineds_value = col;
    else fam_locs->S1_combineds_cl = col;
    if (fam_locs->S1_combinedq_value == 0) fam_locs->S1_combinedq_value = col + 1;
    else fam_locs->S1_combinedq_cl = col + 1;
  }
  else if (strcmp(value, "S3_combined")==0) {
    if (fam_locs->S3_combineds_value == 0) fam_locs->S3_combineds_value = col;
    else fam_locs->S3_combineds_cl = col;
    if (fam_locs->S3_combinedq_value == 0) fam_locs->S3_combinedq_value = col + 1;
    else fam_locs->S3_combinedq_cl = col + 1;
  }
  else if (strcmp(value, "S6_combined")==0) {
    if (fam_locs->S6_combineds_value == 0) fam_locs->S6_combineds_value = col;
    else fam_locs->S6_combineds_cl = col;
    if (fam_locs->S6_combinedq_value == 0) fam_locs->S6_combinedq_value = col + 1;
    else fam_locs->S6_combinedq_cl = col + 1;
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
  else if (col == fam_defns->fam_locs.R1d_value) fam_defns->data[index_of_last].values[MAG_R1D] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R1q_value) fam_defns->data[index_of_last].values[MAG_R1Q] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R1offs_value) fam_defns->data[index_of_last].values[MAG_R1OFFS] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R2d_value) fam_defns->data[index_of_last].values[MAG_R2D] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R2q_value) fam_defns->data[index_of_last].values[MAG_R2Q] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R2offs_value) fam_defns->data[index_of_last].values[MAG_R2OFFS] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R3d_value) fam_defns->data[index_of_last].values[MAG_R3D] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R3q_value) fam_defns->data[index_of_last].values[MAG_R3Q] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.R3offs_value) fam_defns->data[index_of_last].values[MAG_R3OFFS] = strtod(value, NULL);
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
  else if (col == fam_defns->fam_locs.S1_combineds_value) fam_defns->data[index_of_last].values[MAG_S1_COMBINEDS] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S2_combineds_value) fam_defns->data[index_of_last].values[MAG_S2_COMBINEDS] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S3_combineds_value) fam_defns->data[index_of_last].values[MAG_S3_COMBINEDS] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S4_combineds_value) fam_defns->data[index_of_last].values[MAG_S4_COMBINEDS] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S5_combineds_value) fam_defns->data[index_of_last].values[MAG_S5_COMBINEDS] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S6_combineds_value) fam_defns->data[index_of_last].values[MAG_S6_COMBINEDS] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S1_combinedq_value) fam_defns->data[index_of_last].values[MAG_S1_COMBINEDQ] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S2_combinedq_value) fam_defns->data[index_of_last].values[MAG_S2_COMBINEDQ] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S3_combinedq_value) fam_defns->data[index_of_last].values[MAG_S3_COMBINEDQ] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S4_combinedq_value) fam_defns->data[index_of_last].values[MAG_S4_COMBINEDQ] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S5_combinedq_value) fam_defns->data[index_of_last].values[MAG_S5_COMBINEDQ] = strtod(value, NULL);
  else if (col == fam_defns->fam_locs.S6_combinedq_value) fam_defns->data[index_of_last].values[MAG_S6_COMBINEDQ] = strtod(value, NULL);
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
  else if (col == fam_defns->fam_locs.R1d_cl) fam_defns->data[index_of_last].cls[MAG_R1D] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R1q_cl) fam_defns->data[index_of_last].cls[MAG_R1Q] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R1offs_cl) fam_defns->data[index_of_last].cls[MAG_R1OFFS] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R2d_cl) fam_defns->data[index_of_last].cls[MAG_R2D] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R2q_cl) fam_defns->data[index_of_last].cls[MAG_R2Q] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R2offs_cl) fam_defns->data[index_of_last].cls[MAG_R2OFFS] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R3d_cl) fam_defns->data[index_of_last].cls[MAG_R3D] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R3q_cl) fam_defns->data[index_of_last].cls[MAG_R3Q] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.R3offs_cl) fam_defns->data[index_of_last].cls[MAG_R3OFFS] = strtol(value, NULL, 10);
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
  else if (col == fam_defns->fam_locs.S1_combineds_cl) fam_defns->data[index_of_last].cls[MAG_S1_COMBINEDS] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S2_combineds_cl) fam_defns->data[index_of_last].cls[MAG_S2_COMBINEDS] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S3_combineds_cl) fam_defns->data[index_of_last].cls[MAG_S3_COMBINEDS] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S4_combineds_cl) fam_defns->data[index_of_last].cls[MAG_S4_COMBINEDS] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S5_combineds_cl) fam_defns->data[index_of_last].cls[MAG_S5_COMBINEDS] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S6_combineds_cl) fam_defns->data[index_of_last].cls[MAG_S6_COMBINEDS] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S1_combinedq_cl) fam_defns->data[index_of_last].cls[MAG_S1_COMBINEDQ] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S2_combinedq_cl) fam_defns->data[index_of_last].cls[MAG_S2_COMBINEDQ] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S3_combinedq_cl) fam_defns->data[index_of_last].cls[MAG_S3_COMBINEDQ] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S4_combinedq_cl) fam_defns->data[index_of_last].cls[MAG_S4_COMBINEDQ] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S5_combinedq_cl) fam_defns->data[index_of_last].cls[MAG_S5_COMBINEDQ] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.S6_combinedq_cl) fam_defns->data[index_of_last].cls[MAG_S6_COMBINEDQ] = strtol(value, NULL, 10);
  else if (col == fam_defns->fam_locs.LastUpdated) fam_defns->data[index_of_last].lastupdated = strtof(value, NULL);
  else if (col == fam_defns->fam_locs.MagLimitsDate) fam_defns->data[index_of_last].maglimitsdate = strtof(value, NULL);
  else if (col == fam_defns->fam_locs.Description) {
    size_t sz = strlen(value);
    fam_defns->data[index_of_last].description = SDM_MALLOC(sz + 1);
    memcpy(fam_defns->data[index_of_last].description, value, sz);
    for (size_t i=0; i<sz; i++) if (fam_defns->data[index_of_last].description[i]==',') fam_defns->data[index_of_last].description[i] = ' ';
  } else if (col == fam_defns->fam_locs.Comment) {
    size_t sz = strlen(value);
    fam_defns->data[index_of_last].comment = SDM_MALLOC(sz + 1);
    memcpy(fam_defns->data[index_of_last].comment, value, sz);
    for (size_t i=0; i<sz; i++) if (fam_defns->data[index_of_last].comment[i]==',') fam_defns->data[index_of_last].comment[i] = ' ';
  } else if (col == fam_defns->fam_locs.HW_check) {
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

// Function to check if a year is a leap year
static int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to convert days since 1900-01-01 to a date string
char* days_to_date(float days) {
  int whole_days = floorf(days);

  float hours = (days - whole_days) * 24;
  int whole_hours = floorf(hours);

  float minutes = (hours - whole_hours) * 60;
  int whole_minutes = floorf(minutes);

  float seconds = (minutes - whole_minutes) * 60;
  int whole_seconds = floorf(seconds);

  int year = 1900;
  int month = 1;
  int day = 1;
  size_t timestamp_len = 32;
  char *date = SDM_MALLOC(timestamp_len);
  
  // Adjust for correct day alignment
  whole_days -= 2; // Corrects the two-day error

  // Days in each month (non-leap year)
  int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  
  // Process years
  while (whole_days >= (is_leap_year(year) ? 366 : 365)) {
      whole_days -= is_leap_year(year) ? 366 : 365;
      year++;
  }
  
  // Process months
  while (whole_days >= ((month == 2 && is_leap_year(year)) ? 29 : days_in_month[month - 1])) {
      whole_days -= (month == 2 && is_leap_year(year)) ? 29 : days_in_month[month - 1];
      month++;
  }
  
  // Remaining days determine the final day
  day += whole_days;
  
  // Format the date string as YYYY-MM-DD
  snprintf(date, timestamp_len, "%04d-%02d-%02d %02d:%02d:%02d", year, month, day, whole_hours, whole_minutes, whole_seconds);
  
  return date;
}

void print_file_summary(FILE *sink, const char *latt_summ_filename, const FamilyDefns *fam_defns, const Info *info) {
  fprintf(sink, "--------------------------------------------------------\n");
  fprintf(sink, "Summary of %s\n", latt_summ_filename);
  fprintf(sink, "\tVersion:       %s\n", info->version);
  fprintf(sink, "\tDate:          %s\n", days_to_date(info->date));
  fprintf(sink, "\tBy:            %s\n", info->by);
  fprintf(sink, "\tDescription:   \"%s\"\n", info->description);
  fprintf(sink, "\tLattice count: %zu\n", fam_defns->length);
  fprintf(sink, "--------------------------------------------------------\n");
}

bool fake_magnet(MagType type) {
  switch (type) {
    case MAG_D1: case MAG_D2: case MAG_D3:
    case MAG_Q1: case MAG_Q2: case MAG_Q3: case MAG_Q4: case MAG_Q5: case MAG_Q6:
    case MAG_R1Q: case MAG_R2Q: case MAG_R3Q:
    case MAG_S1: case MAG_S2: case MAG_S3: case MAG_S4: case MAG_S5: case MAG_S6:
    case MAG_O1: case MAG_O2: case MAG_O3:
    case MAG_T1: case MAG_T2:
    case MAG_S1_COMBINEDS: case MAG_S2_COMBINEDS: case MAG_S3_COMBINEDS:
    case MAG_S4_COMBINEDS: case MAG_S5_COMBINEDS: case MAG_S6_COMBINEDS:
      return false;
	case MAG_D1Q: case MAG_D2Q: case MAG_D3Q:
	case MAG_R1D: case MAG_R1OFFS:
	case MAG_R2D: case MAG_R2OFFS:
	case MAG_R3D: case MAG_R3OFFS:
	case MAG_S1_COMBINEDQ: case MAG_S2_COMBINEDQ: case MAG_S3_COMBINEDQ:
    case MAG_S4_COMBINEDQ: case MAG_S5_COMBINEDQ: case MAG_S6_COMBINEDQ:
    case MAG_COUNT:
      return true;
  }
}

void print_header(FILE *sink) {
  fprintf(sink, "Lattice name, ");
  for (size_t i=0; i<BLOCK_COUNT; i++) {
    if (i != 0) fprintf(sink, ", ");
    fprintf(sink, "%s", block_type_string(i));
  }
  fprintf(sink, ", ");
  for (size_t i=0; i<MAG_COUNT; i++) {
    if (fake_magnet(i)) continue;
    fprintf(sink, "New %s PS?", string_from_magtype(i));
    fprintf(sink, ", ");
  }
  fprintf(sink, "Block Cost (k.SEK)");
  fprintf(sink, ", ");
  fprintf(sink, "Cooling Cost (k.SEK)");
  fprintf(sink, ", ");
  fprintf(sink, "TOTAL COST (M.SEK)");
  fprintf(sink, ", ");
  fprintf(sink, "Last Updated");
  fprintf(sink, ", ");
  fprintf(sink, "Magnet Limits Date");
  fprintf(sink, ", ");
  fprintf(sink, "Description");
  fprintf(sink, ", ");
  fprintf(sink, "Comment");
  fprintf(sink, "\n");
}

void print_lattice_details(FILE *sink, FamilyDefn fam, double block_work_cost, double cooling_work_cost, BlockWork *block_work_details, size_t num_blocks, bool *new_ps_needed) {
  fprintf(sink, "%s", fam.name);
  fprintf(sink, ", ");
  print_block_work_info(sink, block_work_details, num_blocks);
  fprintf(sink, ", ");
  for (size_t i=0; i<MAG_COUNT; i++) {
    if (fake_magnet(i)) continue;
    fprintf(sink, "%s", new_ps_needed[i] ? "Y" : "-");
    fprintf(sink, ", ");
  }
  fprintf(sink, "%0.1f", NUM_ACHROMATS * block_work_cost/1e3);
  fprintf(sink, ", ");
  fprintf(sink, "%0.1f", NUM_ACHROMATS * cooling_work_cost/1e3);
  fprintf(sink, ", ");
  fprintf(sink, "%0.1f", NUM_ACHROMATS * (block_work_cost + cooling_work_cost)/1e6);
  fprintf(sink, ", ");
  if (fam.lastupdated) fprintf(sink, "%s", days_to_date(fam.lastupdated));
  else fprintf(sink, "-");
  fprintf(sink, ", ");
  if (fam.maglimitsdate) fprintf(sink, "%s", days_to_date(fam.maglimitsdate));
  else fprintf(sink, "-");
  fprintf(sink, ", ");
  if (fam.description) fprintf(sink, "%s", fam.description);
  else fprintf(sink, "-");
  fprintf(sink, ", ");
  if (fam.comment) fprintf(sink, "%s", fam.comment);
  else fprintf(sink, "-");
  fprintf(sink, "\n");
}

void print_block_work_info(FILE *sink, BlockWork *blocks_replaced, size_t num_blocks) {
  for (size_t block_ind=0; block_ind<num_blocks; block_ind++) {
    if (block_ind != 0) fprintf(sink, ", ");
    if (blocks_replaced[block_ind] == BLK_WORK_REPLACE)  fprintf(sink, "R");
    else if (blocks_replaced[block_ind] == BLK_WORK_MOD) fprintf(sink, "M");
    else fprintf(sink, "-");
  }
}

void print_block_replacement_info(FILE *sink, BlockWork *blocks_replaced, size_t num_blocks) {
    fprintf(sink, "Replace:  ");
    bool any_blocks_replaced = any_equal_to(blocks_replaced, num_blocks, BLK_WORK_REPLACE);
    for (size_t block_ind=0; block_ind<num_blocks; block_ind++)
      if (blocks_replaced[block_ind] == BLK_WORK_REPLACE) fprintf(sink, "%s, ", block_type_string(block_ind));
    if (!any_blocks_replaced) fprintf(sink, "-  ");
}

void print_block_modification_info(FILE *sink, BlockWork *blocks_replaced, size_t num_blocks) {
    fprintf(sink, "Modify:  ");
    bool any_blocks_modified = any_equal_to(blocks_replaced, num_blocks, BLK_WORK_MOD);
    for (size_t block_ind=0; block_ind<num_blocks; block_ind++)
      if (blocks_replaced[block_ind] == BLK_WORK_MOD) fprintf(sink, "%s, ", block_type_string(block_ind));
    if (!any_blocks_modified) fprintf(sink, "-  ");
}

Info create_info_struct(void) {
  Info info = {0};
  info.version     = SDM_MALLOC(DEFAULT_INFO_BUFF_LEN);
  info.by          = SDM_MALLOC(DEFAULT_INFO_BUFF_LEN);
  info.description = SDM_MALLOC(DEFAULT_INFO_BUFF_LEN);
  return info;
}

