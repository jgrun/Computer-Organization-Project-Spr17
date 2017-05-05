/*
 * caches.c
 *
 *  Created on: Apr 27, 2017
 *      Author: croney
 */
//2-way set associative data cache, single line (Two 512 Byte Caches):

cache_t cache_orig;

typedef struct directCahes
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
	    uint8_t subsequent_fetching;
	    uint32_t penalty_count;
	    uint32_t target_address;
	    //direct_cache_block_t *blocks;
	    word_t *words;


}directCache;
typedef dCBlock;

void setDataAndInstructionCache(cache_t *cache_new)
{
    cache_orig = (cache_t*)malloc(sizeof(cache_t));
    memcpy(cache_orig, cache_new, sizeof(cache_t));

	//Set Data Cache
    uint32_t blocks = (cache_new->sizeData/4) / cache_new->blockData;
    dataCache_t = direct_cache_init(blocks, cache_new->blockData);

    //Set Instruction Cache
    uint32_t num_blocks = (cache_new->sizeInstr/4) / cache_new->blockInstr;
    instructionCache_t = directCacheInitialization(num_blocks, cache_new->blockInstr);
}

/*
directCache * directCacheInitialization(uint32_t blocks, uint32_t size)
{
    typedef words;
	words *word = (words *)malloc(sizeof(words)*blocks*size);
    directCache *dirCache = (directCache *)malloc(sizeof(directCache));
    dCBlock *numBlocks = (dCBlock *)malloc(sizeof(dCBlock) * blocks);
    bool *validBits = (bool *)malloc(sizeof(bool) * blocks * size);
    uint32_t i = 0;
    for(i = 0; i < blocks; i++)
    {
        blocks[i].valid = validBits + i * size;
        blocks[i].data = word + i * size;

    }

    dirCache->blocks = blocks;
    dirCache->words = words;
    //crash if unable to allocate memory
    if(cache == NULL || cache->blocks == NULL){
        cprintf(ANSI_C_RED, "cache_init: Unable to allocate direct mapped cache\n");
        assert(0);
    }
    cache->num_blocks = num_blocks;
    cache->block_size = block_size;

    //get the number of bits the index takes up
    uint32_t index_size = 1;
    while((num_blocks>>index_size) != 0) index_size+=1;
    index_size--;
    cache->index_size = index_size;
    //cache size is 2^n blocks, so n bits are needed for the index
    //block size is 2^m words, m bits needed for word within block
    //tag bits = 32 - (n + m + 2)
    //This is magic. Look in the header file for some sort of explanation
    uint32_t inner_index_size = 1;
    while((block_size>>inner_index_size) != 0) inner_index_size+=1;
    inner_index_size--;
    cache->inner_index_size = inner_index_size;
    cache->inner_index_mask = ((1 << (inner_index_size + 2)) - 1) & ~3;
    cache->tag_size = 32 - cache->index_size - cache->inner_index_size - 2;
    cache->index_mask = ((1 << (cache->index_size + cache->inner_index_size + 2)) - 1);
    cache->tag_mask = ~cache->index_mask;
    cache->index_mask &= ~(cache->inner_index_mask | 0x3);

    //Set up the fetch variables
    cache->fetching = false;
    cache->penalty_count = 0;
    cache->subsequent_fetching = 0;

    //Invalidate all data in the cache
    uint8_t j;
    for(i = 0; i < cache->num_blocks; i++){
        cache->blocks[i].dirty = false;
        for(j = 0; j < cache->block_size; j++){
            cache->blocks[i].valid[j] = false;
        }
    }
    return cache;
}
*/
