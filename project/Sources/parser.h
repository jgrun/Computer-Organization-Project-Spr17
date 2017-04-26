/*
 * parser.h
 *
 *  Created on: Apr 26, 2017
 *      Author: jacob
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <stdio.h>
#include "types.h"
#include "memory.h"

int parse_input(uint32_t * length, char * filename, uint32_t * output);

void atoh(uint8_t * input, uint32_t * output);




#endif /* PARSER_H_ */
