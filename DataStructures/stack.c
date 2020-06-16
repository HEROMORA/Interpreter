#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

StackNode *newStackNode(Element element) {
    StackNode *newStackNode = malloc(sizeof(StackNode));
    newStackNode->element = element;
    newStackNode->next = NULL;
    return newStackNode;
}

Stack *newStack() {
    Stack *stack = malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack *stack, Element element) {
    StackNode *stackNode = newStackNode(element);
    stackNode->next = stack->top;
    stack->top = stackNode;
}

Element pop(Stack *stack) {
    StackNode *temp = stack->top;
    Element element = temp->element;
    stack->top = temp->next;
    free(temp);
    return element;
}

Element top(Stack *stack) {
    return stack->top->element;
}

int isEmpty(Stack *stack) {
    if (stack->top)
        return 0;
    else
        return 1;
}

void destroy(Stack *stack) {
    while (!isEmpty(stack))
        pop(stack);
    free(stack);
}

