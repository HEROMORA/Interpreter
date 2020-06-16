#include <ctype.h>

#include "tools.h"

int charType(char c) {
    if (isdigit(c))
        return 1;
    if (isalpha(c) || c == '_' || c == '$')
        return 2;
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^')
        return 3;
    if (c == '.')
        return 4;
    if (c == '(' || c == '[' || c == '{')
        return 5;
    if (c == ')' || c == ']' || c == '}')
        return 6;
    return 0;
}

int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/' || c == '%')
        return 2;
    if (c == '^')
        return 3;
    return 0;
}

void deblank(char *s) {
    int i = 0, j;
    while (s[i]) {
        if (s[i] == ' ') {
            for (j = i; s[j]; j++) {
                s[j] = s[j + 1];
            }
        }
        if (s[i] != ' ')
            i++;
    }
}

Element charToElement(char c) {
    Element element;
    element.character = c;
    return element;
}

Element doubleToElement(double d) {
    Element element;
    element.constant = d;
    return element;
}

int isComment(char* instruction){
    if(instruction[0] == '/' && instruction[1] =='/')
        return 1;
    return 0;
}

int isIfStatement(char * instruction){
    int hasEqualEqual = 0;
    if(!(instruction[0] == 'i' && instruction[1] == 'f' && instruction[2] == ' '))
        return 0;
    int i = 3;
    do{
        if(charType(instruction[i]) != 2)
            return 0;
    } while (instruction[i++] == ' ');

    for (i; instruction[i]; ++i) {
        if(instruction[i] == '='){
            if(instruction[i+1] == '=')
                hasEqualEqual = 1;
        }
        if(instruction[i] == ':' && hasEqualEqual)
            return i;
    }
    return 0;
}
