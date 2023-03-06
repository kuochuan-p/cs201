#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>


#define BUFLEN 10100
#define LINELEN 256 
#define NUM_THREADS 4
#define MARGIN 10

typedef struct {
char *A; // the digits themselves--this is a pointer to your big buffer
int start; // first position that thread should look at
int end; // last position that this thread should look at
int bestpos; // ending position of the best sequence found by this thread
int max; // length of the best sequence found by this thread
} ThreadInfo;

int readFile(char *filename, int *numChars, char *buffer){
    FILE *fp;
    int idx = 0;
    int len = 0;
    char line[LINELEN];
    
    fp = fopen(filename, "r");
    char *chp;
    chp = fgets(line, LINELEN, fp);
    
    if (chp == NULL) {
        printf("file is empty\n");
        fclose(fp);
        return 8;
    }

    while (chp != NULL) {
        len = strlen(line);
        if (line[len-1] == '\n') {
            line[len-1] = '\0';
            len = len - 1;
        }
        *numChars+=len;
    
        for (int i=0; i<len; ++i) {
            buffer[idx+i] = line[i];
        }
        idx += len;
        chp = fgets(line, LINELEN, fp);
    } // while not at end of file
    fclose(fp);

    return 0;
}

void *findMaxSumSeq(void *param){
    ThreadInfo *data;
    data = (ThreadInfo *) param;

    int front = data->start+1;
    int back;
    int count=0;

    while (front < data->end){
        while(count <= (int) data->A[front] - 48 && back >=0){
            count += (int) data->A[back] -48;
            if(count == (int) data->A[front] - 48 && front-back > data->max){
                data->max = front-back+1;
                data->bestpos = front;
            }
            back--;
        }
        front++;
        back = front-1;
        count=0;
    }

}

int main(int argc, char *argv[]) {
    int rc, numChars;
    char buffer[BUFLEN];
    if (argc < 2) {
        printf("ERROR: need a filename\n");
        return 8;
    }
    
    rc = readFile(argv[1], &numChars, buffer);
    if (rc != 0) {
        return 8;
    }

    // remove point from buffer
    int pastPointFlag = 0;
    for(int i=0;i<BUFLEN;i++){
        if (buffer[i] == '.'){
            pastPointFlag = 1;
            numChars--;
        }else{
            buffer[i-pastPointFlag] = buffer[i];
        }
    
    }
    // here’s where you’ll create the threads that do the actual searching
    ThreadInfo threads[NUM_THREADS];
    pthread_t threadIds[NUM_THREADS];

    int thread_buflen = numChars/NUM_THREADS;

    //assign thread info
    for(int i = 0; i < NUM_THREADS; i++){
        threads[i].A = buffer;
        threads[i].start = thread_buflen*i;
        threads[i].end = threads[i].start + thread_buflen -1;
        if(i != 0){
            threads[i].start -= MARGIN;
        }
        if(i != NUM_THREADS-1){
            threads[i].end += MARGIN;
            
        }else{
            if(threads[i].end< numChars-1){
                threads[i].end += numChars-threads[i].end-1;
            }
        }
        threads[i].bestpos = 0;
        threads[i].max = 1;
    }

    //create threads
    for(int i =0; i<NUM_THREADS; i++){
        pthread_create(&threadIds[i], NULL, findMaxSumSeq, &threads[i]);
    }

    //join threads
    for (int i=0; i<NUM_THREADS; ++i){
        pthread_join(threadIds[i], NULL);
    }

    //find solution
    int max = 0;
    ThreadInfo sol;
    for(int i =0; i<NUM_THREADS; i++){
        if(threads[i].max > max){
            max = threads[i].max;
            sol = threads[i];
        }
    }

    //output
    printf("Longest sequence:\n");
    for(int i = sol.bestpos - sol.max + 1; i <= sol.bestpos; i++){
        printf("%c", buffer[i]);
    }
    printf("\n");
    printf("Located at index %d\n", sol.bestpos);

    
    return 0;
}