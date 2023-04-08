
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define SHBUFLEN 10
#define BUFLEN 32
#define PROMPT "> "

typedef struct {
    char buf[SHBUFLEN]; // the buffer
    int in; // location to which producer will write
    int out; // location from which consumer will read
    int counter; // total # items in the buffer
    int numWritten; // # items that producer has written
    int numRead; // # items that consumer has read
    int done; // whether we’re done
    pthread_mutex_t lock; // the lock
} ThreadInfo;

void *producer(void *param){
    ThreadInfo *tInfo = (ThreadInfo *) param;
    int done, len;
    char *chp;
    char buffer[BUFLEN];


    done = 0;
    while ( ! done ) {
        printf("%s", PROMPT);
        chp = fgets(buffer, BUFLEN, stdin);
        if (chp != NULL) {
            len = strlen(buffer);
            if (buffer[len-1] == '\n') {
                buffer[len-1] = '\0';
                len = len - 1;
            }

            if ( ! strcmp(buffer, "quit") || ! strcmp(buffer, "exit") ){
                done = 1;
                pthread_mutex_lock(&tInfo->lock);
                tInfo->done = 1;
                pthread_mutex_unlock(&tInfo->lock);

            }else{
                for (int i = 0; i<len; i++){
                    
                    int sts = 0; // This is polling but as an undergrad I wasn't sure if I was supposed to use condition variables or not
                    while (!sts){
                        pthread_mutex_lock(&tInfo->lock);
                        if (tInfo->counter < SHBUFLEN) {
                            tInfo->buf[tInfo->in] = buffer[i];
                            tInfo->in = (tInfo->in + 1) % SHBUFLEN;
                            tInfo->counter = tInfo->counter + 1;
                            sts = 1;
                            tInfo->numWritten++;
                            printf("producer writes '%c'\n", buffer[i]);
                        }
                        pthread_mutex_unlock(&tInfo->lock);
                    }
                    

                }   
            }
        }
    }
    printf("producer is exiting\n");

}

void *consumer(void *param){
    ThreadInfo *tInfo = (ThreadInfo *) param;

    int done = 0;
    int sDone = 0;
    int sts = 0;
    char c;

    while (!done){
        pthread_mutex_lock(&tInfo->lock);
        sDone = tInfo->done;
        pthread_mutex_unlock(&tInfo->lock);

        sts = 0;

        if(sDone){
            done = 1;
        }else{
            
            while(!sts && !sDone){
                pthread_mutex_lock(&tInfo->lock);
                if (tInfo->counter > 0) {
                    c = tInfo->buf[tInfo->out];
                    tInfo->out = (tInfo->out + 1)  % SHBUFLEN;
                    tInfo->counter = tInfo->counter - 1;
                    sts = 1;
                    tInfo->numRead++;
                    printf("consumer read '%c'\n", c);

                }
                sDone = tInfo->done;
                pthread_mutex_unlock(&tInfo->lock);
            }
            


        }
    }
    printf("consumer is exiting\n");

}

int main(){
    
    pthread_t producer_t;
    pthread_t consumer_t;
    
    ThreadInfo tInfo;
    tInfo.in = 0;
    tInfo.out = 0;
    tInfo.counter = 0;
    tInfo.numWritten = 0;
    tInfo.numRead = 0;
    tInfo.done = 0;
    pthread_mutex_init(&tInfo.lock, NULL);


    pthread_create(&producer_t, NULL, producer, &tInfo);
    pthread_create(&consumer_t, NULL, consumer, &tInfo);

    pthread_join(producer_t, NULL);
    pthread_join(consumer_t, NULL);

    printf("num written = %d\n", tInfo.numWritten);
    printf("num read = %d\n", tInfo.numRead);

    
    return 0;
}