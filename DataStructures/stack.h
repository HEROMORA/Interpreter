typedef union Element {
    double constant;
    char character;
} Element;

typedef struct StackNode {
    Element element;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
} Stack;

StackNode *newStackNode(Element element);

Stack *newStack() ;

void push(Stack *stack, Element element);

Element pop(Stack *stack);

Element top(Stack *stack);

int isEmpty(Stack *stack);

void destroy(Stack *stack);
