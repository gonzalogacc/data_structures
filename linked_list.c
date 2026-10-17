
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


void fail_if_null(Node* node){
    if (node == NULL){
        fprintf(stderr, "The list cannot be NULL\n");
        exit(1);
    }
}

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

Node* init_list_from_array(int initial_array[], int array_size){
    // Init a linked list from an array of ints
    Node* nn = new_node(initial_array[0]);
    for (int i=1; i<array_size; i++){
        append_node(nn, initial_array[i]);
    }
    return nn;
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
    fail_if_null(list);

    size_t count = 0;
    while (list != NULL){
        count++;
        list = list->next;
    }
    return count;
}

int find_value(Node* list, int value){
    /* Find a value in the list and return the index. */
    fail_if_null(list);

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
    /* Return the node at position i, or NULL if i is out of range.*/
    if (i < 0){
        return NULL;
    }
    int count = 0;
    while (node != NULL){
        //printf("Value: %d: %d\n", node->value, count);
        if (count == i){
            //printf("Value found: %d: %d\n", node->value, count);
            return node;
        }
        node = node->next;
        count++;
    }
    return NULL;
}

Node* append_node(Node *list, int value){
    /* Add a node to the list.*/
    // Alloc a new node
    fail_if_null(list);

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
    fail_if_null(list);

    *pop_value = list->value;

    list = list->next;
    return list;
}

Node* pop_back(Node* list, int* pop_value){
    Node* head = list;
    fail_if_null(list);

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
    fail_if_null(node);

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


Node* delete_at_index(Node* head, int index){
    // Delete list at index position
    fail_if_null(head);
    Node* node = head;

    size_t list_size = len_list(head);
    if ((size_t) index >= list_size){
        fprintf(stderr, "List index out of range");
        exit(1);
    }
    
    if (index == 0) {
        return node->next;
    }

    Node* previous = head;
    int count = 0;
    while (node != NULL){
        if (count == index){
            // remove at this position
            previous->next = node->next;
            return head;
        }
        count++;
        previous = node;
        node = node->next;
    }
    fprintf(stderr, "List index out of range");
    exit(1);
}

Node* delete_by_value(Node* head, int value) {
    // remove first element with value=value from the list
    fail_if_null(head);

    Node* node = head;
    Node* previous = head;

    if (node->value == value){
        return node->next;
    }

    while (node != NULL){
        if (node->value == value){
            previous->next = node->next;
            return head;
        }
        previous = node;
        node = node->next;
    }
    return head;
}

Node* reverse_list(Node* head){
    // reverse the order of the list.
    fail_if_null(head);

    Node* node = head;
    Node* reversed = init_list(get_node_at(node, 0)->value);
    while (node != NULL){
        reversed = prepend_node(reversed, node->value);
        node = node->next;
    }
    return reversed;
}

// find_middle
// detect_cycle
// merge_sorted_lists
// remove_duplicates


void print_list(Node* list){
    /* Print the list */
    while (list != NULL){
        printf("%d\n", list->value);
        list = list->next;
    }
}

