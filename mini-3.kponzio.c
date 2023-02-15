#include <stdio.h>

int convertString(char *inString, char **outString){
    if(inString == NULL || outString == NULL){
        return -1;
    }
    int length = strlen(inString);
    char *out = malloc(1+length*sizeof(char));
    char curr;
    char low;
    for(int i = 0; i < length; i++){
        curr = inString[i];
        low = tolower(curr);
        out[i] = low;
    }
    *outString = out;
    return length;
}
