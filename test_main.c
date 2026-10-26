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
    ASSERT(len_list(nn) == 4, "The list has the wrong list of elements");
}

void test_swap_nodes_in_place(){
    int i_array[] = {1,2,3,4};
    size_t array_size = sizeof(i_array) / sizeof(i_array[0]);

    Node* nn = init_list_from_array(i_array, array_size);

    nn = swap_nodes(nn, 1, 2);
    ASSERT(get_node_at(nn, 1)->value == 3, "Node not swapped");
    ASSERT(get_node_at(nn, 2)->value == 2, "Node not swapped");

    ASSERT(swap_nodes(nn, 99998, 9999) == NULL, "Out of bounds should have been NULL");
    ASSERT(swap_nodes(nn, 1, 9999) == NULL, "Out of bounds should have been NULL");
}


void test_find_middle(){
    int i_array[] = {1,2,3,4,5};
    size_t array_size = sizeof(i_array) / sizeof(i_array[0]);
    Node* nn = init_list_from_array(i_array, array_size);
    ASSERT(find_middle(nn)->value == 3, "the middle should be 3 but it's not");

    int i_array_2[] = {1,2,3,4,5,6};
    size_t array_size_2 = sizeof(i_array_2) / sizeof(i_array_2[0]);
    nn = init_list_from_array(i_array_2, array_size_2);
    ASSERT(find_middle(nn)->value == 3, "the middle should be 3 but it's not");

    int i_array_3[] = {1,2,3};
    size_t array_size_3 = sizeof(i_array_3) / sizeof(i_array_3[0]);
    nn = init_list_from_array(i_array_3, array_size_3);
    ASSERT(find_middle(nn)->value == 2, "the middle should be 3 but it's not");

    int i_array_4[] = {1,2,3};
    size_t array_size_4 = sizeof(i_array_4) / sizeof(i_array_4[0]);
    nn = init_list_from_array(i_array_4, array_size_4);
    ASSERT(find_middle(nn)->value == 2, "the middle should be 3 but it's not");

}


void test_find_node(){
    //Find a node in a list
    int i_array[] = {1,2,3,4};
    size_t array_size = sizeof(i_array) / sizeof(i_array[0]);
    Node* nn = init_list_from_array(i_array, array_size);

    // Find the second node
    Node* node_found = find_node(nn, nn->next);
    ASSERT(node_found != NULL, "node_found is NULL");
    ASSERT(nn->next == node_found, "Node address is not the same");

}

void test_detect_cycle(){
    // create a linked list that is a circle
    int i_array[] = {1,2,3,4,5};
    size_t array_size = sizeof(i_array) / sizeof(i_array[0]);
    Node* nn = init_list_from_array(i_array, array_size);
    Node* head = get_node_at(nn, 0);
    Node* tail = get_node_at(nn, 4);
    tail->next = head; 

    Node* result = detect_cycle(nn);
    ASSERT(result != NULL, "Cycle was not detected");
    ASSERT(head->next == get_node_at(nn, 1), "detect_cycle should not modify the list");

}

void test_detect_cycle_no_cycle(){
    // a normal list has no cycle and must stay intact
    int i_array[] = {1,2,3,4,5};
    size_t array_size = sizeof(i_array) / sizeof(i_array[0]);
    Node* nn = init_list_from_array(i_array, array_size);

    Node* result = detect_cycle(nn);
    ASSERT(result == NULL, "A list without a cycle should return NULL");
    ASSERT(len_list(nn) == array_size, "detect_cycle should not modify the list");
    free_list(nn);
}

void test_detect_cycle_self_loop(){
    // a single node pointing to itself is a cycle
    Node* nn = init_list(1);
    nn->next = nn;

    ASSERT(detect_cycle(nn) != NULL, "A node pointing to itself is a cycle");
    nn->next = NULL;
    free_list(nn);
}

void test_detect_cycle_two_nodes(){
    // two nodes without a cycle
    Node* nn = init_list(1);
    nn = append_node(nn, 2);

    ASSERT(detect_cycle(nn) == NULL, "Two nodes without a cycle should return NULL");
    free_list(nn);
}

