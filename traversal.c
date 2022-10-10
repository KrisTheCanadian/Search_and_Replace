//
// Created by viking on 10/10/22.
//
#include "traversal.h"


void fileStructPush(FileStruct_t* head, const char* path){
  FileStruct_t * current = head;
  while (current->next != NULL) {
    current = current->next;
  }

  int size = sizeof(FileStruct_t);
  current->next = (FileStruct_t *) malloc(size);
  current->next->path = malloc(strlen(path) + 1);
  strcpy(current->next->path, path);
  current->next->next = NULL;
}

struct FileStruct* getAllFiles(const char* path, FileStruct_t* node){
  DIR* folder;
  struct dirent *entry;
  struct stat filestat;

  folder = opendir(path);

  if(!folder){
    puts("Unable to read directory. Please try running the program with elevated privileges.");
    return 0;
  }

  // d_type == 8 , it's a file
  // d_type == 4, it's a directory
  while((entry= readdir(folder))){
    // append path + name
    char* pathWithName = NULL;
    char* name = NULL;
    char* delimiter = "/";
    name = malloc(strlen(entry->d_name) + 1);
    strcpy(name, entry->d_name);

    pathWithName = malloc(sizeof (path) + strlen(delimiter) + sizeof(entry->d_name));
    strcpy(pathWithName, path);
    strcat(pathWithName, delimiter);
    strcat(pathWithName, name);

    stat(pathWithName, &filestat);
    if(S_ISREG(filestat.st_mode)){
      char* ext = strrchr(entry->d_name, '.');
      if(!ext){ continue; }
      if(strcmp(ext, ".txt") != 0){ continue; }

      fileStructPush(node, pathWithName);


      printf("FILE %s\n", entry->d_name);
    } else if(S_ISDIR(filestat.st_mode)) {
      if(strcmp(entry->d_name, "..") == 0){ continue; }
      if(strcmp(entry->d_name, ".") == 0) { continue; }
      printf("RECURSIVE DIR %s\n", entry->d_name);

      char* newPath = NULL;
      newPath = malloc(strlen(pathWithName) + 1);
      strcpy(newPath, pathWithName);

      getAllFiles(newPath, node);
      free(newPath);
    }
    free(pathWithName);
    free(name);
  }
  closedir(folder);
  return 0;
}