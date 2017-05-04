/*
 * reg.c
 *
 *  Created on: Apr 24, 2017
 *      Author: jacob
 */

#include "reg.h"

word registers[32];

void init_registers() {
	int i = 0;
	for(i = 0; i < 32; i++) {
		registers[i] = 0;
	}
}

void read_register(r_Name reg, word * value) {
	*value = registers[reg];
}

void write_register(r_Name reg, word * value) {
	if(reg) registers[reg] = *value;
}

void print_registers() {
	printf("\n");
	printf("$zero = 0x%08x\n", registers[r_zero]);
	printf("$at   = 0x%08x\n", registers[r_At]);
	printf("$V0   = 0x%08x\n", registers[r_V0]);
	printf("$V1   = 0x%08x\n", registers[r_V1]);
	printf("$A0   = 0x%08x\n", registers[r_A0]);
	printf("$A1   = 0x%08x\n", registers[r_A1]);
	printf("$A2   = 0x%08x\n", registers[r_A2]);
	printf("$A3   = 0x%08x\n", registers[r_A3]);
	printf("$T0   = 0x%08x\n", registers[r_T0]);
	printf("$T1   = 0x%08x\n", registers[r_T1]);
	printf("$T2   = 0x%08x\n", registers[r_T2]);
	printf("$T3   = 0x%08x\n", registers[r_T3]);
	printf("$T4   = 0x%08x\n", registers[r_T4]);
	printf("$T5   = 0x%08x\n", registers[r_T5]);
	printf("$T6   = 0x%08x\n", registers[r_T6]);
	printf("$T7   = 0x%08x\n", registers[r_T7]);
	printf("$S0   = 0x%08x\n", registers[r_S0]);
	printf("$S1   = 0x%08x\n", registers[r_S1]);
	printf("$S2   = 0x%08x\n", registers[r_S2]);
	printf("$S3   = 0x%08x\n", registers[r_S3]);
	printf("$S4   = 0x%08x\n", registers[r_S4]);
	printf("$S5   = 0x%08x\n", registers[r_S5]);
	printf("$S6   = 0x%08x\n", registers[r_S6]);
	printf("$S7   = 0x%08x\n", registers[r_S7]);
	printf("$T8   = 0x%08x\n", registers[r_T8]);
	printf("$T9   = 0x%08x\n", registers[r_T9]);
	printf("$K0   = 0x%08x\n", registers[r_K0]);
	printf("$K1   = 0x%08x\n", registers[r_K1]);
	printf("$gp   = 0x%08x\n", registers[r_GP]);
	printf("$sp   = 0x%08x\n", registers[r_SP]);
	printf("$fp   = 0x%08x\n", registers[r_FP]);
	printf("$ra   = 0x%08x\n", registers[r_RA]);
}
