/*
 * pipeline.c
 *
 *  Created on: Mar 15, 2017
 *      Author: jacob
 */

#include "pipeline.h"

void instruction_fetch(control * ifid, pc_t * pc) {

	// Still need to write code for reading in instr

	ifid->opCode = (ifid->instr & OP_MASK) >> SHIFT_OP;
	ifid->regRs  = (ifid->instr & RS_MASK) >> SHIFT_RS;
	ifid->regRd  = (ifid->instr & RD_MASK) >> SHIFT_RD;
	ifid->regRt  = (ifid->instr & RT_MASK) >> SHIFT_RT;
	ifid->shamt  = (ifid->instr & SH_MASK) >> SHIFT_SH;
	ifid->address  = (ifid->instr & AD_MASK);
	ifid->funct  = (ifid->instr & FC_MASK);

	uint32_t immediate = (ifid->instr & IM_MASK);

	// Sign extend if necessary
	if((ifid->instr & NEGATIVE) && (ifid->opCode != op_andi) && (ifid->opCode != op_ori) && (ifid->opCode != op_xori) && (ifid->opCode != op_sltiu)) {
		ifid->immed = immediate | EXTEND16;
	}
	else ifid->immed = immediate;

	ifid->pcNext = *pc + 4;
}

