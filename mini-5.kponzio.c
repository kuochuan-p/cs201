#include "mini-5.h"
#include <stdio.h>

int createRecords(unsigned int numRecords, int *ids, char **names, Record **records){
    if(ids == NULL || names == NULL || records == NULL){
        return -1;
    }
    else if (numRecords == 0){
        return 0;
    }

    Record *r;
    for (int i=0; i<numRecords; i++){
        r = malloc(sizeof(Record));
        r->id = ids[i];
        strcpy(r->name, names[i]);
        records[i] =r;
    }
    return 0;
}