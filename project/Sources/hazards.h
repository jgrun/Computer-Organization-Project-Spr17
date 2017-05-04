/*
 * hazards.h
 *
 *  Created on: May 4, 2017
 *      Author: jacob
 */

#ifndef HAZARDS_H_
#define HAZARDS_H_

#include "types.h"
#include "reg.h"
#include "pipeline.h"

void init_hazards();

void hazard_detection(control * ifid, control * idex, control * exmem, control * memwb, pc_t * pc);

#endif /* HAZARDS_H_ */
