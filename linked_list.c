
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "linked_list.h"

linked_list *create_linked_list() {
    linked_list *list =  malloc(sizeof(linked_list));
    /* What if malloc returned NULL? */
    if (!list) return NULL; //if queue was not malloc-ed
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}


void free_list(linked_list *list) {
    if (!list) return;
    /* Free the list elements */
    while(list->head) {
        Node *saved = NULL;
        if (list->head->next) {
            saved = list->head->next;
        }
        free(list->head);
        list->head = saved;
    }
    /* Free queue structure */
    free(list);
}

bool linked_list_add(linked_list *list, char *v) {
    
    if (!list) return false; //If queue is null, return false
    Node *newh = malloc(sizeof(Node));
    if (!newh) return false; //if node was not malloc-ed
     
    newh->value = (char *)malloc(strlen(v) * sizeof(char));
    strcpy(newh->value, v);
    newh->next = list->head; //set new elements next to point to the head
    newh->prev = NULL;
    
    if (list->head) {
        list->head->prev = newh; //set the head's previous node to point to new head.
    }

    list->head = newh;

    if (!list->tail) {
        list->tail = newh;
    }
    list->size += 1;
    return true;

}

bool linked_list_add_tail(linked_list *list, char *v) {
    if (!list) return false;
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    Node *newh = malloc(sizeof(Node));
    if (!newh) return false;

    newh->value = (char *)malloc(strlen(v) * sizeof(char));
    strcpy(newh->value, v);
    newh->prev = list->tail;
    newh->next = NULL;

    if (list->tail) {
        list->tail->next = newh; //Set the old tail to point to new tail
    }
    
    list->tail = newh; //set the queue tail to the new tail.

    // If queue head is not yet defined
    if (!list->head) {
        list->head = newh; //set the head to be the same as the tail.
    }
    list->size += 1;
    return true;

}

bool linked_list_delete(linked_list *list, Node *node) {
    if (!list) return false;
    if (!node) return false;
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    free(node);
    list->size -= 1;
    return true;
}

Node *linked_list_search(linked_list *list, char *v) {
    Node *n = list->head;
    for (int i = 0; i < list->size; i++) {
        if (strcmp(n->value, v) == 0) return n;
        n = n->next;
    }
    return NULL;
}

Node *linked_list_get(linked_list *list, int index) {
    int mid = list->size/2;
    Node *n;
    if (index <= mid) { //if the item your wanting is in the first half, go from the head.
        n = list->head;
        for (int i=0; i < index; i++) {
            n = n->next;
        }
    } else {// if the item is in the second half, go from the tail.
        n = list->tail;
        for(int i = list->size-1; i > index; i--) {
            n = n->prev;
        }
    }
    return n;
}

void linked_list_print(linked_list *list) {
    Node *n = list->head;
    printf("printing linked list:\n");
    for(int i=0; i< list->size; i++){
        printf("\t index %i: %s\n", i, n->value);
        n = n->next;
    }
}

void linked_list_sort(linked_list *list) {
    char *temp = (char *)malloc(50 * sizeof(char));
    Node *ni;
    Node *nj;
    char *str1 = (char *)malloc(50 * sizeof(char));
    char *str2 = (char *)malloc(50 * sizeof(char));
    int i;
    int j;
    for(i=0; i<=list->size; i++) {
        ni = linked_list_get(list, i);
        for(j=i+1; j<=list->size; j++){
            nj = linked_list_get(list, j);
            sprintf(str1, "%s", ni->value);
            sprintf(str2, "%s", nj->value);
            for(int i = 0; str1[i]; i++){
                str1[i] = tolower(str1[i]);
            }
            for(int i = 0; str2[i]; i++){
                str2[i] = tolower(str2[i]);
            }
            if(strcmp(str1, str2)>0){
                strcpy(temp,ni->value);
                strcpy(ni->value,nj->value);
                strcpy(nj->value,temp);
            }
        }
    }
}



