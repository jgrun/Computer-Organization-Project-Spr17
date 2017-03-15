/*
 * pipeline.h
 *
 *  Created on: Mar 15, 2017
 *      Author: jacob
 */

#ifndef PIPELINE_H_
#define PIPELINE_H_

typedef struct IFID_t {

}IFID;

typedef struct IDEX_t {

}IDEX;

typedef struct EXMEM_t {

}EXMEM;

typedef struct MEMWB_t {

}MEMWB;

void instruction_fetch(IFID * ifid);

void instruction_decode(IFID * ifid, IDEX * idex);

void execute_instruction(IDEX * idex, EXMEM * exmem);

void memory_access(EXMEM * exmem, MEMWB * memwb);

void write_back(MEMWB * memwb)

#endif /* PIPELINE_H_ */
