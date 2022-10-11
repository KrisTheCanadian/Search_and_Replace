//
// Created by viking on 10/10/22.
//

#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include "replace.h"

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