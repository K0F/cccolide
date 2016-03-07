#include <stdio.h>
#include <pathsetup.h>

#define BUFSIZE 128

#if WIN32
#define popen _popen
#define pclose _pclose
#endif

int main(int *argc,char *argv[]) {
	char *cmd = getSclangExePath(); 
          //"C:/Supercollider/Supercollider_findModules/Install/SuperCollider/sclang";

  char buf[BUFSIZE];
  FILE *fp;

  if ((fp = popen(cmd, "r")) == NULL) {
    printf("Error opening pipe!\n");
    return -1;
  }

  while (fgets(buf, BUFSIZE, fp) != NULL) {
    // Do whatever you want here...
    printf("OUTPUT: %s", buf);
  }

  if(pclose(fp))  {
    printf("Command not found or exited with error status\n");
    return -1;
  }

  return 0;
}
