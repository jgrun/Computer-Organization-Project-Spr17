/*
 * pipeline.h
 *
 *  Created on: Mar 15, 2017
 *      Author: jacob
 */

#ifndef PIPELINE_H_
#define PIPELINE_H_

void instruction_fetch();

void instruction_decode();

void execute_instruction();

void memory_access();

void write_back();

#endif /* PIPELINE_H_ */

