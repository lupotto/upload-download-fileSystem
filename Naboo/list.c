#include "list.h"

node_t* LIST_create(FileInfo e){
	node_t * head = NULL;
	head = malloc(sizeof(node_t));
	if (head == NULL) {
	    return head;
	}

	
	head->e = e;
	head->next = NULL;

	return head;
}

void LIST_destroy(node_t * head){
    node_t * current = head;
    node_t * next = head;

    while (current->next != NULL) {
        next = current->next;
        free (current);
        current = next;
    }
    free (current);

}

void LIST_push(node_t * head, FileInfo e) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = malloc(sizeof(node_t));

    current->next->e = e;
    current->next->next = NULL;
}

FileInfo LIST_pop(node_t ** head) {
    FileInfo retval;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return retval;
    }

    next_node = (*head)->next;
    retval = (*head)->e;
    free(*head);
    *head = next_node;

    return retval;
}

FileInfo LIST_removeByIndex(node_t ** head, int n) {
    int i = 0;
    FileInfo retval;
    node_t * current = *head;
    node_t * temp_node = NULL;

    if (n == 0) {
        return LIST_pop(head);
    }

    for (i = 0; i < n-1; i++) {
        if (current->next == NULL) {
            return retval;
        }
        current = current->next;
    }

    temp_node = current->next;
    retval = temp_node->e;
    current->next = temp_node->next;
    free(temp_node);

    return retval;
}

int LIST_getIndexByValue(node_t * head, FileInfo e){
	int index = 0;
    node_t * current = head;


	while (strcmp(current->e.name, e.name)!=0){
		if (current->next == NULL) {
            return -1;
        }
        current = current->next;
		index++;
	}

	return index;
}

FileInfo LIST_getValueByIndex(node_t * head, int index){
	FileInfo e;
    node_t * current = head;
    int i = 0;

	for (i = 0; i < index; i++) {
        if (current->next == NULL) {
            return e;
        }
        current = current->next;
    }

	return current->e;
}

void LIST_print(node_t * head){
    node_t * current = head;


	while (current->next != NULL){
		printf("%s\n", current->e.name);
		printf("%s\n", current->e.ts);


        current = current->next;
	}

	printf("%s\n", current->e.name);
	printf("%s\n", current->e.ts);

}

/*void main (){
	FileInfo e;
	node_t * list = NULL;

	strcpy(e.name, "foto.png");
	strcpy(e.ts, "1467479515");
	list = LIST_create(e);
	strcpy(e.name, "img.jpeg");
	strcpy(e.ts, "1467479847");
	LIST_push(list, e);
	strcpy(e.name, "gods");
	strcpy(e.ts, "1467479234");
	LIST_push(list, e);
	LIST_print(list);

    printf ("\n**********************\n");
    printf ("\n**********************\n\n");

    strcpy(e.name, "img.jpeg");
    strcpy(e.ts, "1467479847");

    int index = LIST_getIndexByValue(list, e);
    //printf("Index: %d\n", index);

    LIST_removeByIndex(&list, index);
    LIST_print(list);


    LIST_destroy(list);





}*/