#include <stdio.h>

#include "ReadEvaluate/io.h"

void printItems(Item** items, int counter) {
    for (int i = 0; i < counter; i++) {
        printf("%s  =    %0.2f \n", (*(items+i))->key, (*(items+i))->value);
    }
}

int main() {
    BSTNode *root = NULL;
    Item** items;
    int counter = 0;
    process(&root, items, &counter);
    if (!error){
        printf("\nBinary Search Tree InOrder:\n");
        inOrder(root);
        printf("\n");
        printf("\nHeap Sort by value:\n");
        heapSort(items, counter);
        printItems(items, counter);
    }

    return 0;
}

