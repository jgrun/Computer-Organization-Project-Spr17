/*
 * pipeline.c
 *
 *  Created on: Mar 15, 2017
 *      Author: jacob
 */

#include "pipeline.h"

void instruction_fetch(control * ifid, pc_t * pc) {


	ifid->opCode = (ifid->instr & OP_MASK) >> SHIFT_OP;
	ifid->regRs  = (ifid->instr & RS_MASK) >> SHIFT_RS;
	ifid->regRd  = (ifid->instr & RD_MASK) >> SHIFT_RD;
	ifid->regRt  = (ifid->instr & RT_MASK) >> SHIFT_RT;
	ifid->shamt  = (ifid->instr & SH_MASK) >> SHIFT_SH;
	ifid->address  = (ifid->instr & AD_MASK);
	ifid->funct  = (ifid->instr & FC_MASK);

	uint32_t immediate = (ifid->instr & IM_MASK);
}

