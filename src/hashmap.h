#ifndef R4221_HASHMAP
#define R4221_HASHMAP 4221

#include <stdlib.h>
#include <string.h>


/* data types */
typedef struct {
    char *Key;
    char *Data;
} HashItem;

typedef struct {
    size_t Size;
    HashItem *Items;
} Hashmap;

/* semi internal functions */
size_t    HashmapHashData(char *key, size_t size);
HashItem *GetHashmapItem(char *key, Hashmap *hashmap);

/* external functions */
Hashmap   createHashmap(size_t size);
void      destroyHashmap(Hashmap *hashmap);
int       reallocHashmap(Hashmap *hashmap);

int       hashmapStore(char *key, void *data, Hashmap *hashmap);
void     *hashmapGet(char *key, Hashmap *hashmap);
int       hashmapDelete(char *key, Hashmap *hashmap);

#endif
