/*
 * reg.h
 *
 *  Created on: Apr 24, 2017
 *      Author: jacob
 */

#ifndef REG_H_
#define REG_H_

#include "types.h"

typedef enum regName {
	r_zero = 0,
	r_At   = 1,
	r_V0   = 2,
	r_V1   = 3,
	r_A0   = 4,
	r_A1   = 5,
	r_A2   = 6,
	r_A3   = 7,
	r_T0   = 8,
	r_T1   = 9,
	r_T2   = 10,
	r_T3   = 11,
	r_T4   = 12,
	r_T5   = 13,
	r_T6   = 14,
	r_T7   = 15,
	r_S0   = 16,
	r_S1   = 17,
	r_S2   = 18,
	r_S3   = 19,
	r_S4   = 20,
	r_S5   = 21,
	r_S6   = 22,
	r_S7   = 23,
	r_T8   = 24,
	r_T9   = 25,
	r_K0   = 26,
	r_K1   = 27,
	r_GP   = 28,
	r_SP   = 29,
	r_FP   = 30,
	r_RA   = 31
}r_Name;

void init_registers();

void print_registers();

void read_register(r_Name reg, word * value);

void write_register(r_Name reg, word * value);

#endif /* REG_H_ */
