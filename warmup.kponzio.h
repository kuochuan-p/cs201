#define MAXNAMELEN 63

typedef struct {
    char title[1+MAXNAMELEN];
    char artist[1+MAXNAMELEN];
    unsigned int year;
} Song;

Song *createSong(char *title, char *artist, unsigned int year);
int compareSongs(Song *songOne, Song *songTwo);
