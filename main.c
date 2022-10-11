#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "traversal.h"
#include "text.h"
#include "report.h"


typedef struct FileStruct FileStruct;

int main(int argc, char *argv[]) {
  if(argc != 2){
    puts("Usage: a.out <string>");
    return 0;
  }
  if(strcmp(argv[1], "") == 0) {
    puts("Usage: a.out <string>");
    return 0;
  }
  // traverse through and find all files to parse
  char* absolutePath = realpath(".", 0);

  // create a linked list
  FileStruct_t* head = (FileStruct_t *) malloc(sizeof(FileStruct_t));
  head->path = "Head";
  head->next = NULL;

  // create a node pointing to head
  FileStruct_t* node = head;
  getAllFiles(absolutePath, node);



  // look in all the files ending with a .txt
  // replace all files string to upper
  parseFiles(node, argv[1]);

  // report changes
  report(node, absolutePath, argv[1]);

  free(absolutePath);
  free(head);
  return 0;
}
