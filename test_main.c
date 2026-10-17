#include "minitests.h"
#include "linked_list.h" // Your code under test
#include <stddef.h>
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
    Node* list = init_list(10);
    list = append_node(list, 20);
    list = append_node(list, 30);
    list = append_node(list, 40);

    ASSERT(get_node_at(list, 0)->value == 10, "get_node_at should return the head at position 0 (value 10)");
    ASSERT(get_node_at(list, 2)->value == 30, "get_node_at should return the node at position 2 (value 30)");
    ASSERT(get_node_at(list, 3)->value == 40, "get_node_at should return the last node at position 3 (value 40)");
    ASSERT(get_node_at(list, 4) == NULL, "get_node_at should return NULL for position == length");
    ASSERT(get_node_at(list, -1) == NULL, "get_node_at should return NULL for a negative position");
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

    int returned;
    list = pop_front(list, &returned);

    ASSERT(returned == 1, "Returned wrong value X");
    ASSERT(list->value == 2, "Returned wrong value1");
}

void test_pop_back(void){
    Node* list = init_list(1);
    list = append_node(list, 2);

    int returned;
    list = pop_back(list, &returned);
    ASSERT(returned == 2, "Returned wrong value X");
    ASSERT(list->value == 1, "Returned wrong value1");
}


void test_init_list_from_array(void){
    int i_array[] = {1,2,3,4};
    int array_size = sizeof(i_array) / sizeof(i_array[0]);

    Node* nn = init_list_from_array(i_array, array_size);

    ASSERT(get_node_at(nn, 3)->value == 4, "Wrong last number");
}


void test_delete_at_index(){
    int i_array[] = {1,2,3,4};
    int array_size = sizeof(i_array) / sizeof(i_array[0]);

    int delete_index = 2;
    Node* nn = init_list_from_array(i_array, array_size);
    nn = delete_at_index(nn, delete_index);

    ASSERT(len_list(nn) == 3, "Wrong len for list");
    ASSERT(get_node_at(nn, delete_index)->value == 4, "Wrong index at the deleted part");
    ASSERT(find_value(nn, 3) == -1, "Item found but it shouldnt be there");

    delete_index = 2;
    nn = delete_at_index(nn, delete_index);
    ASSERT(len_list(nn) == 2, "Wrong len for list");

}

void test_delete_first_index(){
    int i_array[] = {1,2,3,4};
    size_t array_size = sizeof(i_array) / sizeof(i_array[0]);

    // delete first index
    int delete_index = 0;
    Node* nn = init_list_from_array(i_array, array_size);
    nn = delete_at_index(nn, delete_index);
    ASSERT(get_node_at(nn, 0)->value == 2, "Wrong number at the head of the list");
}


void test_delete_by_value(){
    int i_array[] = {1,2,3,1,4};
    size_t array_size = sizeof(i_array) / sizeof(i_array[0]);

    int delete_value = 1;
    Node* nn = init_list_from_array(i_array, array_size);
    nn = delete_by_value(nn, delete_value);
    ASSERT(len_list(nn) == array_size-1, "Wrong array length!");
    
    delete_value = 1;
    nn = delete_by_value(nn, delete_value);
    ASSERT(len_list(nn) == array_size-2, "Wrong array length!");

    delete_value = 2;
    nn = delete_by_value(nn, delete_value);
    ASSERT(len_list(nn) == array_size-3, "Wrong array length!");

    delete_value = 4;
    nn = delete_by_value(nn, delete_value);
    ASSERT(len_list(nn) == array_size-4, "Wrong array length!");

    //delete_value = 3;
    //nn = delete_by_value(nn, delete_value);
    //ASSERT(len_list(nn) == array_size-4, "Wrong array length!");
}


void test_reverse_list(){
    int i_array[] = {1,2,3,4};
    size_t array_size = sizeof(i_array) / sizeof(i_array[0]);

    Node* nn = init_list_from_array(i_array, array_size);
    nn = reverse_list(nn);
    ASSERT(get_node_at(nn, 0)->value == 4, "Elements are not reverted.");
    ASSERT(get_node_at(nn, 1)->value == 3, "Elements are not reverted.");
    ASSERT(get_node_at(nn, 2)->value == 2, "Elements are not reverted.");
    ASSERT(get_node_at(nn, 3)->value == 1, "Elements are not reverted.");
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
    RUN_TEST(test_init_list_from_array);
    RUN_TEST(test_delete_at_index);
    RUN_TEST(test_delete_first_index);
    RUN_TEST(test_delete_by_value);
    RUN_TEST(test_reverse_list);

    TEST_REPORT();
    return tests_failed != 0; // Return non-zero exit code if any test failed
}
