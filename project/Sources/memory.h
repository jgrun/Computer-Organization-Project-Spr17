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

void mem_free();

uint32_t mem_size_bytes();

uint32_t mem_size_words();

void mem_read_word(uint32_t address, word * data);

void mem_read_halfword(uint32_t address, word * data);

void mem_read_byte(uint32_t address, word * data);

void mem_write_word(uint32_t address, word * data);

void mem_write_halfword(uint32_t address, word * data);

void mem_write_byte(uint32_t address, word * data);

void init_control_reg(control ** reg);

void empty_reg(control * reg);

void dump_memory_bytes(uint32_t size);

#endif /* MEMORY_H_ */
