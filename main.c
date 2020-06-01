#include <stdio.h>

#include "bst.h"

int main() {
    int x = 10;
    Item* items[x];
    items[0] = newItem("Z", 513.25);
    items[1] = newItem("B", 712.23);
    items[2] = newItem("H", 42.31);
    items[3] = newItem("D", 1);
    items[4] = newItem("X", 5000);
    items[5] = newItem("C", 22);
    items[6] = newItem("G", 100);
    items[7] = newItem("V", 813.123);
    items[8] = newItem("I", 900.8124);
    items[9] = newItem("O", 5);

    heapSort(items, x);

    printf("Sort by Value: \n\n");
    for (int i = 0; i < x; i++) {
        printf("%s \t\t\t %lf\n", items[i]->key, items[i]->value);
    }

    printf("\n");
    printf("-----------------------------\n");
    printf("Sort by Key: \n\n");

    BSTNode* nodes[10];
    for (int i = 0; i < x; i++) {
        nodes[i] = newNodeByItem(items[i]);
        nodes[0] = insert(nodes[0], nodes[i]->item->key, nodes[i]->item->value);
    }

    inOrder(nodes[0]);





    return 0;
}
