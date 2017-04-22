/*
 * alu.h
 *
 *  Created on: Apr 22, 2017
 *      Author: jacob
 */

#ifndef ALU_H_
#define ALU_H_

#define BIT31    0x80000000

#include "types.h"
#include <stdint.h>

void alu(operation op, word rs, word rt, word shamt, word * result);

#endif /* ALU_H_ */
