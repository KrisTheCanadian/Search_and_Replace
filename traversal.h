//
// Created by viking on 10/10/22.
//

#ifndef COMP348_SEARCH_AND_REPLACE_TRAVERSAL_H
#define COMP348_SEARCH_AND_REPLACE_TRAVERSAL_H

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <malloc.h>

#include "string.h"

typedef struct FileStruct{
  char* path;
  struct FileStruct* next;
} FileStruct_t;

void fileStructPush(FileStruct_t* head, const char* path);

FileStruct_t* getAllFiles(const char* path, FileStruct_t* head);

#endif //COMP348_SEARCH_AND_REPLACE_TRAVERSAL_H
