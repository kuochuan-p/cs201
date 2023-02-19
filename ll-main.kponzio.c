#include "ll-functions.kponzio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    char filename[TMPBUFFLEN];
    strcpy(filename, "");
    if(argc > 2){
        printf("ERROR: Too many command line arguments\n");
        return 8;
    }
    else if(argc < 2){
        while(strcmp(filename, "")==0){
            printf("enter a filename to read from: ");
            fscanf(stdin,"%s",filename);
        }
    }
    else{
        strcpy(filename, argv[1]);
    }

    FILE *infile;
    infile = fopen(filename, "r");
    if(infile == NULL){
        printf("Cannot open file '%s'\n", filename);
        return 8;
    }

    struct StudentRecordStruct *studentList = NULL;
    char buffer[BUFFLEN];
    char code[TMPBUFFLEN];
    char name[TMPBUFFLEN];
    int id;
    char *chp;
    int nf;
    int linenum = 0;

    chp = fgets(buffer, BUFFLEN, infile);

    while (chp != NULL)
    {
        linenum++;
        nf = sscanf(buffer, "%[A-Za-z.'’ -],%[A-Za-z.'’ -],%d,", code, name, &id);
        if (nf == 3) {
            if (strcmp("A",code) == 0) {
                if (insertEntry(&studentList, name, id)==0) {
                    printf("inserted | %s | %d\n", name, id);
                } else {
                    printf("error: cannot insert '%s' %d; id already present in list\nerror inserting |%s| %d\n",name,id,name,id);
                }
            }else if(strcmp("M",code) == 0) {
                if (modifyEntry(studentList, name, id)==0) {
                    printf("modified %d\n", id );
                } else {
                    printf("error in modify(): id %d not found in list\nerror modifying %d\n",id,id);
                }
            } else if(strcmp("D",code) == 0) {
                if (deleteEntry(&studentList,id)==0) {
                    printf("deleted %d\n", id);
                } else {
                    printf("error in delete(): id %d not found in list\nerror deleting %d\n",id,id);
                }
            } else {
                printf("Invalid Action Code");
            }
        } else {
            printf("line %d error: not enough values; or incorrect format\n", linenum);
        }
        chp = fgets(buffer, BUFFLEN, infile);
    }
    

    fclose(infile);
}