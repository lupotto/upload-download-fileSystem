#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	char name[11];
   	char ts[20];
}FileInfo;

typedef struct node {
   	FileInfo e;
    struct node * next;
}node_t;


node_t* LIST_create(FileInfo e);

void LIST_destroy(node_t * head);

void LIST_push(node_t * head, FileInfo e);

FileInfo LIST_pop(node_t ** head);

FileInfo LIST_removeByIndex(node_t ** head, int n);

int LIST_getIndexByValue(node_t * head, FileInfo e);

FileInfo LIST_getValueByIndex(node_t * head, int index);

void LIST_print(node_t * head);





