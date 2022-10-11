//
// Created by viking on 10/10/22.
//

#include <stdlib.h>
#include "text.h"
#include "replace.h"

#define BUFFER_SIZE 2048

FileStruct_t *parseFiles(FileStruct_t *files, char *target) {
  char inputBuffer[BUFFER_SIZE];
  char outputBuffer[BUFFER_SIZE];

  while(files->next){
    unsigned int changes = 0;
    char* replacementString = getReplacementString(target);
    files = files->next;

    char* tempFile = NULL;
    char* temp = ".temp";
    tempFile = malloc(strlen(files->path) + strlen(temp) + 1);
    strcpy(tempFile, files->path);
    strcat(tempFile, temp);

    FILE* in = fopen(files->path, "r");
    FILE* out = fopen(tempFile, "w");

    fseek(out, 0, SEEK_SET);


    if(!in || !out){
      printf("Unable to read file: %s "
             "\n Please try running the program with elevated privileges or check the file format.",
             files->path);
      exit(EXIT_FAILURE);
    }



    while(fgets( inputBuffer, BUFFER_SIZE - 1, in ) != NULL){
      char* ret = strstr(inputBuffer, target);
      if(!ret) {
        strcpy(outputBuffer, inputBuffer);
        fputs(outputBuffer, out);
      } else {
        replaceLine(inputBuffer, replacementString, target, (unsigned int) (ret - inputBuffer), &changes);
        // do the replacements on the line buffer
        fputs(inputBuffer, out);
      }

    }
    files->changes = changes;
    fclose(in);
    fclose(out);
    rename(tempFile, files->path);
    remove(tempFile);
    free(replacementString);
    free(tempFile);
  }
}