void test_detect_cycle_single_node(){
    // a single node without a cycle
    Node* nn = init_list(1);

    ASSERT(detect_cycle(nn) == NULL, "A single node without a cycle should return NULL");
    free_list(nn);
}

int list_matches(Node* list, int expected[], size_t expected_size){
    // 1 if the list holds exactly the values in expected, in order
    for (size_t i = 0; i < expected_size; i++){
        if (list == NULL || list->value != expected[i]){
            return 0;
        }
        list = list->next;
    }
    return list == NULL;
}

void test_merge_sorted_lists_interleaved(){
    int a[] = {1,3,5};
    int b[] = {2,4,6};
    int expected[] = {1,2,3,4,5,6};
    Node* l1 = init_list_from_array(a, 3);
    Node* l2 = init_list_from_array(b, 3);

    Node* merged = merge_sorted_lists(l1, l2);
    ASSERT(list_matches(merged, expected, 6), "Interleaved lists should merge to 1..6");
    free_list(merged);
}

void test_merge_sorted_lists_one_after_other(){
    // every value in the first list is smaller than the second
    int a[] = {1,2,3};
    int b[] = {4,5,6};
    int expected[] = {1,2,3,4,5,6};
    Node* l1 = init_list_from_array(a, 3);
    Node* l2 = init_list_from_array(b, 3);

    Node* merged = merge_sorted_lists(l1, l2);
    ASSERT(list_matches(merged, expected, 6), "Second list should be appended after the first");
    free_list(merged);
}

void test_merge_sorted_lists_second_starts_smaller(){
    // the head of the result comes from the second list
    int a[] = {4,5,6};
    int b[] = {1,2,3};
    int expected[] = {1,2,3,4,5,6};
    Node* l1 = init_list_from_array(a, 3);
    Node* l2 = init_list_from_array(b, 3);

    Node* merged = merge_sorted_lists(l1, l2);
    ASSERT(list_matches(merged, expected, 6), "Head should come from the second list");
    free_list(merged);
}

void test_merge_sorted_lists_different_lengths(){
    // the longer list has several nodes left over at the end
    int a[] = {1,10};
    int b[] = {2,3,4,5};
    int expected[] = {1,2,3,4,5,10};
    Node* l1 = init_list_from_array(a, 2);
    Node* l2 = init_list_from_array(b, 4);

    Node* merged = merge_sorted_lists(l1, l2);
    ASSERT(list_matches(merged, expected, 6), "All leftover nodes should be kept");
    free_list(merged);
}

void test_merge_sorted_lists_duplicates(){
    // equal values from both lists are all kept
    int a[] = {1,2,2};
    int b[] = {2,3};
    int expected[] = {1,2,2,2,3};
    Node* l1 = init_list_from_array(a, 3);
    Node* l2 = init_list_from_array(b, 2);

    Node* merged = merge_sorted_lists(l1, l2);
    ASSERT(list_matches(merged, expected, 5), "Duplicate values should all be kept");
    free_list(merged);
}

void test_merge_sorted_lists_single_nodes(){
    int expected[] = {1,5};
    Node* l1 = init_list(5);
    Node* l2 = init_list(1);

    Node* merged = merge_sorted_lists(l1, l2);
    ASSERT(list_matches(merged, expected, 2), "Two single nodes should merge to 1, 5");
    free_list(merged);
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
    RUN_TEST(test_swap_nodes_in_place);
    RUN_TEST(test_find_middle);
    RUN_TEST(test_find_node);
    RUN_TEST(test_detect_cycle);
    RUN_TEST(test_detect_cycle_no_cycle);
    RUN_TEST(test_detect_cycle_self_loop);
    RUN_TEST(test_detect_cycle_two_nodes);
    RUN_TEST(test_detect_cycle_single_node);
    RUN_TEST(test_merge_sorted_lists_interleaved);
    RUN_TEST(test_merge_sorted_lists_one_after_other);
    RUN_TEST(test_merge_sorted_lists_second_starts_smaller);
    RUN_TEST(test_merge_sorted_lists_different_lengths);
    RUN_TEST(test_merge_sorted_lists_duplicates);
    RUN_TEST(test_merge_sorted_lists_single_nodes);

    TEST_REPORT();
    return tests_failed != 0; // Return non-zero exit code if any test failed
}
