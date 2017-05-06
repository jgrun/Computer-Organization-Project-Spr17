/*
 * cache.h
 *
 *  Created on: May 4, 2017
 *      Author: croney
 */

#ifndef CACHE_H_
#define CACHE_H_

typedef struct caches {
    /* Split cache options */
    bool			dataOn;
	unsigned int    sizeData;
    unsigned int    blockData;
    bool            instructionOn;
    unsigned int    sizeInstr;
    unsigned int    blockInstr;
    unsigned int 	writeType;  //writeback or writethrough
} cache_t;

typedef struct instructionCache
{

}instructionCache_t;

typedef struct dataCache
{

}dataCache_t;

directCache * cacheSetup(uint32_t blockNum, uint32_t blockSize)
uint32_t calculateIndex(int num);
void setDataAndInstructionCache(cache_t *cache_new);





#endif /* CACHE_H_ */
