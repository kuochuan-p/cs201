// jdh CS201 Spring 2023

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "warmup.kponzio.h"

int createAndCheck(char *testname, char *title, char *artist, int year, int expectFail, Song **songReturn) {
  Song *song;
  int rc = 0;

  song = createSong(title, artist, year);
  if ( expectFail ) {
    if (song != NULL) {
      printf("error: test %s fails; expected NULL return value\n", testname);
      rc = 1;
    }
  } else {
    *songReturn = song;
    if ( strcmp(song->title, title) ) {
      printf("error: test %s fails; title is not correct\n", testname);
      rc = 1;
    }
    if ( strcmp(song->artist, artist) ) {
      printf("error: test %s fails; artist is not correct\n", testname);
      rc = 1;
    }
    if (song->year != year) {
      printf("error: test %s fails; year is not correct\n", testname);
      rc = 1;
    }
  }

  if (rc == 0)
    printf("pass test %s\n", testname);

  return rc;
} // createAndCheck()

//------------------------------------------------------

int compareCheck(char *testname, Song *song1, Song *song2, int expected) {
  int res, fail;

  fail = 0;
  res = compareSongs(song1, song2);
  if (expected == 0) {
    if (res != 0) {
      printf("error: test %s fails; expected zero from comparison; got %d\n", testname, res);
      fail = 1;
    }
  } else if (expected > 0) {
    if (res != 1) {
      printf("error: test %s fails; expected return value = 1 from comparison; got %d\n", testname, res);
      fail = 1;
    }
  } else {
    if (res != -1) {
      printf("error: test %s fails; expected negative return value = -1 from comparison; got %d\n", testname, res);
      fail = 1;
    }
  }

  if (fail == 0)
    printf("pass test %s\n", testname);

  return fail;
} // compareCheck()

//------------------------------------------------------

int main() {
  Song *song1, *song2, *song3, *song4, *song5;
  int numfails = 0;
  int rc;

  song1 = NULL;
  song2 = NULL;
  song3 = NULL;
  song4 = NULL;
  song5 = NULL;

  // this should fail
  rc = createAndCheck("T1", NULL, "Radiohead", 2007, 1, NULL);
  if (rc)
    numfails = numfails + 1;

  // this should fail
  rc = createAndCheck("T2", "Ceremony", NULL, 2007, 1, NULL);
  if (rc)
    numfails = numfails + 1;

  // this should fail
  rc = createAndCheck("T3", "", "New Order", 1981, 1, NULL);
  if (rc)
    numfails = numfails + 1;

  // this should fail
  rc = createAndCheck("T4", "Ceremony", "", 1981, 1, NULL);
  if (rc)
    numfails = numfails + 1;

  // this should pass
  rc = createAndCheck("T5", "Ceremony", "New Order", 1981, 0, &song1);
  if (rc)
    numfails = numfails + 1;

  // this should pass
  rc = createAndCheck("T6", "Ceremony", "Radiohead", 2007, 0, &song2);
  if (rc)
    numfails = numfails + 1;

  // this should pass
  rc = createAndCheck("T7", "Just", "Radiohead", 1995, 0, &song3);
  if (rc)
    numfails = numfails + 1;

  // this should pass
  rc = createAndCheck("T8", "Fearless", "Taylor Swift", 2021, 0, &song4);
  if (rc)
    numfails = numfails + 1;

  // this should pass
  rc = createAndCheck("T9", "Fearless", "Taylor Swift", 2008, 0, &song5);
  if (rc)
    numfails = numfails + 1;

  if (song1 != NULL && song2 != NULL && song3 != NULL && song4 != NULL && song5 != NULL) {
    rc = compareCheck("T10", song1, song2, -1);
    if (rc)
      numfails = numfails + 1;

    rc = compareCheck("T11", song3, song2, 1);
    if (rc)
      numfails = numfails + 1;

    rc = compareCheck("T12", song3, song3, 0);
    if (rc)
      numfails = numfails + 1;

    rc = compareCheck("T13", song5, song4, -1);
    if (rc)
      numfails = numfails + 1;
  } else {
    printf("was not able to run some tests\n");
  }

  if (numfails == 0) {
    printf("all tests pass\n");
    return 0;
  } else {
    printf("%d test(s) failed\n", numfails);
    return 8;
  }

}
