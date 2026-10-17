
#ifndef linked_list
#define linked_list
#include <stddef.h>

// Node def
typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Functions
Node* init_list(int value);
Node* append_node(Node* list, int value);
Node* prepend_node(Node* list, int value);
void print_list(Node* list);
void free_list(Node* list);
size_t len_list(Node* list);
int find_value(Node* list, int value);
Node* get_node_at(Node* node, int i);
Node* insert_at(Node* list, int value, int pos);
Node* pop_front(Node* list, int* pop_node);
Node* pop_back(Node* list, int* pop_node);
Node* init_list_from_array(int initial_list[], int array_size);
Node* delete_at_index(Node* list, int array_index);
Node* delete_by_value(Node* list, int value);

#endif
