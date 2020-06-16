

#include "../DataStructures/bst.h"

void infixToPostfix(char *infix, char *postfix);
int evaluatePostfix(BSTNode *root, char *postfix, double *result);
int evaluate(BSTNode *root, char *expression, double *result);
