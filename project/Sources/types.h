/*
 * types.h
 *
 *  Created on: Apr 8, 2017
 *      Author: jacob
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <stdbool.h>

#define bool int
#define true 1
#define false 0

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

// Represents a 32-bit instruction
typedef uint32_t inst;
// Represents a 32-bit program counter
typedef uint32_t pc_t;
// Represents a single word (32b) of memory, with ambiguous signedness
typedef uint32_t word;

// Mapping opcode values to mnemonic
typedef enum OpCodes {
    op_Rtype   = 0x00,
    op_Addi    = 0x08, // 0b001000, Add Immediate Word
    op_Addiu   = 0x09, // 0b001001, Add Immediate Unsigned Word
    op_Andi    = 0x0c, // 0b001100, And Immediate
    op_Beq     = 0x04, // 0b000100, Branch on Equal
    op_Bne     = 0x05, // 0b000101, Branch on Not Equal
    op_Blitz    = 0x01, // 0b000001, Branch on less than zero
    op_Bgtz    = 0x07, // 0b000111, Branch on greater than zero
    op_Blez    = 0x06, // 0b000110, Branch on less than equal to zero
    op_Jtype   = 0x02, // 0b000010, Jump
    op_Jal     = 0x03, // 0b000011, Jump And Link
    op_Lb      = 0x20, // 0b100000, Load Byte
    op_Lbu     = 0x24, // 0b100100, Load Byte Unsigned
    op_Lh      = 0x21, // 0b100001, Load Halfword
    op_Lhu     = 0x25, // 0b100101, Load Halfword Unsigned
    op_Lui     = 0x0f, // 0b001111, Load Upper Immediate
    op_Lw      = 0x23, // 0b100011, Load Word
    op_Ori     = 0x0d, // 0b001101, Or Immediate
    op_Sb      = 0x28, // 0b101000, Store Byte
    op_Sh      = 0x29, // 0b101001, Store Halfword
    op_Slti    = 0x0a, // 0b001010, Set on Less Than Immediate
    op_Sltiu   = 0x0b, // 0b001011, Set on Less Than Immediate Unsigned
    op_Sw      = 0x2b, // 0b101011, Store Word
    op_Xori    = 0x0e  // 0b001110, Exclusive OR Immediate
} opcode;

// Mapping funct values to mnemonic (R-type, opcode=0x0)
typedef enum FunctCodes {
    funct_Add     = 0x20, // 0b100000, Add Word
    funct_Addu    = 0x21, // 0b100001, Add Unsigned Word
    funct_And     = 0x24, // 0b100100, And
    funct_Jr      = 0x08, // 0b001000, Jump REGISTERister
    funct_Nor     = 0x27, // 0b100111, Not Or
    funct_Or      = 0x25, // 0b100101, Or
    funct_Sll     = 0x00, // 0b000000, Shift Word Left Logical
    funct_Slt     = 0x2a, // 0b101010, Set On Less Than
    funct_Sltu    = 0x2b, // 0b101011, Set on Less Than Unsigned
    funct_Srl     = 0x02, // 0b000010, Shift Word Right Logical
    funct_Sub     = 0x22, // 0b100010, Subtract Word
    funct_Subu    = 0x23, // 0b100011, Subtract Unsigend Word
    funct_Xor     = 0x26  // 0b100110, Exclusive OR
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

    oper_Mfhi,
    oper_Mflo,
    oper_Mthi,
    oper_Mtlo,

    oper_Trap
}operation;


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
}register;


#endif /* _TYPES_H */
