#ifndef R4221_HASHMAP
#define R4221_HASHMAP 4221

#include <stdlib.h>
#include <string.h>

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

/* data types */
typedef struct {
    char *Key;
    void *Data;
} HashItem;

typedef struct {
    size_t Size;
    HashItem *Items;
} Hashmap;

/* semi internal functions */
size_t    HashmapHashData(char *key, size_t size);
size_t    DoubleHashData(size_t data, size_t size);
HashItem *GetHashmapItem(char *key, Hashmap *hashmap);

/* external functions */
Hashmap   createHashmap(size_t size);
void      destroyHashmap(Hashmap *hashmap);
int       reallocHashmap(Hashmap *hashmap);

int       hashmapStore(char *key, void *data, Hashmap *hashmap);
void     *hashmapGet(char *key, Hashmap *hashmap);
int       hashmapDelete(char *key, Hashmap *hashmap);

#endif
