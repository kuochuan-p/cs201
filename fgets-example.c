#include <stdio.h>
#include <string.h>

#define BUFLEN 32
#define PROMPT "> "

int main() {
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
      printf("|%s|\n", buffer);
      if ( ! strcmp(buffer, "quit") || ! strcmp(buffer, "exit") )
        done = 1;
    }
  }

  return 0;
}
