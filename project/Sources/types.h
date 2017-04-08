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

typedef struct CONTROL_REGISTER {
	bool RegDst; // rd if 0, rt if 1
	bool RegWrite; // nothing if 0, write register is written from write data input
	bool ALUSrc; // second ALU operand comes from second register file output if 0 or sign extended lower 16 bits of instruction if 1
	bool PCSrc; // PC is incremented by 4 normally if 0, branch taken if 1
	bool MemRead; // nothing if 0, data memory contents designated by the address input are put on the read data output if 1
	bool MemWrite; // nothing if 0, data memory contents designated by the address input are replaced by the value on the write data input if 1
	bool MemtoReg; // The value fed to the register write data comes from the ALU if 0, from data memory if 1
};

#endif /* TYPES_H_ */
