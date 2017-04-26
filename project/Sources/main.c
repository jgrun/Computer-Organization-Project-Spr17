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

//#define REGISTERS

//#define TEST_REGISTERS
//#define TEST_PIPELINE
#define TEST_PARSER

int main(int argc, char * argv[]) {
	pc_t pc = 0;

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
	instruction_fetch(&ifid, &pc, 0x2229FFF6);
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

	while(1);
}
