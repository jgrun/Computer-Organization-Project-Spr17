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

#define NEGATIVE 0x00008000
#define EXTEND16 0xffff0000
#define EXTEND8  0xffffff00


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

// Enumerate all "operations" (R/J/I type instruction action)
// See http://alumni.cs.ucr.edu/~vladimir/cs161/mips.html
// These are used internally to represent operations between stages
typedef enum Operations {
    // Arithmetic and logical
    oper_Add,
    oper_Addu,
    oper_Addi,
    oper_Addiu,
    oper_And,
    oper_Andi,
    oper_Div,    // Probably not supported
    oper_Divu,   // Probably not supported
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
    // Constant-manipulating
    oper_Lhi,
    oper_Llo,
    // Comparison
    oper_Slt,
    oper_Sltu,
    oper_Slti,
    oper_Sltiu,
    // Branch
    oper_Beq,
    oper_Btqz,
    oper_Blez,
    oper_Bne,
    // Jump
    oper_J,
    oper_Jal,
    oper_Jalr,
    oper_Jr,
    // Load
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

typedef enum REGISTERNames {
    REGISTER_ZERO    =  0,
    REGISTER_AT      =  1,
    REGISTER_V0      =  2,
    REGISTER_V1      =  3,
    REGISTER_A0      =  4,
    REGISTER_A1      =  5,
    REGISTER_A2      =  6,
    REGISTER_A3      =  7,
    REGISTER_T0      =  8,
    REGISTER_T1      =  9,
    REGISTER_T2      = 10,
    REGISTER_T3      = 11,
    REGISTER_T4      = 12,
    REGISTER_T5      = 13,
    REGISTER_T6      = 14,
    REGISTER_T7      = 15,
    REGISTER_S0      = 16,
    REGISTER_S1      = 17,
    REGISTER_S2      = 18,
    REGISTER_S3      = 19,
    REGISTER_S4      = 20,
    REGISTER_S5      = 21,
    REGISTER_S6      = 22,
    REGISTER_S7      = 23,
    REGISTER_T8      = 24,
    REGISTER_T9      = 25,
    REGISTER_K0      = 26,
    REGISTER_K1      = 27,
    REGISTER_GP      = 28,
    REGISTER_SP      = 29,
    REGISTER_FP      = 30,
    REGISTER_RA      = 31
}register_t;


#endif /* _TYPES_H */
