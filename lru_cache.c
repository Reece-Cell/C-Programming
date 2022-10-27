#include <stdlib.h>
#include "lru_cache.h"

//
// Your implementations of cache_new, cache_lookup, cache_insert,
// and cache_clear go in this file.  You must use a least-recently-used
// cache replacement policy.
//

// return a new cache object
CACHE *cache_new(int size) {
  CACHE *cache = malloc(sizeof(CACHE));
  cache->size = size;
  cache->addr = malloc(size * sizeof(int));
  cache->data = malloc(size * sizeof(float));

  // initialize cache
  int i;
  for (i = 0; i < cache->size; i++) {
    cache->addr[i] = -1;
    cache->data[i] = 0.0;
  }

  return cache;
}

// is the cache contains an element with key value i, return its value,
// else return -1
float cache_lookup(CACHE *cache, int i) {
// your code here
int j;
int x;
float st;
for (j = 0; j < cache->size; j++) {
     if (cache->addr[j] == i) {
         st = cache->data[j];
         // yes, cache hit
         for(x = j;x > 0;x--){
             cache->data[x] = cache->data[x-1];
             cache->addr[x] = cache->addr[x-1];
    }
    cache->addr[0] = i;
    cache->data[0] = st;
    return st;
     }
}
// cache miss
return -1.0;
}

// record in the cache that the data element with key i has value x
// LRU replacement policy is used
void cache_insert(CACHE *cache, int i, float b) {
// your code here
int j;
int x;
for(j = 0;j<cache->size;j++){
   if(cache->addr[j] == -1){
       for(x = j;x > 0;x--){
           cache->addr[x] = cache->addr[x-1];
           cache->data[x] = cache->data[x-1];
           
       }
       cache->addr[0] = i;
       cache->data[0] = b;
       return;
   }
}
for(j = cache->size-1;j > 0;j--){
    cache->addr[j] = cache->addr[j-1];
    cache->data[j] = cache->data[j-1];
    
}
cache->addr[0] = i;
cache->data[0] = b;
}

// remove cache element having key value i, if such an element exists
void cache_clear(CACHE *cache, int i) {
int j;
int x;
for (j = 0; j < cache->size; j++) {
     if (cache->addr[j] == i) {
         int st = cache->size-1;
         for(x = j;x<st;x++){
             if(cache->addr[x+1] == -1){
                 break;
   }
        cache->addr[x] = cache->addr[x+1];
        cache->data[x] = cache->data[x+1];
  }
  cache->addr[x] = -1;
        break;
     }
}
}
