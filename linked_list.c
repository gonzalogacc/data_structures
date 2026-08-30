
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


Node* new_node(int value){
    Node* node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

Node* init_list(int value){
    /* TODO: make this list to take a vairable number fo things to init a linked list. */
    Node *node = new_node(value);
    return node;
}

void free_list(Node* list){
    /* Clear the linked list.*/
    while (list != NULL){
        Node *next = list->next;
        free(list);
        list = next;
    }
}

size_t len_list(Node* list){
    /* Return the length of the list. */
    if (list == NULL){
        fprintf(stderr, "The list cannot be NULL\n");
        exit(1);
    }
    size_t count = 0;
    while (list != NULL){
        count++;
        list = list->next;
    }
    return count;
}

int find_value(Node* list, int value){
    /* Find a value in the list and return the index. */
    if (list == NULL){
        fprintf(stderr, "The list cannot be NULL\n");
        exit(1);
    }

    int i = 0;
    while(list != NULL){
        if (list->value == value){
            return i;
        }
        list = list->next;
        i++;
    }
    return -1;
}

Node* get_node_at(Node* node, int i){
    /* Return the node at position i.*/
    if (i>len_list(node)){
        fprintf(stderr, "List doesn't have position i=%d\n", i);
        exit(1);
    }
    int count = 0;
    while (node != NULL){
        printf("Value: %d: %d\n", node->value, count);
        if (count == i){
            printf("Value found: %d: %d\n", node->value, count);
            return node;
        }
        node = node->next;
        count++;
    }
}

Node* append_node(Node *list, int value){
    /* Add a node to the list.*/
    // Alloc a new node
    if (list == NULL){
        fprintf(stderr, "The list cannot be NULL\n");
        exit(1);
    }

    Node* nn = new_node(value);
    
    // go to the last node in the list and point 
    // the last node to the new node
    Node* head = list;
    while (list->next != NULL){
        list = list->next;
    }
    list->next = nn;
    return head;
}

Node* prepend_node(Node* list, int value){
    // Create a new node
    Node* nn = new_node(value);

    // Insert the new node at the beginning of the list
    nn->next = list;
    return nn;
}

Node* pop_front(Node* list, int* pop_value){
    /* Pop a node from the beginning of the list. */
    if (list == NULL){
        fprintf(stderr, "List can't be NULL");
        exit(1);
    }
    *pop_value = list->value;

    list = list->next;
    return list;
}

Node* pop_back(Node* list, int* pop_value){
    Node* head = list;
    if (list == NULL){
        fprintf(stderr, "List can't be NULL");
        exit(1);
    }
    Node* prev_node = NULL;
    while (list->next != NULL){
        prev_node = list;
        list = list->next;
    }
    prev_node->next = NULL;
    *pop_value = list->value;
    return head;
}

Node* insert_at(Node* node, int value, int pos){
    /* Insert the value at position of the linked list. */
    Node* head = node;
    if (node == NULL){
        fprintf(stderr, "The list cannot be NULL\n");
        exit(1);
    }

    // Insert at position 0 is a prepend
    if (pos == 0){
        return prepend_node(node, value);
    }

    Node *nn = new_node(value);

    int count = 0;
    while (node != NULL){
        // Insert if the position is correct
        if (count == pos-1){
            nn->next = node->next;
            node->next = nn;
        }
        count++;
        node = node->next;
    }
    return head;
}

void print_list(Node* list){
    /* Print the list */
    printf("%d\n", list->value);
    while (list != NULL){
        printf("%d\n", list->value);
        list = list->next;
    }
}

