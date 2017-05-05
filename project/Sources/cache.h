/*
 * cache.h
 *
 *  Created on: May 4, 2017
 *      Author: croney
 */

#ifndef CACHE_H_
#define CACHE_H_

typedef struct caches_t {
    /* Split cache options */
    unsigned int    sizeData;
    unsigned int    blockData;
    //bool            inst_enabled;
    unsigned int    sizeInstr;
    unsigned int    blockInstr;
} cache_t;

typedef struct instructionCache
{

}instructionCache_t;

typedef struct dataCache
{

}dataCache_t;

#endif /* CACHE_H_ */
