#include <stdio.h>

int NUM_PAGES = 256;
int PAGE_SIZE = 256;
int NUM_FRAMES = 128;

int decodeAddress(int address, int *pageNumber, int *pageOffset){
    if (address > NUM_PAGES*PAGE_SIZE-1 || address < 0){
        return 1;
    }

    *pageNumber = address/PAGE_SIZE;
    *pageOffset = address%PAGE_SIZE;

    return 0;
}

int readFromBackingStore(FILE *fp, char *buffer, int pageNumber){
    
    fseek(fp, pageNumber*PAGE_SIZE*sizeof(unsigned char), SEEK_SET);
    
    fread(buffer, PAGE_SIZE*sizeof(char),1, fp);
}
