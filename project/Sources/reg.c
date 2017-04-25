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
	printf("$zero = %#08x", registers[0]);
	printf("$At   = %#08x", registers[1]);
	printf("$V0   = %#08x", registers[2]);
	printf("$V1   = %#08x", registers[3]);
	printf("$A0   = %#08x", registers[4]);
	printf("$A1   = %#08x", registers[5]);
	printf("$A2   = %#08x", registers[6]);
	printf("$A3   = %#08x", registers[7]);
	printf("$T0   = %#08x", registers[8]);
	printf("$T1   = %#08x", registers[9]);
	printf("$T2   = %#08x", registers[10]);
	printf("$T3   = %#08x", registers[11]);
	printf("$T4   = %#08x", registers[12]);
	printf("$T5   = %#08x", registers[13]);
	printf("$T6   = %#08x", registers[14]);
	printf("$T7   = %#08x", registers[15]);
	printf("$S0   = %#08x", registers[16]);
	printf("$S1   = %#08x", registers[17]);
	printf("$S2   = %#08x", registers[18]);
	printf("$S3   = %#08x", registers[19]);
	printf("$S4   = %#08x", registers[20]);
	printf("$S5   = %#08x", registers[21]);
	printf("$S6   = %#08x", registers[22]);
	printf("$S7   = %#08x", registers[23]);
	printf("$T8   = %#08x", registers[24]);
	printf("$T9   = %#08x", registers[25]);
	printf("$K0   = %#08x", registers[26]);
	printf("$K1   = %#08x", registers[27]);
	printf("$GP   = %#08x", registers[28]);
	printf("$SP   = %#08x", registers[29]);
	printf("$FP   = %#08x", registers[30]);
	printf("$RA   = %#08x", registers[31]);
}
