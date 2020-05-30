#include "heap.h"

struct bNode
{
    struct bNode *right;
    struct bNode *left;
    Item* item;
}n;

typedef struct bNode BSTNode;

BSTNode * addNewNode(char* key, TYPE value);
BSTNode* insert(BSTNode* current, char* key, TYPE value);
void inOrder(BSTNode* root);
double Search(BSTNode *root,char* key);
