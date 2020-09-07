#ifndef Linked_list
#define Linked_list

#include <stdbool.h>

typedef struct ELE {
    struct ELE *next;
    struct ELE *prev;
    char *value; 
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} linked_list;


linked_list *create_linked_list();

void free_list(linked_list *list);

bool linked_list_add(linked_list *list, char *v);

bool linked_list_add_tail(linked_list *list, char *v);

bool linked_list_delete(linked_list *list, Node *node);

Node *linked_list_search(linked_list *list, char *v);

Node *linked_list_get(linked_list *list, int index);

void linked_list_print(linked_list *list);

void linked_list_sort(linked_list *list);
#endif
