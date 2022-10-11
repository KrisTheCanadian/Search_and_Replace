//
// Created by viking on 10/10/22.
//

#include <stdlib.h>

#include "text.h"
#include "replace.h"
#include "traversal.h"

#define BUFFER_SIZE 1024
const long MAX_BUFFER_SIZE = 1024 * 1024;

FileStruct_t *parseFiles(FileStruct_t *files, char *target) {
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

    char* line = NULL;
    while ((line = getNextLine(in))){
      char* ret = strstr(line, target);
      if(!ret) {
        fputs(line, out);
      } else {
        replaceLine(line, replacementString, target, (unsigned int) (ret - line), &changes);
        // do the replacements on the line buffer
        fputs(line, out);
      }
      free(line);
    }

    files->changes = changes;
    fclose(in);
    fclose(out);
    rename(tempFile, files->path);
    remove(tempFile);
    free(replacementString);
    free(tempFile);
  }
  return NULL;
}

char* getNextLine(FILE* fileHandle){
  int currentBufferSize = BUFFER_SIZE;
  char* line = (char*)malloc(sizeof(char) * currentBufferSize);
  memset(line, 1, sizeof(char) * currentBufferSize);

  while (1){
    long currentPos = ftell(fileHandle);
    if (fgets(line, currentBufferSize - 1, fileHandle) == NULL){
      if (!feof(fileHandle)){
        puts("Error reading the file");
      }
      return NULL;
    }

    if (line[currentBufferSize - 1] == '\0' && line[currentBufferSize - 2] != '\n'){
      // we need a bigger buffer
      currentBufferSize += BUFFER_SIZE;
      if (currentBufferSize > MAX_BUFFER_SIZE){
        printf("Reached max buffer size...");
        exit(-1);
      }

      line = (char*) realloc((void*)line, sizeof(char) * currentBufferSize);
      memset(line, 1, sizeof(char) * currentBufferSize);

      fseek(fileHandle, currentPos, SEEK_SET);
      continue;
    }

    return line;
  }

}

