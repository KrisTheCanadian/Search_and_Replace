//
// Created by viking on 10/10/22.
//

#include <string.h>
#include <ctype.h>
#include "replace.h"

#include <stdio.h>
#include <stdlib.h>

#include "traversal.h"
#include "text.h"
#include "report.h"


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


char* getReplacementString(const char* target){
  if(!target){ return 0; }

  char* upperTarget = malloc(strlen(target));
  strcpy(upperTarget, target);

  for(int i = 0; upperTarget[i] != '\0'; i++){
    upperTarget[i] = toupper(target[i]);
  }

  return upperTarget;
}

void replaceLine(char* out_buffer, const char* replacementString, const char* target,
                 unsigned int firstOccurrence, unsigned int* changes){
  for(int i = 0; replacementString[i] != '\0' ; i++){
    out_buffer[firstOccurrence + i] = replacementString[i];
  }
  (*changes)++;
  // check if other replacement is needed
  char* ret = strstr(out_buffer, target);
  if(!ret){ return; }
  replaceLine(out_buffer, replacementString, target, ret - out_buffer , changes);
}