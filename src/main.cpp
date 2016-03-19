#include <iostream>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 128

#if WIN32
#define popen _popen
#define pclose _pclose
#endif

using namespace std;

int main(int *argc, char *argv[]) {
  string cmd = "sclang";
  string arguments = string(" -r -s start.scd");
  cmd += arguments;

  char buf[BUFSIZE];
  FILE *fp;

  if ((fp = popen(cmd.c_str(), "r")) == NULL) {
    printf("Error opening pipe!\n");
    return -1;
  }

  while (fgets(buf, BUFSIZE, fp) != NULL) {
    // Do whatever you want here...
    printf("OUTPUT: %s", buf);
  }

  if (pclose(fp)) {
    printf("Command not found or exited with error status\n");
    return -1;
  }

  return 0;
}
