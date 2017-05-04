/*
 * hazards.c
 *
 *  Created on: May 4, 2017
 *      Author: jacob
 */

#include "hazards.h"

control * backup_ifid;
control * backup_idex;
control * backup_exmem;
control * backup_memwb;
pc_t backup_pc;

void init_hazards() {
	init_control_reg(&backup_ifid);
	init_control_reg(&backup_idex);
	init_control_reg(&backup_exmem);
	init_control_reg(&backup_memwb);
}

void hazard_detection(control * ifid, control * idex, control * exmem, control * memwb, pc_t * pc) {
	int forwarding = 0;
	backup_pc = *pc;

	int stall = 0;
	uint32_t exDest = 0;
	if(exmem->RegDst) {
		exDest = exmem->regRd;
	}
	else exDest = exmem->regRt;

}
