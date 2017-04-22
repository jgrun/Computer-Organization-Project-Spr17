/*
 * alu.c
 *
 *  Created on: Apr 22, 2017
 *      Author: jacob
 */

#include "alu.h"

void alu(operation op, word rs, word rt, word shamt, word * result) {
	switch (op) {
		case oper_Add:
			break;
		case oper_Addu:
			break;
		case oper_And:
			break;
		case oper_movz:
			break;
		case oper_movn:
			break;
		case oper_Nor:
			break;
		case oper_Or:
			break;
		case oper_seb:
			break;
		case oper_seh:
			break;
		case oper_Sll:
			break;
		case oper_Srl:
			break;
		case oper_Sltu:
			break;
		case oper_Sub:
			break;
		case oper_Subu:
			break;
		case oper_Xor:
			break;
		default:
			printf("alu hit default state\n");
			break;
	}
}
