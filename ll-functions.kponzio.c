#include "ll-functions.kponzio.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int insertEntry(StudentRecord **list, char *name, int id){
    if(name == NULL || id < 0){
        return 8;
    }
    StudentRecord *curr = *list;
    StudentRecord *prev = NULL;
    StudentRecord *newRecord = malloc(sizeof(StudentRecord));
    strcpy(newRecord->name, name);
    newRecord->id = id;
    newRecord->next = NULL;
    if (curr == NULL) {
        // list is empty: the list becomes the new record
        *list = newRecord; // set the list to be the new node
    } else {
        // list is not empty: find where new record should go
        while(curr != NULL && id > curr->id){
            prev = curr;
            curr = curr->next;
        }
        if (curr != NULL && curr->id == id){
            return 8;
        }
        if(prev != NULL){
            prev->next = newRecord;
        }
        else{
            *list = newRecord;
        }
        newRecord->next = curr;
    }
    return 0;
}

int deleteEntry(StudentRecord **list, int id){
    StudentRecord *curr = *list;
    StudentRecord *prev = NULL;
    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        // id was not found: return 8
        return 8;
    } else {
        if (prev != NULL){
            prev->next = curr->next;
        }
        else{
            *list = curr->next; // prev is NULL, meaning that curr is the first node in the list
        }
        free(curr);
        return 0;        
    }
}

int modifyEntry(StudentRecord *list, char *name, int id){
    StudentRecord *curr = list;
    StudentRecord *prev = NULL;
    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        // id was not found: return 8
        return 8;
    }
    else{
        strcpy(curr->name, name);
        return 0;
    }
}

int findEntry(StudentRecord *list, char *name, int id){
    StudentRecord *curr = list;
    StudentRecord *prev = NULL;
    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        // id was not found: return 8
        return 8;
    }
    else{
        strcpy(name, curr->name);
        return 0;
    }
}

int printList(StudentRecord *list){
    if (list == NULL){
        printf("(List is empty)");
        return 0;
    }
    else{
        StudentRecord *curr = list;
        while (curr != NULL) {
            printf("|%s|%d\n", curr->name, curr->id);
            curr = curr->next;
        }
        return 0;
    }
}
