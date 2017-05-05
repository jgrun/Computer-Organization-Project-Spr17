/*
 * types.h
 *
 *  Created on: Apr 8, 2017
 *      Author: jacob
 */
#ifndef _TYPES_H
#define _TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEGATIVE 0x00008000
#define EXTEND16 0xffff0000
#define EXTEND8  0xffffff00
#define BIT8     0x00000080
#define BIT16    0x00008000

/***************************************************************
 * To run Program2File.txt copy "Program2File.txt" and paste
 * 	into definition for FILE_NAME. NUM_LINES should equal 274
 *
 * To run Program1File.txt copy "Program1File.txt" and paste
 *  into definition for FILE_NAME. NUM_LINES should equal 493
 *
 * Should define appropriate part for program.
 */

#define PART1
//#define PART2
#define NUM_LINES 493
#define FILE_NAME "Program1File.txt"

//#define REGISTERS

//#define TEST_REGISTERS
//#define TEST_PIPELINE
//#define TEST_PARSER
//#define TEST_MEMORY
//#define TEST_INSTR_MOVE
//#define TEST_INIT
#define TEST_FULL_PIPELINE


// 32 bit instructions
typedef uint32_t inst;
// store program counter as uint32
typedef uint32_t pc_t;
// words are also 32 bits
typedef uint32_t word;

// make opcodes easier to use
typedef enum OpCodes {
    op_rtype   = 0x00,
    op_addi    = 0x08, // add immediate word
    op_addiu   = 0x09, // add immediate unsigned word
    op_andi    = 0x0c,
    op_beq     = 0x04,
    op_bne     = 0x05,
    op_blitz   = 0x01, // branch on less than zero
    op_bgtz    = 0x07,
    op_blez    = 0x06, // branch on less than equal to zero
    op_jtype   = 0x02, // jump
    op_jal     = 0x03, // jump and link
    op_lb      = 0x20, // load byte
    op_lbu     = 0x24, // load byte unsigned
    op_lh      = 0x21, // load halfword
    op_lhu     = 0x25, // load halfword unsigned
    op_lui     = 0x0f, // load upper immediate
    op_lw      = 0x23, // load word
    op_ori     = 0x0d,
    op_sb      = 0x28, // store byte
    op_sh      = 0x29, // store halfword
    op_slti    = 0x0a, // Set on less than immediate
    op_sltiu   = 0x0b, // Set on less than unsigned immediate
    op_sw      = 0x2b,
    op_xori    = 0x0e
} opcode;

//r-type
typedef enum FunctCodes {
    funct_add     = 0x20,
    funct_addu    = 0x21,
    funct_and     = 0x24,
    funct_jr      = 0x08, // jump register
	funct_movn    = 0x0b, //move on not zero
    funct_movz    = 0x0a, //move on zero
    funct_nor     = 0x27,
    funct_or      = 0x25,
    funct_sll     = 0x00, // shift word left logical
    funct_slt     = 0x2a, // set on less than
    funct_sltu    = 0x2b, // set on less than unsigned
    funct_srl     = 0x02, // shift word right logical
    funct_sub     = 0x22,
    funct_subu    = 0x23,
    funct_xor     = 0x26
} function;

typedef enum Operations {
    oper_Add,
    oper_Addu,
    oper_Addi,
    oper_Addiu,
    oper_And,
    oper_Andi,
    oper_Div,
    oper_Divu,
    oper_Mult,
    oper_Multu,
    oper_Nor,
    oper_Or,
    oper_Ori,
	oper_Movn,
	oper_Movz,
    oper_Sll,
    oper_Sllv,
    oper_Sra,
    oper_Srav,
    oper_Srl,
    oper_Srlv,
    oper_Sub,
    oper_Subu,
    oper_Xor,
    oper_Xori,
    oper_Lhi,
    oper_Llo,
    oper_Slt,
    oper_Sltu,
    oper_Slti,
    oper_Sltiu,
    oper_Beq,
    oper_Btqz,
    oper_Blez,
    oper_Bne,
    oper_J,
    oper_Jal,
    oper_Jalr,
    oper_Jr,
    oper_lb,
    oper_lbu,
    oper_Lh,
    oper_Lhu,
    oper_Lw,
    oper_Sb,
    oper_Sh,
    oper_Sw,
	oper_movn,
	oper_movz,
    oper_Mfhi,
    oper_Mflo,
    oper_Mthi,
    oper_Mtlo,
    oper_seb,
	oper_seh
}operation;

typedef struct CONTROL_REGISTER {
	bool RegDst; // rd if 0, rt if 1
	bool RegWrite; // nothing if 0, write register is written from write data input
	bool ALUSrc; // second ALU operand comes from second register file output if 0 or sign extended lower 16 bits of instruction if 1
	bool PCSrc; // PC is incremented by 4 normally if 0, branch taken if 1
	bool MemRead; // nothing if 0, data memory contents designated by the address input are put on the read data output if 1
	bool MemWrite; // nothing if 0, data memory contents designated by the address input are replaced by the value on the write data input if 1
	bool MemtoReg; // The value fed to the register write data comes from the ALU if 0, from data memory if 1

    operation ALUop; // ALU operation
    bool jump; // perform jump

    inst instr; // Raw instruction

    opcode opCode;
    uint32_t regRs;
    uint32_t regRt;
    uint32_t regRd;
    uint32_t immed;
    uint32_t address;
    function funct;
    uint32_t shamt;

    uint32_t regRsValue;
    uint32_t regRtValue;

    uint32_t ALUresult;
    uint32_t pcNext;
    uint32_t memData;
}control;

typedef struct sim_results_t {
	uint32_t instruction_count;
	uint32_t cycles;
}sim_results;

void init_sim(sim_results * sim);

void startup();

#endif /* _TYPES_H */
