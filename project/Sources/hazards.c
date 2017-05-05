/*
 * hazards.c
 *
 *  Created on: May 4, 2017
 *      Author: jacob
 */

#include "hazards.h"

control * backup_ifid;
control * backup_idex;
control * backup_exmem;
control * backup_memwb;
pc_t backup_pc;

void init_hazards() {
	init_control_reg(&backup_ifid);
	init_control_reg(&backup_idex);
	init_control_reg(&backup_exmem);
	init_control_reg(&backup_memwb);
}

void hazard_detection(control * ifid, control * idex, control * exmem, control * memwb, pc_t * pc, sim_results * sim) {
	uint8_t forwarding = 0;
	backup_pc = *pc;

	uint8_t stall = 0;
	uint32_t exDest = 0;
	uint32_t memDest = 0;
	if(exmem->RegDst) exDest = exmem->regRd;
	else exDest = exmem->regRt;
	if(memwb->RegDst) memDest = memwb->regRd;
	else memDest = memwb->regRt;

	if(exmem->RegWrite && (exDest != 0) && (exDest == idex->regRs)) {
		forwarding = 1;
		idex->regRsValue = exmem->ALUresult;
	}
	if(exmem->RegWrite && (exDest != 0) && (exDest == idex->regRt)) {
		forwarding = 1;
		idex->regRtValue = exmem->ALUresult;
	}

	if(memwb->RegWrite && (memDest != 0) && (memDest == idex->regRs) && !(exmem->RegWrite && (exDest != 0) && (exDest == idex->regRs))) {
		forwarding = 1;
		if(memwb->MemtoReg) idex->regRsValue = memwb->memData;
		else idex->regRsValue = memwb->ALUresult;
	}

	int cycle_increment = 1;
	if(exmem->MemRead) cycle_increment = 2;

	//need to add sim cycle update when cache is added
	if(forwarding) {
		switch(idex->opCode) {
		case op_bne:
			if(idex->regRsValue != idex->regRtValue) idex->PCSrc = true;
			else idex->PCSrc = false;
			break;
		case op_beq:
			if(idex->regRsValue == idex->regRtValue) idex->PCSrc = true;
			else idex->PCSrc = false;
			break;
		case op_blitz:
			if(idex->regRsValue < 0) idex->PCSrc = true;
			else idex->PCSrc = false;
			break;
		case op_bgtz:
			if(idex->regRsValue > 0) idex->PCSrc = true;
			else idex->PCSrc = false;
			break;
		case op_blez:
			if(idex->regRsValue <= 0) idex->PCSrc = true;
			else idex->PCSrc = false;
			break;
		case op_rtype:
			if(idex->funct == funct_jr) idex->pcNext = idex->regRsValue;
			break;
		default:
			printf("got somewhere weird with forwarding in hazard\n");
		}
	}

	if(idex->MemRead && ((idex->regRt == ifid->regRs) || (idex->regRt == ifid->regRt)) && !(ifid->opCode == op_jtype || ifid->opCode == op_jal)) {
		if(!(idex->regRt == r_zero)) {
			stall = 1;
			empty_reg(ifid);
		}
	}

	if(idex->jump || idex->PCSrc) *pc = idex->pcNext;
	else if (stall) {
		empty_reg(ifid);
	}
	else *pc += 4;
}

void backup_pipeline(control * ifid, control * idex, control * exmem, control * memwb, pc_t * p) {
	copyPipeline(ifid, backup_ifid);
	copyPipeline(idex, backup_idex);
	copyPipeline(exmem, backup_exmem);
	copyPipeline(memwb, backup_memwb);
	backup_pc = *p;
}

void restore_pipeline(control * ifid, control * idex, control * exmem, control * memwb, pc_t * p) {
	copyPipeline(backup_ifid, ifid);
	copyPipeline(backup_idex, idex);
	copyPipeline(backup_exmem, exmem);
	copyPipeline(backup_memwb, memwb);
	*p = backup_pc;
}
