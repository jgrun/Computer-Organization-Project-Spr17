/*
 * pipeline.c
 *
 *  Created on: Mar 15, 2017
 *      Author: jacob
 */

#include "pipeline.h"

#define NEXT 0xF0000000
#define SHIFT_NUM 16

extern word registers[32];

#define TEST

control * ifid;
control * idex;
control * exmem;
control * memwb;

void instruction_fetch(control * ifid, pc_t * pc, inst instruction) {

	// Still need to write code for reading in instr
#ifdef TEST
	ifid->instr = instruction;
#else

#endif

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

void instruction_decode( control * ifid , control * idex) {
    copyPipeline(ifid, idex);

    switch(idex->opCode){
        case op_rtype:
            idex->RegDst = true;
            idex->ALUSrc = false;
            idex->MemtoReg = false;
            idex->RegWrite = true;
            idex->MemRead = false;
            idex->MemWrite = false;
            idex->jump = false;
            idex->PCSrc = false;
            switch(idex->funct){
                case funct_add:
                    idex->ALUop = oper_Add;
                    break;
                case funct_addu:
                    idex->ALUop = oper_Addu;
                    break;
                case funct_and:
                    idex->ALUop = oper_And;
                    break;
                case funct_jr:
                    idex->ALUop = oper_Add;
                    idex->jump = true;
                    idex->RegWrite = false;
                    break;
                case funct_movz:
                    idex->ALUop = oper_Movz;
                    break;
                case funct_movn:
                    idex->ALUop = oper_Movn;
                    break;
                case funct_nor:
                    idex->ALUop = oper_Nor;
                    break;
                case funct_or:
                    idex->ALUop = oper_Or;
                    break;
                case funct_sll:
                    idex->ALUop = oper_Sll;
                    break;
                case funct_srl:
                    idex->ALUop = oper_Srl;
                    break;
                case funct_slt:
                    idex->ALUop = oper_Slt;
                    break;
                case funct_sltu:
                    idex->ALUop = oper_Sltu;
                    break;
                case funct_sub:
                    idex->ALUop = oper_Sub;
                    break;
                case funct_subu:
                    idex->ALUop = oper_Subu;
                    break;
                case funct_xor:
                    idex->ALUop = oper_Xor;
                    break;
                default:
                	break;
            }

            break;

       case op_beq:
       case op_bne:
       case op_blitz:
       case op_bgtz:
       case op_blez:
           idex->ALUop = oper_Sub;
           idex->ALUSrc = false;
           idex->RegWrite = false;
           idex->MemRead = false;
           idex->MemWrite = false;
           idex->jump = false;
           idex->PCSrc = true;
           break;
        case op_sw:
        case op_sh:
        case op_sb:
            idex->ALUop = oper_Addu;
            idex->ALUSrc = true;
            idex->RegWrite = false;
            idex->MemRead = false;
            idex->MemWrite = true;
            idex->jump = false;
            idex->PCSrc = false;
            break;
        case op_lw:
        case op_lb:
        case op_lh:
        case op_lbu:
        case op_lhu:
            idex->ALUop = oper_Addu;
            idex->RegDst = false;
            idex->ALUSrc = true;
            idex->MemtoReg = true;
            idex->RegWrite = true;
            idex->MemRead = true;
            idex->MemWrite = false;
            idex->jump = false;
            idex->PCSrc = false;
            break;
        case op_addi:
            idex->ALUop = oper_Add;
            idex->RegDst = false;
            idex->ALUSrc = true;
            idex->MemtoReg = false;
            idex->RegWrite = true;
            idex->MemRead = false;
            idex->MemWrite = false;
            idex->jump = false;
            idex->PCSrc = false;
            break;
        case op_addiu:
            idex->ALUop = oper_Addu;
            idex->RegDst = false;
            idex->ALUSrc = true;
            idex->MemtoReg = false;
            idex->RegWrite = true;
            idex->MemRead = false;
            idex->MemWrite = false;
            idex->jump = false;
            idex->PCSrc = false;
            break;
        case op_andi:
            idex->ALUop = oper_And;
            idex->RegDst = false;
            idex->ALUSrc = true;
            idex->MemtoReg = false;
            idex->RegWrite = true;
            idex->MemRead = false;
            idex->MemWrite = false;
            idex->jump = false;
            idex->PCSrc = false;
            break;
        case op_ori:
            idex->ALUop = oper_Or;
            idex->RegDst = false;
            idex->ALUSrc = true;
            idex->MemtoReg = false;
            idex->RegWrite = true;
            idex->MemRead = false;
            idex->MemWrite = false;
            idex->jump = false;
            idex->PCSrc = false;
            break;
        case op_slti:
            idex->ALUop = oper_Slt;
            idex->RegDst = false;
            idex->ALUSrc = true;
            idex->MemtoReg = false;
            idex->RegWrite = true;
            idex->MemRead = false;
            idex->MemWrite = false;
            idex->jump = false;
            idex->PCSrc = false;
            break;
        case op_sltiu:
            idex->ALUop = oper_Sltu;
            idex->RegDst = false;
            idex->ALUSrc = true;
            idex->MemtoReg = false;
            idex->RegWrite = true;
            idex->MemRead = false;
            idex->MemWrite = false;
            idex->jump = false;
            idex->PCSrc = false;
            break;
        case op_xori:
            idex->ALUop = oper_Xor;
            idex->RegDst = false;
            idex->ALUSrc = true;
            idex->MemtoReg = false;
            idex->RegWrite = true;
            idex->MemRead = false;
            idex->MemWrite = false;
            idex->jump = false;
            idex->PCSrc = false;
            break;
        case op_jtype:
            idex->ALUop = oper_Addu;
            idex->regRs = r_zero;
            idex->regRt = r_zero;
            idex->regRd = r_zero;
            idex->RegDst = true;
            idex->ALUSrc = false;
            idex->RegWrite = true;
            idex->MemRead = false;
            idex->MemWrite = false;
            idex->MemtoReg = false;
            idex->PCSrc = false;
            idex->jump = true;
            break;
        case op_jal:
            idex->ALUop = oper_Addu;
            idex->regRs = r_zero;
            idex->regRt = r_zero;
            idex->regRd = r_RA;
            idex->RegDst = true;
            idex->ALUSrc = false;
            idex->RegWrite = true;
            idex->MemRead = false;
            idex->MemWrite = false;
            idex->MemtoReg = false;
            idex->PCSrc = false;
            idex->jump = true;
            break;
        case op_lui:
            idex->ALUop = oper_Sll;
            idex->RegDst = false;
            idex->ALUSrc = true;
            idex->RegWrite = true;
            idex->MemRead = false;
            idex->MemWrite = false;
            idex->MemtoReg = false;
            idex->PCSrc = false;
            idex->jump = false;
            idex->shamt = SHIFT_NUM;
            break;
        default:
            break;
    }


    (idex->ALUresult) = registers[idex->regRd];
    (idex->regRsValue) = registers[idex->regRs];
    (idex->regRtValue) = registers[idex->regRt];

    idex->address = ( idex->address << 2 );            //jump address

    if(idex->jump && (idex->opCode != op_rtype)){
        idex->regRtValue = idex->pcNext;
        idex->pcNext = ( idex->pcNext & NEXT ) | idex->address;
    }
    else if(idex->jump && (idex->opCode == op_rtype)){
        idex->pcNext = idex->regRsValue;
    }
    else {
        idex->pcNext = idex->pcNext + ( idex->immed << 2 );
    }
    //Take branch
    if(idex->opCode == op_beq){
        if(idex->regRsValue == idex->regRtValue){
            idex->PCSrc = true;
        }
        //Don't take branch
        else{
            idex->PCSrc = false;
        }
    }
    //Took branch
    else if (idex->opCode == op_bne){
        if(idex->regRsValue != idex->regRtValue){
            idex->PCSrc = true;  //Branch taken
        }
        //Did not take branch
        else{
            idex->PCSrc = false;
        }
    }
    else if (idex->opCode == op_blitz){
        if((int)idex->regRsValue < 0){
            idex->PCSrc = true;
        }
        else{
            idex->PCSrc = false;
        }
    }
    else if (idex->opCode == op_blez){
        if((int)idex->regRsValue <= 0){
            idex->PCSrc = true;
        }
        else{
            idex->PCSrc = false;
        }
    }
    else if (idex->opCode == op_bgtz){
        if((int)idex->regRsValue > 0){
            idex->PCSrc = true;
        }
        else{
            idex->PCSrc = false;
        }
    }
}

void execute_instruction(control * idex, control * exmem) {
	word alu_rs;
	word alu_rt;
	word alu_result;

	copyPipeline(idex, exmem);

	alu_rs = idex->regRsValue;

	if(idex->ALUSrc) alu_rt = idex->immed;
	else alu_rt = idex->regRtValue;

	alu_result = idex->ALUresult;

	alu(idex->ALUop, alu_rs, alu_rt, idex->shamt, &alu_result);

	if((idex->ALUop == oper_movz && alu_rt != 0) || (idex->ALUop == oper_movn && alu_rt == 0)) idex->RegWrite = false;

	exmem->ALUresult = alu_result;
}

void memory_access(control * exmem, control * memwb)
{
	// If load or store, access memory
	//If branch, replace PC with destination address
	//Otherwise do nothing
	copyPipeline(exmem, memwb);
	switch(memwb->opCode)
	{
		case op_lw:
		case op_lb:
		case op_lbu:
		case op_lhu:
		case op_lui:
		case op_sb:
		case op_sh:
		case op_sw:
			//access memory
			accessMemory();
			break;
		case op_beq:
		case op_bne:
		case op_blitz:
		case op_bgtz:
		case op_blez:
			memwb->pcNext = memwb->address;
			break;
		default:
			break;
	}
}


void write_back(control * memwb) {
	word reg;
	word regValue;

	if(memwb->RegDst) reg = memwb->regRd;
	else reg = memwb->regRt;

	if(memwb->MemtoReg) regValue = memwb->memData;
	else regValue = memwb->ALUresult;

#ifndef REGISTERS
#ifdef TEST
	if(memwb->RegWrite) printf("Write %#08x (%d) to register %d", regValue, regValue, reg);
#endif
#else
	if(memwb->RegWrite) write_register(reg, &regValue);
#endif
}

void accessMemory()
{

}

void print_control_reg(control reg) {
	printf("---------------------------\n");
	printf("RegDst:    %#01x\n", reg.RegDst);
	printf("RegWrite:  %#01x\n", reg.RegWrite);
	printf("ALUSrc:    %#01x\n", reg.ALUSrc);
	printf("PCSrc:     %#01x\n", reg.PCSrc);
	printf("MemRead:   %#01x\n", reg.MemRead);
	printf("MemWrite:  %#01x\n", reg.MemWrite);
	printf("MemtoReg:  %#01x\n\n", reg.MemtoReg);
	printf("ALUop:     %d\n", reg.ALUop);
	printf("jump:      %#01x\n\n", reg.jump);
	printf("instr:     %#08x\n\n", reg.instr);
	printf("opCode:    %#02x\n", reg.opCode);
	printf("regRs:     %#02x\n", reg.regRs);
	printf("regRt:     %#02x\n", reg.regRt);
	printf("regRd:     %#02x\n", reg.regRd);
	printf("immed:     %d\n", reg.immed);
	printf("funct:     %d\n\n", reg.funct);
	printf("regRsValue:%d\n", reg.regRsValue);
	printf("regRtValue:%d\n\n", reg.regRtValue);
	printf("ALUresult: %d\n", reg.ALUresult);
	printf("pcNext:    %d\n", reg.pcNext);
	printf("memData:   %d\n", reg.memData);
	printf("---------------------------\n\n");


}

void copyPipeline(control* original, control* copy){
    copy->RegDst        = original->RegDst;
    copy->RegWrite      = original->RegWrite;
    copy->ALUSrc        = original->ALUSrc;
    copy->PCSrc         = original->PCSrc;
    copy->MemRead       = original->MemRead;
    copy->MemWrite      = original->MemWrite;
    copy->MemtoReg      = original->MemtoReg;
    copy->ALUop         = original->ALUop;
    copy->jump          = original->jump;
    copy->instr         = original->instr;
    copy->opCode        = original->opCode;
    copy->regRs         = original->regRs;
    copy->regRt         = original->regRt;
    copy->regRd         = original->regRd;
    copy->immed         = original->immed;
    copy->address       = original->address;
    copy->funct         = original->funct;
    copy->shamt         = original->shamt;
    copy->regRsValue    = original->regRsValue;
    copy->regRtValue    = original->regRtValue;
    copy->ALUresult     = original->ALUresult;
    copy->pcNext        = original->pcNext;
}

void init_pipeline() {
	init_control_reg(&ifid);
	init_control_reg(&idex);
	init_control_reg(&exmem);
	init_control_reg(&memwb);

	// Need to probably call init memory here as well
}

