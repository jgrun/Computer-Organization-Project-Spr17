/*
 * pipeline.h
 *
 *  Created on: Mar 15, 2017
 *      Author: jacob
 */

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include "types.h"
#include "alu.h"
#include "reg.h"
#include "memory.h"

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

void instruction_fetch(control * ifid, pc_t * pc);

void instruction_decode(control * IFID , control * IDEX);

void execute_instruction(control * idex, control * exmem);

void memory_access(control * exmem, control * memwb);

void write_back(control * memwb);


typedef enum reg_type {
	IFID,
	IDEX,
	EXMEM,
	MEMWB
}r_type;

void print_control_reg(control reg);

void copyPipeline(control* original, control* copy);

void init_pipeline();

#endif /* PIPELINE_H_ */

