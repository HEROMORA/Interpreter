#include <string.h>
#include <math.h>
#include <stdio.h>

#include "evaluation.h"
#include "../tools.h"
#include "../validations.h"

/** Start : Expression Evaluation Using Stacks */

void infixToPostfix(char *infix, char *postfix) {
    Stack *stack = newStack();
    int expected = 0;
    while (*infix) {
        if (charType(*infix) == 1) {
            while (charType(*infix) == 1 || *infix == '.')
                *postfix++ = *infix++;
            *postfix++ = ' ';
            expected = 1;
        } else if (charType(*infix) == 5) {
            push(stack, charToElement(*infix++));
        } else if (charType(*infix) == 6) {
            while (charType(top(stack).character) != 5) {
                *postfix++ = pop(stack).character;
                *postfix++ = ' ';
            }
            infix++;
            pop(stack);
            expected = 1;
        } else if (charType(*infix) == 2) {
            while (charType(*infix) == 2 || charType(*infix) == 1)
                *postfix++ = *infix++;
            *postfix++ = ' ';
            expected = 1;
        } else if (charType(*infix) == 3) {
            if (expected) {
                if (isEmpty(stack) || charType(top(stack).character) == 5 ||
                    precedence(top(stack).character) < precedence(*infix)) {
                    push(stack, charToElement(*infix++));
                } else if (precedence(top(stack).character) == precedence(*infix)) {
                    *postfix++ = pop(stack).character;
                    *postfix++ = ' ';
                    push(stack, charToElement(*infix++));
                } else {
                    while (!isEmpty(stack) && charType(top(stack).character) != 5 &&
                           precedence(top(stack).character) >= precedence(*infix)) {
                        *postfix++ = pop(stack).character;
                        *postfix++ = ' ';
                    }
                    push(stack, charToElement(*infix++));
                }
            } else
                *postfix++ = *infix++;
            expected = 0;
        }
    }
    while (!isEmpty(stack)) {
        *postfix++ = pop(stack).character;
        *postfix++ = ' ';
    }
    *(--postfix) = '\0';
    destroy(stack);
}

int evaluatePostfix(BSTNode *root, char *postfix, double *result) {
    Stack *stack = newStack();
    char *element = strtok(postfix, " ");
    while (element) {
        if (charType(*element) == 1)
            push(stack, doubleToElement(atof(element)));
        else if (charType(*element) == 2) {
            double value;
            if (!Search(root, element, &value))
                return 0;
            push(stack, doubleToElement(value));

        } else if (strlen(element) == 1) {
            double constant_1, constant_2;
            constant_2 = pop(stack).constant;
            constant_1 = pop(stack).constant;
            switch (*element) {
                case '+' :
                    push(stack, doubleToElement(constant_1 + constant_2));
                    break;
                case '-' :
                    push(stack, doubleToElement(constant_1 - constant_2));
                    break;
                case '*' :
                    push(stack, doubleToElement(constant_1 * constant_2));
                    break;
                case '/' :
                    push(stack, doubleToElement(constant_1 / constant_2));
                    break;
                case '%' :
                    if (!(remainder(constant_1, 1.0) == 0.0 && remainder(constant_2, 1.0) == 0.0))
                        return 0;
                    else {
                        int int_1 = (int) constant_1;
                        int int_2 = (int) constant_2;
                        push(stack, doubleToElement(int_1 % int_2));
                    }
                    break;
                case '^' :
                    push(stack, doubleToElement(pow(constant_1, constant_2)));
                    break;
                default:
                    break;
            }
        } else if (charType(*(element + 1)) == 1)
            push(stack, doubleToElement(atof(element)));
        else {
            if (*element == '-') {
                double value;
                if (!Search(root, ++element, &value))
                    return 0;
                push(stack, doubleToElement(-value));
            } else {
                element++;
                continue;
            }
        }
        element = strtok(NULL, " ");
    }
    *result = pop(stack).constant;
    return 1;
}

int evaluate(BSTNode *root, char *expression, double *result) {
    char postfix[strlen(expression) * 2];
    infixToPostfix(expression, postfix);
    if (!evaluatePostfix(root, postfix, result))
        return 0;
    return 1;
}



/** End : Expression Evaluation Using Stacks */

