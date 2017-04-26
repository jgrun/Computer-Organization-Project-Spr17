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
	printf("$zero = %#08x", registers[r_zero]);
	printf("$At   = %#08x", registers[r_At]);
	printf("$V0   = %#08x", registers[r_V0]);
	printf("$V1   = %#08x", registers[r_V1]);
	printf("$A0   = %#08x", registers[r_A0]);
	printf("$A1   = %#08x", registers[r_A1]);
	printf("$A2   = %#08x", registers[r_A2]);
	printf("$A3   = %#08x", registers[r_A3]);
	printf("$T0   = %#08x", registers[r_T0]);
	printf("$T1   = %#08x", registers[r_T1]);
	printf("$T2   = %#08x", registers[r_T2]);
	printf("$T3   = %#08x", registers[r_T3]);
	printf("$T4   = %#08x", registers[r_T4]);
	printf("$T5   = %#08x", registers[r_T5]);
	printf("$T6   = %#08x", registers[r_T6]);
	printf("$T7   = %#08x", registers[r_T7]);
	printf("$S0   = %#08x", registers[r_S0]);
	printf("$S1   = %#08x", registers[r_S1]);
	printf("$S2   = %#08x", registers[r_S2]);
	printf("$S3   = %#08x", registers[r_S3]);
	printf("$S4   = %#08x", registers[r_S4]);
	printf("$S5   = %#08x", registers[r_S5]);
	printf("$S6   = %#08x", registers[r_S6]);
	printf("$S7   = %#08x", registers[r_S7]);
	printf("$T8   = %#08x", registers[r_T8]);
	printf("$T9   = %#08x", registers[r_T9]);
	printf("$K0   = %#08x", registers[r_K0]);
	printf("$K1   = %#08x", registers[r_K1]);
	printf("$GP   = %#08x", registers[r_GP]);
	printf("$SP   = %#08x", registers[r_SP]);
	printf("$FP   = %#08x", registers[r_FP]);
	printf("$RA   = %#08x", registers[r_RA]);
}
