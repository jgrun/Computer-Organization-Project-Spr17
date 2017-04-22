/*
 * alu.c
 *
 *  Created on: Apr 22, 2017
 *      Author: jacob
 */

#include "alu.h"

void alu(operation op, word rs, word rt, word shamt, word * result) {
	int32_t temp; // used in in case of overflow
	switch (op) {
		case oper_Add:
			temp = (int32_t)rs + (int32_t)rt;
			if(((BIT31 && rs) == (BIT31 && rt)) && ((BIT31 && temp) ^ (BIT31 && rs))) *result = temp;
			return;
			break;
		case oper_Addu:
			*result = (uint32_t)rs + (uint32_t)rt;
			return;
			break;
		case oper_And:
			*result = rs & rt;
			return;
			break;
		case oper_movz:
			if(rt == 0) *result = rs;
			return;
			break;
		case oper_movn:
			if(rt != 0) *result = rs;
			return;
			break;
		case oper_Nor:
			*result = ~(rs | rt);
			return;
			break;
		case oper_Or:
			*result = rs | rt;
			return;
			break;
		case oper_seb:
			if(rt & 0x80) *result = (rt | EXTEND8);
			else *result = rt;
			return;
			break;
		case oper_seh:
			if(rt & 0x8000) *result = (rt | EXTEND16);
			else *result = rt;
			break;
		case oper_Sll:
			*result = rt << shamt;
			return;
			break;
		case oper_Srl:
			*result = rt >> shamt;
			return;
			break;
		case oper_Slt:
			if((int32_t)rs < (int32_t)rt) *result = 1;
			else *result = 0;
			return;
			break;
		case oper_Sltu:
			if((uint32_t)rs < (uint32_t)rt) *result = 1;
			else *result = 0;
			return;
			break;
		case oper_Sub:
			temp = (int32_t)rs - (int32_t)rt;
			if(((BIT31 && rs) == (BIT31 && rt)) && ((BIT31 && temp) ^ (BIT31 && rs))) *result = temp;
			return;
			break;
		case oper_Subu:
			*result = (uint32_t)rs - (uint32_t)rt;
			return;
			break;
		case oper_Xor:
			*result = rs ^ rt;
			break;
		default:
			printf("alu hit default state\n");
			break;
	}
}
