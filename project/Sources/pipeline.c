/*
 * pipeline.c
 *
 *  Created on: Mar 15, 2017
 *      Author: jacob
 */

#include <stdio.h>
#include "pipeline.h"
#include "alu.h"


#define NEXT 0xF0000000
#define SHIFT_NUM 16

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

int instruction_decode( control * IFID , control * IDEX) {

	typedef uint32_t reg_Word[32];

	//initialize the registers to 0
	for(int i = 0; i < 32; i++)
		reg_Word[i] = 0;


    clonePipeline(IFID, IDEX);

    switch(IDEX->opCode){
        case op_rtype:
            IDEX->RegDst = true;
            IDEX->ALUSrc = false;
            IDEX->MemtoReg = false;
            IDEX->RegWrite = true;
            IDEX->MemRead = false;
            IDEX->MemWrite = false;
            IDEX->jump = false;
            IDEX->PCSrc = false;
            switch(IDEX->funct){
                case funct_add:
                    IDEX->ALUop = oper_Add;
                    break;
                case funct_addu:
                    IDEX->ALUop = oper_Addu;
                    break;
                case funct_and:
                    IDEX->ALUop = oper_And;
                    break;
                case funct_jr:
                    IDEX->ALUop = oper_Add;
                    IDEX->jump = true;
                    IDEX->RegWrite = false;
                    break;
                case funct_movz:
                    IDEX->ALUop = oper_Movz;
                    break;
                case funct_movn:
                    IDEX->ALUop = oper_Movn;
                    break;
                case funct_nor:
                    IDEX->ALUop = oper_Nor;
                    break;
                case funct_or:
                    IDEX->ALUop = oper_Or;
                    break;
                case funct_sll:
                    IDEX->ALUop = oper_Sll;
                    break;
                case funct_srl:
                    IDEX->ALUop = oper_Srl;
                    break;
                case funct_slt:
                    IDEX->ALUop = oper_Slt;
                    break;
                case funct_sltu:
                    IDEX->ALUop = oper_Sltu;
                    break;
                case funct_sub:
                    IDEX->ALUop = oper_Sub;
                    break;
                case funct_subu:
                    IDEX->ALUop = oper_Subu;
                    break;
                case funct_xor:
                    IDEX->ALUop = oper_Xor;
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
           IDEX->ALUop = oper_Sub;
           IDEX->ALUSrc = false;
           IDEX->RegWrite = false;
           IDEX->MemRead = false;
           IDEX->MemWrite = false;
           IDEX->jump = false;
           IDEX->PCSrc = true;
           break;
        case op_sw:
        case op_sh:
        case op_sb:
            IDEX->ALUop = oper_Addu;
            IDEX->ALUSrc = true;
            IDEX->RegWrite = false;
            IDEX->MemRead = false;
            IDEX->MemWrite = true;
            IDEX->jump = false;
            IDEX->PCSrc = false;
            break;
        case op_lw:
        case op_lb:
        case op_lh:
        case op_lbu:
        case op_lhu:
            IDEX->ALUop = oper_Addu;
            IDEX->RegDst = false;
            IDEX->ALUSrc = true;
            IDEX->MemtoReg = true;
            IDEX->RegWrite = true;
            IDEX->MemRead = true;
            IDEX->MemWrite = false;
            IDEX->jump = false;
            IDEX->PCSrc = false;
            break;
        case op_addi:
            IDEX->ALUop = oper_Add;
            IDEX->RegDst = false;
            IDEX->ALUSrc = true;
            IDEX->MemtoReg = false;
            IDEX->RegWrite = true;
            IDEX->MemRead = false;
            IDEX->MemWrite = false;
            IDEX->jump = false;
            IDEX->PCSrc = false;
            break;
        case op_addiu:
            IDEX->ALUop = oper_Addu;
            IDEX->RegDst = false;
            IDEX->ALUSrc = true;
            IDEX->MemtoReg = false;
            IDEX->RegWrite = true;
            IDEX->MemRead = false;
            IDEX->MemWrite = false;
            IDEX->jump = false;
            IDEX->PCSrc = false;
            break;
        case op_andi:
            IDEX->ALUop = oper_And;
            IDEX->RegDst = false;
            IDEX->ALUSrc = true;
            IDEX->MemtoReg = false;
            IDEX->RegWrite = true;
            IDEX->MemRead = false;
            IDEX->MemWrite = false;
            IDEX->jump = false;
            IDEX->PCSrc = false;
            break;
        case op_ori:
            IDEX->ALUop = oper_Or;
            IDEX->RegDst = false;
            IDEX->ALUSrc = true;
            IDEX->MemtoReg = false;
            IDEX->RegWrite = true;
            IDEX->MemRead = false;
            IDEX->MemWrite = false;
            IDEX->jump = false;
            IDEX->PCSrc = false;
            break;
        case op_slti:
            IDEX->ALUop = oper_Slt;
            IDEX->RegDst = false;
            IDEX->ALUSrc = true;
            IDEX->MemtoReg = false;
            IDEX->RegWrite = true;
            IDEX->MemRead = false;
            IDEX->MemWrite = false;
            IDEX->jump = false;
            IDEX->PCSrc = false;
            break;
        case op_sltiu:
            IDEX->ALUop = oper_Sltu;
            IDEX->RegDst = false;
            IDEX->ALUSrc = true;
            IDEX->MemtoReg = false;
            IDEX->RegWrite = true;
            IDEX->MemRead = false;
            IDEX->MemWrite = false;
            IDEX->jump = false;
            IDEX->PCSrc = false;
            break;
        case op_xori:
            IDEX->ALUop = oper_Xor;
            IDEX->RegDst = false;
            IDEX->ALUSrc = true;
            IDEX->MemtoReg = false;
            IDEX->RegWrite = true;
            IDEX->MemRead = false;
            IDEX->MemWrite = false;
            IDEX->jump = false;
            IDEX->PCSrc = false;
            break;
        case op_jtype:
            IDEX->ALUop = oper_Addu;
            IDEX->regRs = REGISTER_ZERO;
            IDEX->regRt = REGISTER_ZERO;
            IDEX->regRd = REGISTER_ZERO;
            IDEX->RegDst = true;
            IDEX->ALUSrc = false;
            IDEX->RegWrite = true;
            IDEX->MemRead = false;
            IDEX->MemWrite = false;
            IDEX->MemtoReg = false;
            IDEX->PCSrc = false;
            IDEX->jump = true;
            break;
        case op_jal:
            IDEX->ALUop = oper_Addu;
            IDEX->regRs = REGISTER_ZERO;
            IDEX->regRt = REGISTER_ZERO;
            IDEX->regRd = REGISTER_RA;    //Override so we can put pc in $ra
            IDEX->RegDst = true;
            IDEX->ALUSrc = false;
            IDEX->RegWrite = true;
            IDEX->MemRead = false;
            IDEX->MemWrite = false;
            IDEX->MemtoReg = false;
            IDEX->PCSrc = false;
            IDEX->jump = true;
            break;
        case op_lui:
            IDEX->ALUop = oper_Sll;
            IDEX->RegDst = false;
            IDEX->ALUSrc = true;
            IDEX->RegWrite = true;
            IDEX->MemRead = false;
            IDEX->MemWrite = false;
            IDEX->MemtoReg = false;
            IDEX->PCSrc = false;
            IDEX->jump = false;
            IDEX->shamt = SHIFT_NUM;
            break;
        default:
            break;
    }

    //for forwarding, put value of RS into Rs, same with RT. For RegRd, put ALU result into it. Read Registers.
    &(IDEX->ALUresult) = reg_Word[IDEX->regRd];
    &(IDEX->regRsValue) = reg_Word[IDEX->regRs];
    &(IDEX->regRtValue) = reg_Word[IDEX->regRt];

    IDEX->address = ( IDEX->address << 2 );            //jump address

    if(IDEX->jump && (IDEX->opCode != op_rtype)){
        IDEX->regRtValue = IDEX->pcNext;
        IDEX->pcNext = ( IDEX->pcNext & NEXT ) | IDEX->address;
    }
    else if(IDEX->jump && (IDEX->opCode == op_rtype)){
        IDEX->pcNext = IDEX->regRsValue;
    }
    else {
        IDEX->pcNext = IDEX->pcNext + ( IDEX->immed << 2 );
    }
    //Take branch
    if(IDEX->opCode == op_beq){
        if(IDEX->regRsValue == IDEX->regRtValue){
            IDEX->PCSrc = true;
        }
        //Don't take branch
        else{
            IDEX->PCSrc = false;
        }
    }
    //Took branch
    else if (IDEX->opCode == op_bne){
        if(IDEX->regRsValue != IDEX->regRtValue){
            IDEX->PCSrc = true;  //Branch taken
        }
        //Did not take branch
        else{
            IDEX->PCSrc = false;
        }
    }
    else if (IDEX->opCode == op_blitz){
        if((int)IDEX->regRsValue < 0){
            IDEX->PCSrc = true;
        }
        else{
            IDEX->PCSrc = false;
        }
    }
    else if (IDEX->opCode == op_blez){
        if((int)IDEX->regRsValue <= 0){
            IDEX->PCSrc = true;
        }
        else{
            IDEX->PCSrc = false;
        }
    }
    else if (IDEX->opCode == op_bgtz){
        if((int)IDEX->regRsValue > 0){
            IDEX->PCSrc = true;
        }
        else{
            IDEX->PCSrc = false;
        }
    }

    return 0;
}

void execute_instruction(control * idex, control * exmem) {
	word alu_rs;
	word alu_rt;
	word alu_result;

	alu_rs = idex->regRsValue;

	if(idex->ALUSrc) alu_rt = idex->immed;
	else alu_rt = idex->regRtValue;

	alu_result = idex->ALUresult;

	alu(idex->ALUop, alu_rs, alu_rt, idex->shamt, &alu_result);

	if((idex->ALUop == oper_movz && alu_rt != 0) || (idex->ALUop == oper_movn && alu_rt == 0)) idex->RegWrite = false;

	exmem->ALUresult = alu_result;
}

void print_control_reg(control reg) {
	printf("opCode:   %#02x\n", reg.opCode);
	printf("regRs:    %#04x\n", reg.regRs);
	printf("regRd:    %#04x\n", reg.regRd);
	printf("regRt:    %#04x\n", reg.regRt);
	printf("shamt:    %#04x\n", reg.shamt);
	printf("address:  %#04x\n", reg.address);
	printf("funct:    %#02x\n", reg.funct);
	printf("immed:    %d\n\n", reg.immed);
	printf("pc:       %d\n", reg.pcNext);
	printf("RegDst:   %d\n", reg.RegDst);
	printf("RegWrite: %d\n", reg.RegWrite);
	printf("ALUSrc:   %d\n", reg.ALUSrc);
	printf("PCSrc:    %d\n", reg.PCSrc);
	printf("MemRead:  %d\n", reg.MemRead);
	printf("MemWrite: %d\n", reg.MemWrite);
	printf("MemtoReg: %d\n", reg.RegDst);


}

void clonePipeline(control* original, control* clone){
    clone->RegDst        = original->RegDst;
    clone->RegWrite      = original->RegWrite;
    clone->ALUSrc        = original->ALUSrc;
    clone->PCSrc         = original->PCSrc;
    clone->MemRead       = original->MemRead;
    clone->MemWrite      = original->MemWrite;
    clone->MemtoReg      = original->MemtoReg;
    clone->ALUop         = original->ALUop;
    clone->jump          = original->jump;
    clone->instr         = original->instr;
    clone->opCode        = original->opCode;
    clone->regRs         = original->regRs;
    clone->regRt         = original->regRt;
    clone->regRd         = original->regRd;
    clone->immed         = original->immed;
    clone->address       = original->address;
    clone->funct         = original->funct;
    clone->shamt         = original->shamt;
    clone->regRsValue    = original->regRsValue;
    clone->regRtValue    = original->regRtValue;
    clone->ALUresult     = original->ALUresult;
    clone->pcNext        = original->pcNext;
}

