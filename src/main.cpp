#include "cprocessing.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 128

#if WIN32
#define popen _popen
#define pclose _pclose
#endif

using namespace std;
using namespace cprocessing;

FILE *fp;
char buf[BUFSIZE];

int start() {

  string cmd = "sclang";
  string arguments = string(" -r -s");
  cmd += arguments;

  if ((fp = popen(cmd.c_str(), "r")) == NULL) {
    printf("Error opening pipe!\n");
    return -1;
  }

  /*
    while (fgets(buf, BUFSIZE, fp) != NULL) {
      // Do whatever you want here...
      printf("OUTPUT: %s", buf);
    }

    if (pclose(fp)) {
      printf("Command not found or exited with error status\n");
      return -1;
    }
  */
  return 0;
}

void setup() {
  size(320, 240);
  start();
}

void draw() {
  background(255);

  if (fgets(buf, BUFSIZE, fp) != NULL) {
    // Do whatever you want here...
    printf("OUTPUT: %s", buf);
  }
}
