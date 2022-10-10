#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "traversal.h"


int main(int argc, char *argv[]) {
  if(argc != 1){
    puts("Usage: a.out <string>");
    return 0;
  }
  if(strcmp(argv[0], "") == 0) {
    puts("Usage: a.out <string>");
    return 0;
  }
  // traverse through and find all files to parse
  char* absolutePath = realpath(".", 0);
  getAllFiles(absolutePath);
  free(absolutePath);
  // look in all the files ending with a .txt

  // replace all files string to upper

  // report changes

  return 0;
}
