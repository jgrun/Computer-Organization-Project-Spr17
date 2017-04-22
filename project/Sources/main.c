/*
 * main.c
 *
 *  Created on: Mar 15, 2017
 *      Author: jacob
 */
#include <stdio.h>
#include "pipeline.h"
#include "types.h"


int main() {
	control ifid;
	pc_t pc = 0;
	instruction_fetch(&ifid, &pc, 0x2229FFF6);
	print_control_reg(ifid);
	while(1);
}
