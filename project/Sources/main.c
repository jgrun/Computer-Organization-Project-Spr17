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
	control idex;
	pc_t pc = 0;
	instruction_fetch(&ifid, &pc, 0x2229FFF6);
	instruction_decode(&ifid, &idex);
	print_control_reg(ifid);
	while(1);
}
