#include <stdio.h>

#include "ReadEvaluate/io.h"

void printItems(Item** items, int counter) {
    for (int i = 0; i < counter; i++) {
        printf("%s  =    %0.2f \n", (*(items+i))->key, (*(items+i))->value);
    }
}

void bstToHeap(BSTNode* node, Item** items, int* i) {
    if (node) {
        *(items + *i) = node->item;
        *i = *i + 1;
        bstToHeap(node->left, items, i);
        bstToHeap(node->right, items, i);
    }
}

int main() {
    BSTNode *root = NULL;
    Item** items;
    process(&root);
    if (!error){
        printf("\nBinary Search Tree InOrder:\n");
        inOrder(root);
        printf("\n");
        printf("\nHeap Sort by value:\n");
        int co = 0;
        bstToHeap(root, items, &co);
        heapSort(items, co);
        printItems(items, co);
    }
    return 0;
}
