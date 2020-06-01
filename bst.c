#include "bst.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BSTNode* addNewNode(char* key, TYPE value)
{
    BSTNode* bstNode =(BSTNode*)malloc(sizeof(BSTNode));
    bstNode->left=NULL;
    bstNode->right=NULL;
    bstNode->item = newItem(key, value);
    bstNode->item->value=value;
    strcpy(bstNode->item->key, key);
    return bstNode;
}

BSTNode* newNodeByItem(Item* item) {
    BSTNode* bstNode =(BSTNode*)malloc(sizeof(BSTNode));
    bstNode->left=NULL;
    bstNode->right=NULL;
    bstNode->item = item;
    return bstNode;
}

BSTNode* insert(BSTNode* current,char* key,TYPE value)
{
    if(!current)
        return addNewNode(key,value);
    if(strcasecmp(key,current->item->key)<0)
        current->left = insert(current->left,key,value);
    else if(strcasecmp(key,current->item->key)>0)
        current->right = insert(current->right,key,value);
    else
        current->item->value = value;
    return current;
}

BSTNode* insertByItem(BSTNode* current, Item* item)
{
    if(!current)
        return newNodeByItem(item);
    if(strcasecmp(item->key,current->item->key)<0)
        current->left = insert(current->left,item->key,item->value);
    else if(strcasecmp(item->key,current->item->key)>0)
        current->right = insert(current->right,item->key,item->value);
    else
        current->item->value = item->value;
    return current;
}

void inOrder(BSTNode* root)
{
    if(root)
    {
        inOrder(root->left);
        printf("%s  =    %0.2f \n",root->item->key,root->item->value);
        inOrder(root->right);
    }
}

double Search(BSTNode *root,char* key){
    BSTNode *current=root;
    while(current != NULL)
    {
        if (strcasecmp(current->item->key,key) == 0 )
            return current->item->value;
        else if (strcasecmp(current->item->key,key) > 0){
            if(current->left == NULL) break;
            else  current = current->left;
        }
        else{
            if(current->right == NULL) break;
            else current=current->right;
        }
    }
    return 0;
}