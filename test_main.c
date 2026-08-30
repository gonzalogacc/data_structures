#include "minitests.h"
#include "linked_list.h" // Your code under test
#include <stdio.h>

int tests_run = 0;
int tests_failed = 0;

void test_init_list(void) {
    Node* n = init_list(2);
    ASSERT(n->value == 2, "Node value should be 2");
    ASSERT(n->next == NULL, "A freshly initialized node's next should be NULL");
    free_list(n);
}

void test_insert_node(void){
    // Create a list insert a node and check before and after.
    Node* n = init_list(1);
    ASSERT(len_list(n) == 1, "List should have exactly 1 node before appending");
    n = append_node(n, 2);
    ASSERT(len_list(n) == 2, "List should have exactly 2 nodes after appending");
    free_list(n);
}

void test_append_node_last_element(void){
    // newly appended node ends up correctly as the last one.
    Node* list = init_list(1);
    list = append_node(list, 2);
    list = append_node(list, 3);

    ASSERT(len_list(list) == 3, "List should have 3 nodes after two appends");

    Node* tail = get_node_at(list, 2);
    ASSERT(tail->value == 3, "Last node should have the most recently appended value");
    ASSERT(tail->next == NULL, "Last node's next should be NULL");

    free_list(list);
}

void test_find_element_in_list(void){
    Node* n = init_list(4);
    for (int i=0; i<10; i++){
        n = append_node(n, i);
    }
    ASSERT(find_value(n, 5) == 6, "find_value should return index 6 for value 5");
    ASSERT(find_value(n, 999) == -1, "find_value should return -1 for a value not in the list");
    ASSERT(find_value(n, 9) == 10, "find_value should find a value stored in the last node");

    free_list(n);
}

void test_get_node_at(void){
    Node* list = init_list(1);
    list = append_node(list, 1);
    list = append_node(list, 22);
    list = append_node(list, 22);

    Node* found_node = get_node_at(list, 2);
    ASSERT(found_node->value == 22, "get_node_at should return the node at position 2 (value 22)");
    free_list(list);
}


void test_insert_node_at(void){
    Node* list = init_list(1);
    list = append_node(list, 2);
    list = append_node(list, 3);
    list = append_node(list, 4);

    list = insert_at(list, 99, 2);
    ASSERT(get_node_at(list, 2)->value == 99, "failed to insert node at position 2");

    list = insert_at(list, 99, 0);
    ASSERT(get_node_at(list, 0)->value == 99, "failed to insert node at position 0");
    
    free_list(list);
}


void test_pop_front(void){
    Node* list = init_list(1);
    list = append_node(list, 2);

    int* returned;
    list = pop_front(list, returned);
    ASSERT(*returned == 1, "Returned wrong value X");
    ASSERT(list->value == 2, "Returned wrong value1");
}

void test_pop_back(void){
    Node* list = init_list(1);
    list = append_node(list, 2);

    int* returned;
    list = pop_back(list, returned);
    ASSERT(*returned == 2, "Returned wrong value X");
    ASSERT(list->value == 1, "Returned wrong value1");
}

int main(void) {

    RUN_TEST(test_init_list);
    RUN_TEST(test_insert_node);
    RUN_TEST(test_append_node_last_element);
    RUN_TEST(test_find_element_in_list);
    RUN_TEST(test_get_node_at);
    RUN_TEST(test_insert_node_at);
    RUN_TEST(test_pop_front);
    RUN_TEST(test_pop_back);

    TEST_REPORT();
    return tests_failed != 0; // Return non-zero exit code if any test failed
}