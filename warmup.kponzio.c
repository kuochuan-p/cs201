#include "string.h"
#include "warmup.kponzio.h"
#include <stdio.h>
#include <stdlib.h>

Song *createSong(char *title, char *artist, unsigned int year){
    if(strlen(title)>0 && strlen(title)<=MAXNAMELEN && strlen(artist)>0 && strlen(artist)<=MAXNAMELEN){
        Song *newSong = malloc(sizeof(Song));
        strcpy(newSong->title, title);
        strcpy(newSong->artist, artist);
        newSong->year = year;
        return newSong;
    }
    else{
        return NULL;
    }
}
int compareSongs(Song *songOne, Song *songTwo){
    int result;
    result = strcmp(songOne->title, songTwo->title);
    if(result == 0){
        result = strcmp(songOne->artist, songTwo->artist);
        if (result == 0){
            result = songOne->year - songTwo->year;
        }
    }
    if(result != 0){
        result = result/abs(result);
    }
    return result;
}
