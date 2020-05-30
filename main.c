#include <stdio.h>

#include "heap.h"

int main() {
    int n = 10;
    Item* nodes[n];
    nodes[0] = newItem("A", 513.25);
    nodes[1] = newItem("B", 712.23);
    nodes[2] = newItem("C", 42.31);
    nodes[3] = newItem("D", 1);
    nodes[4] = newItem("E", 5000);
    nodes[5] = newItem("F", 22);
    nodes[6] = newItem("G", 100);
    nodes[7] = newItem("H", 813.123);
    nodes[8] = newItem("I", 900.8124);
    nodes[9] = newItem("J", 5);

    heapSort(nodes, n);


    for (int i = 0; i < n; i++) {
        printf("%s \t\t\t %lf\n", nodes[i]->key, nodes[i]->value);
    }


    return 0;
}
