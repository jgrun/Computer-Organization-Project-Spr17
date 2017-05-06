/*
 * caches.c
 *
 *  Created on: Apr 27, 2017
 *      Author: croney
 */
//2-way set associative data cache, single line (Two 512 Byte Caches):

cache_t cache_orig;

#include "cache.h"

typedef struct dirBlock{
    bool *validBit;
    bool dirtyBit;
    tag_t tagBit;
    word_t *dataBit;
} dirCacheBlock;

typedef struct directCache
{
	    uint32_t blockNum;
	    uint32_t blockSize;
	    uint32_t tagSize;
	    uint32_t tagMask;
	    uint32_t indexSize;
	    uint32_t indexMask;
	    uint32_t inIndexSize;
	    uint32_t inIndexMask;
	    //Flag to tell if active fetch from memory
	    bool fetching;
	    //Used for getting multiple block lines
	    uint8_t afterFetch;
	    uint32_t penaltyNum;
	    uint32_t address;
	    dirCacheBlock *blocks;
	    word_t *words;

}dirCache;

typedef struct writeBuffer {
    uint32_t addressVal;
    bool writing;
    uint32_t penaltyNum;
    uint32_t afterWrite;
    word_t *dataVal;
} writeBuff;

typedef struct PROFILE {
    cache_status_t  i_cache_status;
    cache_status_t  i_cache_status_prev;
    uint32_t        i_cache_hit_count;
    uint32_t        i_cache_access_count;
    cache_status_t  d_cache_status;
    cache_status_t  d_cache_status_prev;
    uint32_t        d_cache_hit_count;
    uint32_t        d_cache_access_count;
    uint32_t        instruction_count;
    uint32_t        cycles;
    uint32_t        debug;
} profile_t;

void setDataAndInstructionCache(cache_t *cache_new)
{
    cache_orig = (cache_t*)malloc(sizeof(cache_t));
    memcpy(cache_orig, cache_new, sizeof(cache_t));

	//Set Data Cache
    uint32_t blocks = (cache_new->sizeData/4) / cache_new->blockData;
    dataCache_t = cacheSetup(blocks, cache_new->blockData);

    //Set Instruction Cache
    uint32_t num_blocks = (cache_new->sizeInstr/4) / cache_new->blockInstr;
    instructionCache_t = cacheSetup(num_blocks, cache_new->blockInstr);
}


directCache * cacheSetup(uint32_t blockNum, uint32_t blockSize)
{
    typedef uint32_t words;
	words *word = (words *)malloc(sizeof(words)*blockNum*blockSize);
    dirCache *dirCache1 = (dirCache *)malloc(sizeof(dirCache));
    dirCacheBlock *cacheBlocks = (dirCacheBlock *)malloc(sizeof(dirCacheBlock) * blocksize);
    bool *validBits = (bool *)malloc(sizeof(bool) * blockNum * blockSize);
    uint32_t i = 0;
    for(i = 0; i < blockNum; i++)
    {
        cacheBlocks[i].validBit = validBits + i * blockSize;
        cacheBlocks[i].dataBit = word + i * blockSize;

    }

    //Set up the fetch variables
    dirCache1->fetching = false;
    dirCache1->penaltyNum = 0;
    dirCache1->afterFetch = 0;

    dirCache1->blocks = cacheBlocks;
    dirCache1->words = word;

    dirCache1->blockNum = blockNum;
    dirCache1->blockSize = blockSize;

    uint32_t indexSize = calculateIndex(blockNum);
    dirCache1->indexSize = indexSize;

    uint32_t firstIndex = calculateIndex(blockSize);
    dirCache1->inIndexSize = firstIndex;

    dirCache1->inIndexMask = ((1 << (firstIndex + 2)) - 1) & ~3;
    dirCache1->tagSize = 32 - dirCache1->indexSize - dirCache1->inIndexSize - 2;
    dirCache1->indexMask = ((1 << (dirCache1->indexSize + dirCache1->inIndexSize + 2)) - 1);
    dirCache1->tagMask = ~dirCache1->indexMask;
    dirCache1->indexMask &= ~(dirCache1->inIndexMask | 0x3);

    //Invalidate all data in the cache
    for(int i = 0; i < dirCache1->blockNum; i++){
        dirCache1->blocks[i].dirtyBit = false;
        for(int j = 0; j < dirCache1->blockSize; j++){
            dirCache1->blocks[i].validBit[j] = false;
        }
    }
    return dirCache1;
}

uint32_t calculateIndex(int num)
{
    uint32_t index = 1;
    while((num>>index) != 0)
    	index+=1;
    index--;

    return index;
}
