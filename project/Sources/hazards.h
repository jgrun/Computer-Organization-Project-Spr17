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

void hazard_detection(control * ifid, control * idex, control * exmem, control * memwb, pc_t * p, sim_results * sim);

void backup_pipeline(control * ifid, control * idex, control * exmem, control * memwb, pc_t * p);

void restore_pipeline(control * ifid, control * idex, control * exmem, control * memwb, pc_t * p);

#endif /* HAZARDS_H_ */
