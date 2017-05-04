/*
 * main.c
 *
 *  Created on: Mar 15, 2017
 *      Author: jacob
 */
#include <stdio.h>
#include "pipeline.h"
#include "types.h"
#include "parser.h"
#include "memory.h"

pc_t pc = 0;

extern control * ifid;
extern control * idex;
extern control * exmem;
extern control * memwb;

int main(int argc, char * argv[]) {

#ifdef TEST_REGISTERS
	init_registers();
	word value = 0;
	for(value = 0; value < 32; value++) {
		write_register(value, &value);
	}
	print_registers();
#endif

#ifdef TEST_PIPELINE
	init_registers();
	instruction_fetch(&ifid, &pc);
	print_control_reg(ifid);
	instruction_decode(&ifid, &idex);
	print_control_reg(idex);
	execute_instruction(&idex, &exmem);
	print_control_reg(exmem);
#endif

#ifdef TEST_PARSER
	uint32_t length;
	char filename[] = FILE_NAME;
	uint32_t output[NUM_LINES];

	if(parse_input(&length, filename, output)) printf("Didn't read\n");
	int i = 0;
	for(i = 0; i < NUM_LINES; i++) {
		printf("%08x\n", output[i]);
	}
#endif

#ifdef TEST_MEMORY
	init_memory(4096);
	printf("mem size = %d\n", mem_size_words());
	int i = 0;
	word data;
	for(i = 0; i < 3; i++) {
		data = (word)(0x123456 - i);
		mem_write_word(0 + 12*i, &data);
		mem_write_halfword(4 + 12*i, &data);
		mem_write_byte(8 + 12*i, &data);
	}
	for(i = 0; i < 36; i += 4) {
		mem_read_word(i, &data);
		printf("word %d:     0x%08x\n", i, data);
		mem_read_halfword(i, &data);
		printf("halfword %d: 0x%08x\n", i, data);
		mem_read_byte(i, &data);
		printf("byte %d:     0x%08x\n", i, data);
		printf("\n");
	}

	mem_free();
#endif

#ifdef TEST_INSTR_MOVE
	init_memory(4096);
	uint32_t length;
	char filename[] = FILE_NAME;
	uint32_t output[NUM_LINES];
	parse_input(&length, filename, output);
	int i;
	for(i = 0; i < NUM_LINES; i++) {
		mem_write_word(4*i, &output[i]);
	}
	dump_memory_bytes(NUM_LINES);

	mem_free();
#endif

#ifdef TEST_INIT
	uint32_t length;
	char filename[] = FILE_NAME;
	uint32_t output[NUM_LINES];

	// Initializations
	init_memory(4096);
	init_registers();
	init_pipeline();

	// Useful variables
	int i;
	word data;

	// Setup before execution
	parse_input(&length, filename, output);

	for(i = 0; i < NUM_LINES; i++) {
		mem_write_word(4*i, &output[i]);
	}

	// Write sp, fp and pc to registers
	mem_read_word(0, &data);
	write_register(r_SP, &data);
	mem_read_word(1 << 2, &data);
	write_register(r_FP, &data);
	mem_read_word(5 << 2, &pc);
	pc <<= 2;

	instruction_fetch(ifid, &pc);
	instruction_decode(ifid, idex);
	execute_instruction(idex, exmem);
	memory_access(exmem, memwb);
	write_back(memwb);

	pc += 4;

	instruction_fetch(ifid, &pc);
	instruction_decode(ifid, idex);
	execute_instruction(idex, exmem);
	memory_access(exmem, memwb);
	write_back(memwb);

	print_registers();

	mem_free();
#endif

	while(1);
}
