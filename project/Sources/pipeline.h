/*
 * pipeline.h
 *
 *  Created on: Mar 15, 2017
 *      Author: jacob
 */

#ifndef PIPELINE_H_
#define PIPELINE_H_

#define OP_MASK 0xfc000000
#define RS_MASK 0x03e00000
#define RT_MASK 0x001f0000
#define RD_MASK 0x0000f800
#define SH_MASK 0x000007c0
#define FC_MASK 0x0000003f
#define AD_MASK 0x03ffffff
#define IM_MASK 0x0000ffff

#define SHIFT_OP 26
#define SHIFT_RS 21
#define SHIFT_RT 16
#define SHIFT_RD 11
#define SHIFR_SH 6



void instruction_fetch(control ifid, pc_t pc);

void instruction_decode();

void execute_instruction();

void memory_access();

void write_back();



#endif /* PIPELINE_H_ */
