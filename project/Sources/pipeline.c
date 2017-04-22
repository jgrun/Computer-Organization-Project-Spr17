/*
 * pipeline.c
 *
 *  Created on: Mar 15, 2017
 *      Author: jacob
 */

#include <stdio.h>
#include "pipeline.h"
#include "alu.h"

void instruction_fetch(control * ifid, pc_t * pc, inst instruction) {

	// Still need to write code for reading in instr
	ifid->instr = instruction;


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

void execute_instruction(control * idex, control * exmem) {
	word alu_rs;
	word alu_rt;
	word alu_result;

	alu_rs = idex->regRsValue;

	if(idex->ALUSrc) alu_rt = idex->immed;
	else alu_rt = idex->regRtValue;

	alu_result = idex->ALUresult;

	alu();

	if((idex->ALUop == oper_movz && alu_rt != 0) || (idex->ALUop == oper_movn && alu_rt == 0)) idex->RegWrite = false;
}

void print_control_reg(control reg, r_type t) {
	switch(t) {
	case IFID:
		printf("opCode:   %#02x\n", reg.opCode);
		printf("regRs:    %#04x\n", reg.regRs);
		printf("regRd:    %#04x\n", reg.regRd);
		printf("regRt:    %#04x\n", reg.regRt);
		printf("shamt:    %#04x\n", reg.shamt);
		printf("address:  %#04x\n", reg.address);
		printf("funct:    %#02x\n", reg.funct);
		printf("immed:    %d\n", reg.immed);
		break;
	case IDEX:
		break;
	case EXMEM:
		break;
	case MEMWB:
		break;
	default:
		printf("Bad register type\n");
		break;
	}

	printf("pc:       %d\n", reg.pcNext);
	printf("RegDst:   %d\n", reg.RegDst);
	printf("RegWrite: %d\n", reg.RegWrite);
	printf("ALUSrc:   %d\n", reg.ALUSrc);
	printf("PCSrc:    %d\n", reg.PCSrc);
	printf("MemRead:  %d\n", reg.MemRead);
	printf("MemWrite: %d\n", reg.MemWrite);
	printf("MemtoReg: %d\n", reg.RegDst);


}

