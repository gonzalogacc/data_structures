#include <stdio.h>
#include "linked_list.h"

void main(){
    printf("Initialization\n");
    Node* n = init_list(2);
    printf("--> %d\n", n->value);
    printf("Before\n");
    print_list(n);

    n = append_node(n, 3);
    n = append_node(n, 4);
    n = append_node(n, 5);
    n = prepend_node(n, -1);

    printf("After\n");
    print_list(n);
    printf("Length of the list is %ld\n", len_list(n));
    free_list(n);
}