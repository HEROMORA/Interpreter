#include "validations.h"
#include "tools.h"

/** Validation */

int balancedParentheses(char *expression) {
    Stack *stack = newStack();
    while (*expression) {
        if (*expression == '(' || *expression == '[' || *expression == '{')
            push(stack, charToElement(*expression));
        else if (*expression == ')') {
            if (!isEmpty(stack)) {
                if (pop(stack).character == '(') {
                    expression++;
                    continue;
                }
            }
            return 0;
        } else if (*expression == ']') {
            if (!isEmpty(stack)) {
                if (pop(stack).character == '[') {
                    expression++;
                    continue;
                }
            }
            return 0;
        } else if (*expression == '}') {
            if (!isEmpty(stack)) {
                if (pop(stack).character == '{') {
                    expression++;
                    continue;
                }
            }
            return 0;
        }
        expression++;
    }
    int empty = isEmpty(stack);
    destroy(stack);
    return empty;
}

int validVariable(char **variable) {
    char *cursor = *variable;
    while (*cursor == ' ')
        cursor++;
    *variable = cursor;
    if (charType(*cursor) != 2)
        return 0;
    while (*cursor) {
        if (charType(*cursor) == 2 || charType(*cursor) == 1)
            cursor++;
        else if (*cursor == ' ') {
            *cursor = '\0';
            cursor++;
            while (*cursor) {
                if (*cursor != ' ')
                    return 0;
                cursor++;
            }
        } else
            return 0;
    }
    return 1;
}

int validateExpression(char *start, char *end) {
    char *cursor = start;
    char temp = *end;
    *end = '\0';
    int op = 1;
    int loop = 1;
    while (*cursor) {
        if (*cursor == ' ') {
            cursor++;
            continue;
        } else if (charType(*cursor) == 5) {
            op = 0;
            char *stop = ++cursor;
            while (charType(*stop) != 6)
                stop++;
            if (!validateExpression(cursor, stop) || cursor == stop)
                return 0;
            cursor = stop + 1;
            while (*cursor && charType(*cursor) != 3) {
                if (*cursor != ' ')
                    return 0;
            }
        } else if (charType(*cursor) == 1) {
            int dec = 0;
            op = 0;
            while (*cursor) {
                if (charType(*cursor) == 1) {
                    cursor++;
                    continue;
                } else if (charType(*cursor) == 4) {
                    if (dec)
                        return 0;
                    else
                        dec = 1;
                    if (charType(*(cursor + 1)) != 1)
                        return 0;
                } else if (charType(*cursor) == 3)
                    break;
                else if (*cursor == ' ') {
                    while (*cursor++ == ' ') {
                        if (*cursor != ' ' && charType(*cursor) != 3 && *cursor)
                            return 0;
                    }
                    break;
                } else
                    return 0;
                cursor++;
            }
        } else if (charType(*cursor) == 2) {
            op = 0;
            while (*cursor) {
                if (charType(*cursor) == 1 || charType(*cursor) == 2)
                    cursor++;
                else if (charType(*cursor) == 3)
                    break;
                else if (*cursor == ' ') {
                    while (*cursor++ == ' ') {
                        if (*cursor != ' ' && charType(*cursor) != 3 && *cursor)
                            return 0;
                    }
                    break;
                } else
                    return 0;
            }
        } else if (charType(*cursor) == 3) {
            if (op && *cursor != '+' && *cursor != '-')
                return 0;
            cursor++;
            op = 1;
        } else
            return 0;
    }
    *end = temp;
    return op ? 0 : 1;
}

int validExpression(char *expression) {
    //imbalanced parentheses
    if (!balancedParentheses(expression))
        return 0;
    //invalid character
    char *cursor = expression;
    while (*cursor) {
        if (!charType(*cursor) && *cursor != ' ')
            return 0;
        cursor++;
    }
    //invalid numbers or variables
    if (!validateExpression(expression, cursor))
        return 0;
    else
        deblank(expression);
    return 1;
}



/** Validation */