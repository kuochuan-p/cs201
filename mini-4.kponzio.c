#define MAXNAMELEN 31

typedef struct {
char name[1+MAXNAMELEN];
int id;
} Record;

int searchFor(int id, int numRecords, Record *records){
    Record r;
    for (int i = 0; i<numRecords; i++){
        r = records[i];
        if (r.id == id){
            return i;
        }
    }
    return -1;
}