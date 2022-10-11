//
// Created by viking on 10/10/22.
//

#include <stdlib.h>
#include "report.h"

typedef struct FileStructArray{
  FileStruct_t** fileArray;
  size_t size;
} FileStructArray_t;

size_t countLinkedList(FileStruct_t* head){
  size_t count = 0;
  while(head->next != NULL){
    count++;
    head = head->next;
  }
  return count;
}

FileStructArray_t* createArrayOfPointers(FileStruct_t* head, size_t size){
  FileStruct_t** files = (FileStruct_t **) malloc(sizeof(FileStruct_t *) * size);
  for(int i = 0; i < size; i++){
    files[i] = head;
    head = head->next;
  }
  FileStructArray_t* fileStructArray = malloc(sizeof(FileStructArray_t));
  fileStructArray->fileArray = files;
  fileStructArray->size = size;
  return fileStructArray;
}

int compare_data(const void* _a, const void* _b){
  FileStruct_t **ptrToLeftStruct = (FileStruct_t **) _a;
  FileStruct_t **ptrToRightStruct = (FileStruct_t **) _b;

  if ((*ptrToLeftStruct)->changes < (*ptrToRightStruct)->changes)
    return -1;
  else if ((*ptrToLeftStruct)->changes > (*ptrToRightStruct)->changes)
    return 1;
  else
    return 0;
}

FileStructArray_t* sort(FileStruct_t* node){
  if(node->next == NULL){
    // nothing to sort
    return 0;
  }

  // figure out how many items are in the linked list
  unsigned int count = countLinkedList(node->next);


  // create an array of pointers
  FileStructArray_t* fileStructArray = createArrayOfPointers(node->next, count);
  qsort(fileStructArray->fileArray, count, sizeof(FileStructArray_t*), &compare_data);
  // let qsort do the rest
  return fileStructArray;
}

void report(FileStruct_t* node, char* absolutePath, char* target){
  FileStructArray_t* fileStructArray = sort(node);

  printf("Target string: \t%s\n", target);
  printf("Search begins in current folder: %s\n\n", absolutePath);
  printf("** Search Report **");
  puts("\n");

  if(fileStructArray == NULL){
    puts("No files to report.");
    return;
  }

  if(fileStructArray->size == 0){
    puts("No files to report.");
    return;
  }

  puts("Updates\t\t File Name");

  FileStruct_t** files = fileStructArray->fileArray;
  for(size_t i = fileStructArray->size -1; i > 0; i--){
    if(files[i] && files[i]->changes > 0){
      printf("%d\t\t %s\n", files[i]->changes, files[i]->path + strlen(absolutePath) + 1);
    }
  }
  puts("\n");

  free(fileStructArray);
  free(files);
}