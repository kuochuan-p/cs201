#define MAXNAMELEN 127
#define BUFFLEN 256
#define TMPBUFFLEN 128
#define NULL 0

typedef struct StudentRecordStruct {
char name[1+MAXNAMELEN];
int id;
struct StudentRecordStruct *next;
} StudentRecord;

int insertEntry(StudentRecord **list, char *name, int id);
int deleteEntry(StudentRecord **list, int id);
int modifyEntry(StudentRecord *list, char *name, int id);
int findEntry(StudentRecord *list, char *name, int id);
int printList(StudentRecord *list);