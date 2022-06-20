#include "../../bin/hashmap.h"
#include <stdio.h>

int main() {

    Hashmap hashmap = createHashmap(1024);

    char *key  = "A very cool test key";
    char *data = "Testing";

    if (hashmapStore(key,data,&hashmap)) {
        printf("Error with test case 1!\n");
        exit(1);
    }

    if (hashmapStore("Testing","Test two",&hashmap)) {
        printf("Error with test case 2!\n");
        exit(1);
    }

    if (strcmp(hashmapGet(key,&hashmap),data) != 0) {
        printf("Error with test case 3!\n");
        exit(1);
    }

    if (strcmp(hashmapGet("Testing",&hashmap),"Test two") != 0) {
        printf("Error with test case 4!\n");
        exit(1);
    }

    if (hashmapDelete(key,&hashmap)) {
        printf("Error with test case 5!\n");
        exit(1);
    }
    if (hashmapDelete(key,&hashmap) != 1) {
        printf("Error with test case 6!\n");
        exit(1);
    }

    if (reallocHashmap(&hashmap)) {
        printf("Error with test cae 7!\n");
        exit(1);
    }

    destroyHashmap(&hashmap);

    printf("Tests successful!\n");
    return 0;
}
