/*
 * parser.c
 *
 *  Created on: Apr 26, 2017
 *      Author: jacob
 */

#include "parser.h"

uint8_t storage[NUM_LINES][8];

int parse_input(uint32_t * length, char * filename, uint32_t * output) {
	FILE * input = fopen(filename, "r");
	if(!input) return 1;
	*length = 0;
	int i = 0;
	uint8_t temp;
	temp = fgetc(input);
	temp = fgetc(input);
	while(!feof(input)) {
		for(i = 0; i < 8; i++) {
			storage[*length][i] = fgetc(input);
		}
		do {
			temp = fgetc(input);
		} while(temp != '\n' && temp != 0xff);
		*length = *length + 1;
		temp = fgetc(input);
		temp = fgetc(input);
	}
	uint32_t tem;
	for(i = 0; i < *length; i++) {
		atoh(storage[i], &tem);
		*(output + i) = tem;
	}
	fclose(input);
	return 0;
}

void atoh(uint8_t * input, uint32_t * output) {
	int i = 0;
	uint32_t temp = 0;
	uint8_t mid;
	do {
		mid = *(input + i);
		switch(mid) {
			case ('f'):
				temp += 0xf;
				break;
			case ('e'):
				temp += 0xe;
				break;
			case ('d'):
				temp += 0xd;
				break;
			case ('c'):
				temp += 0xc;
				break;
			case ('b'):
				temp += 0xb;
				break;
			case ('a'):
				temp += 0xa;
				break;
			case ('9'):
				temp += 0x9;
				break;
			case ('8'):
				temp += 0x8;
				break;
			case ('7'):
				temp += 0x7;
				break;
			case ('6'):
				temp += 0x6;
				break;
			case ('5'):
				temp += 0x5;
				break;
			case ('4'):
				temp += 0x4;
				break;
			case ('3'):
				temp += 0x3;
				break;
			case ('2'):
				temp += 0x2;
				break;
			case ('1'):
				temp += 0x1;
				break;
			case ('0'):
				temp += 0x0;
				break;
			default:
				printf("Malformed input");
				break;
		}
		if(i != 7) temp = temp << 4;
		i++;
	} while(i < 8);
	*output = temp;
}
