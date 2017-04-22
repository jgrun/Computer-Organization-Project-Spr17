/*
 * pipeline.h
 *
 *  Created on: Mar 15, 2017
 *      Author: jacob
 */

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include "types.h"

// maskers
#define OP_MASK 0xfc000000
#define RS_MASK 0x03e00000
#define RT_MASK 0x001f0000
#define RD_MASK 0x0000f800
#define SH_MASK 0x000007c0
#define FC_MASK 0x0000003f
#define AD_MASK 0x03ffffff
#define IM_MASK 0x0000ffff

// shifters
#define SHIFT_OP 26
#define SHIFT_RS 21
#define SHIFT_RT 16
#define SHIFT_RD 11
#define SHIFT_SH 6

// extenders
#define NEGATIVE 0x00008000
#define EXTEND16 0xffff0000

void instruction_fetch(control * ifid, pc_t * pc, inst instruction);

void instruction_decode();

void execute_instruction();

void memory_access();

void write_back();

typedef enum reg_type {
	IFID,
	IDEX,
	EXMEM,
	MEMWB
}r_type;

void print_control_reg(control reg, r_type t);



#endif /* PIPELINE_H_ */

