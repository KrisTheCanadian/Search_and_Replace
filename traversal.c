//
// Created by viking on 10/10/22.
//
#include "traversal.h"

int getAllFiles(const char* path){
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
    char* pathWithName;
    char* name;
    char* delimiter = "/";
    name = (char *) malloc(strlen(entry->d_name) + 1);
    strcpy(name, entry->d_name);
    pathWithName = malloc(strlen(path) + strlen(delimiter) + strlen(entry->d_name) + 1);
    strcpy(pathWithName, path);
    strcat(pathWithName, delimiter);
    strcat(pathWithName, name);

    stat(pathWithName, &filestat);
    if(S_ISREG(filestat.st_mode)){
      printf("FILE %s\n", entry->d_name);
    } else if(S_ISDIR(filestat.st_mode)) {
      if(strcmp(entry->d_name, "..") == 0){ continue; }
      if(strcmp(entry->d_name, ".") == 0) { continue; }
      printf("RECURSIVE DIR %s\n", entry->d_name);
      // TODO : RECURSE FOLDER
      char* newPath = (char *) malloc(strlen(pathWithName) + 1);
      strcpy(newPath, pathWithName);
      getAllFiles(newPath);
      free(newPath);
    } else {
      printf("Unknown File:  %s", path);
    }
    free(pathWithName);
    free(name);
  }
  closedir(folder);
  return 0;
}