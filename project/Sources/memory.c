/*
 * memory.c
 *
 *  Created on: Apr 24, 2017
 *      Author: jacob
 */

#include "memory.h"

uint8_t * main_mem;
uint32_t mem_size; // length of memory in words
const uint32_t instr_end = (NUM_LINES + 1) * 4;

// Input number of words wanted
int init_memory(uint32_t size) {
	main_mem = (uint8_t *)malloc(size * sizeof(word));
	if(!main_mem) return 1; // if malloc fails return 1;
	mem_size = size;
	int i = 0;
	for(i = 0; i < 4 * size; i++) {
		*(main_mem + i) = 0;
	}
	return 0;
}

void mem_free() {
	free(main_mem);
	mem_size = 0;
}

uint32_t mem_size_bytes() {
	return mem_size >> 2; // mem_size is in words, so need to divide by 4 to get bytes
}

uint32_t mem_size_words() {
	return mem_size; // return mem_size since it is already in words
}

void mem_read_word(uint32_t address, word * data) {
	*data = *((uint32_t*)(main_mem + address));
}

void mem_read_halfword(uint32_t address, word * data) {
	*data = *((uint16_t *)(main_mem + address));
	*data &= 0x0000ffff;
}

void mem_read_byte(uint32_t address, word * data) {
	*data = *(main_mem + address);
	*data &= 0xff;
}

void mem_write_word(uint32_t address, word * data) {
	uint32_t index = address;
	*((uint32_t*)(main_mem + index)) = *data;
}

void mem_write_halfword(uint32_t address, word * data) {
	uint32_t index = address;
	*((uint16_t*)(main_mem + index)) = (*data & 0xffff);
}

void mem_write_byte(uint32_t address, word * data) {
	uint32_t index = address;
	*(main_mem + index) = (*data & 0xff);
}

void init_control_reg(control ** reg) {
	*reg = (control *)malloc(sizeof(control));
	empty_reg(*reg);
}

void empty_reg(control * reg) {
	reg->RegDst    = false;
	reg->RegWrite  = false;
	reg->ALUSrc    = false;
	reg->PCSrc     = false;
	reg->MemRead   = false;
	reg->MemWrite  = false;
	reg->MemtoReg  = false;
	reg->ALUop     = 0;
	reg->jump      = false;
	reg->instr     = 0;
	reg->opCode    = 0;
	reg->regRs     = 0;
	reg->regRt     = 0;
	reg->regRd     = 0;
	reg->immed     = 0;
	reg->address   = 0;
	reg->funct     = 0;
	reg->shamt     = 0;
	reg->regRsValue= 0;
	reg->regRtValue= 0;
	reg->ALUresult = 0;
	reg->pcNext    = 0;
	reg->memData   = 0;
}

void dump_memory_bytes(uint32_t size) {
	int i;
	word data;
	for(i = 0; i < size; i++) {
		mem_read_word(4*i, &data);
		printf("0x%08x: 0x%08x\n", (main_mem + 4*i), data);
	}
}

