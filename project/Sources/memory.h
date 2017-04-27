/*
 * memory.h
 *
 *  Created on: Apr 24, 2017
 *      Author: jacob
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#include "types.h"

int init_memory(uint32_t size);

void init_control_reg(control ** reg);

void empty_reg(control * reg);

#endif /* MEMORY_H_ */
