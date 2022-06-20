#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

/* This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

/* function for creating hashmaps */
Hashmap createHashmap(size_t size) {
    Hashmap hashmap;
    hashmap.Size = size;
    hashmap.Items = (HashItem*)calloc(size, sizeof(HashItem*));
    return hashmap;
}

/* function for destroying hashmaps */
void destroyHashmap(Hashmap *hashmap) {
    free(hashmap->Items);
}

int reallocHashmap(Hashmap *hashmap) {
    hashmap->Size *= 2;
    hashmap->Items = realloc(hashmap->Items, hashmap->Size);
    if (hashmap->Items) {
        return 0;
    }
    return 1;
}

/* function for hashing key */
size_t HashmapHashData(char *key, size_t size) {
    size_t hash = 0;
    size_t keyLen = strlen(key);

    for (size_t i = 0;i < keyLen;i++) {
        hash += (i+1) * key[i];
    }
    hash %= size;

    return hash;
}

size_t DoubleHashData(size_t data, size_t size) {
    size_t hash = 0;
    hash += data * 4221;
    hash += hash * data;
    hash %= size;
    return hash;
}

/* function for getting item from hashmap */
HashItem *GetHashmapItem(char *key, Hashmap *hashmap) {
    size_t hash = HashmapHashData(key,hashmap->Size);

    char *destinationKey = hashmap->Items[hash].Key;
    if (destinationKey) {
        if (strcmp(key,destinationKey) == 0) {
            return &hashmap->Items[hash];
        } else {
            hash = DoubleHashData(hash,hashmap->Size);
            destinationKey = hashmap->Items[hash].Key;
            if (destinationKey) {
                if (strcmp(key,destinationKey) == 0) {
                    return &hashmap->Items[hash];
                } else {
                    size_t oldHash = hash;
                    while (1) {
                        hash = hash + 1;
                        destinationKey = hashmap->Items[hash].Key;
                        if (destinationKey) {
                            if (strcmp(key,destinationKey) == 0) {
                                return &hashmap->Items[hash];
                            }
                        } else {
                            return &hashmap->Items[hash];
                        }
                        if (hash == oldHash)
                            return NULL;
                    }
                }
            } else {
                return &hashmap->Items[hash];
            }
        }
    } else {
        return &hashmap->Items[hash];
    }
    return NULL;
}

/* return 0 on store success return 1 on store failure */
int hashmapStore(char *key, void *data, Hashmap *hashmap) {
    HashItem *item = GetHashmapItem(key,hashmap);
    if (item) {
        item->Data = data;
        item->Key  = key;
        return 0;
    }
    return 1;
}

/* return pointer to data on success return pointer to null on failure */
void *hashmapGet(char *key, Hashmap *hashmap) {
    HashItem *item = GetHashmapItem(key,hashmap);
    if (item) {
        return item->Data;
    }
    return NULL;
}

/* return 0 if key was found and deleted return 1 if key was not found */
int hashmapDelete(char *key, Hashmap *hashmap) {
    HashItem *item = GetHashmapItem(key,hashmap);
    if (item) {
        if (item->Key) {
            item->Data = NULL;
            item->Key  = NULL;
            return 0;
        }
    }
    return 1;
}
