/*
 * memory.c
 *
 *  Created on: Apr 24, 2017
 *      Author: jacob
 */

#include "memory.h"

void init_memory(uint32_t size) {

}

void init_control_reg(control ** reg) {
	*reg = (control *)malloc(sizeof(control));
	empty_reg(*reg);
}

void empty_reg(control * reg) {
	reg->RegDst    = false;
	reg->RegWrite  = false;
	reg->ALUSrc    = false;
	reg->PCSrc     = false;
	reg->MemRead   = false;
	reg->MemWrite  = false;
	reg->MemtoReg  = false;
	reg->ALUop     = 0;
	reg->jump      = false;
	reg->instr     = 0;
	reg->opCode    = 0;
	reg->regRs     = 0;
	reg->regRt     = 0;
	reg->regRd     = 0;
	reg->immed     = 0;
	reg->address   = 0;
	reg->funct     = 0;
	reg->shamt     = 0;
	reg->regRsValue= 0;
	reg->regRtValue= 0;
	reg->ALUresult = 0;
	reg->pcNext    = 0;
	reg->memData   = 0;
}

