#include <string.h>
#include <stdio.h>

#include "../validations.h"
#include "../tools.h"
#include "io.h"

/** Processing Input from File */



int parse(char *instruction, char **variable, char **expression) {
    char *cursor = instruction;
    int found = 0;
    while (*cursor) {
        if (*cursor == '=') {
            *cursor = '\0';
            *variable = instruction;
            *expression = cursor + 1;
            found = 1;
            break;
        }
        cursor++;
    }
    return found;
}


int validateIf(char *instruction, int end, BSTNode **root, Item** items, int* counter) {
    char leftHandSide[end];
    strcpy(leftHandSide, "");
    int i = 3;
    while (instruction[i] != '=') {
        if (instruction[i] == ' ') {
            i++;
            continue;
        }
        char dummy[2];
        dummy[0] = instruction[i];
        dummy[1] = '\0';
        strcat(leftHandSide, dummy);
        i++;
    }

    char rightHandSide[end];
    strcpy(rightHandSide, "");
    i = i + 2;
    while (i < end) {
        if (instruction[i] == ' ') {
            i++;
            continue;
        }
        char dummy[2];
        dummy[0] = instruction[i];
        dummy[1] = '\0';
        strcat(rightHandSide, dummy);
        i++;
    }

    BSTNode *copy = *root;
    char leftHandSideExpression[end + 7];
    strcpy(leftHandSideExpression, "_LHS = ");
    strcat(leftHandSideExpression, leftHandSide);

    compute(&copy, items, leftHandSideExpression, 1, counter);

    char rightHandSideExpression[end + 7];
    strcpy(rightHandSideExpression, "_RHS = ");
    strcat(rightHandSideExpression, rightHandSide);
    compute(&copy,items,  rightHandSideExpression, 1, counter);

    double valueOfLHS;
    double valueOfRHS;
    Search(copy, "_LHS", &valueOfLHS);
    Search(copy, "_RHS", &valueOfRHS);

    delete(copy, "_LHS");
    delete(copy, "_RHS");
    if (valueOfLHS != valueOfRHS)
        return 0;

    return 1;
}

void compute(BSTNode **root, Item** items, char *instruction, int line, int* counter) {
    char *variable, *expression;
    char copy[strlen(instruction)];
    int i;

    strcpy(copy, instruction);

    if (isComment(instruction)) return;

    if ((i = isIfStatement(instruction)) > 0) {
        if (validateIf(instruction, i, root, items, counter))
            compute(root,items, &instruction[i + 1], line, counter);
        return;
    }

    if (!parse(instruction, &variable, &expression)) {
        printf("Error in line %d : %s > Missing Equal sign\n", line, copy);
        error = 1;
        return;
    }

    if (!validVariable(&variable)) {
        printf("Error in line %d : %s > More than one/Invalid variable\n", line, copy);
        error = 1;
        return;
    }

    if (!validExpression(expression)) {
        printf("Error in line %d : %s > Invalid Expression\n", line, copy);
        error = 1;
        return;
    }

    double value = 7;
    if (!evaluate(*root, expression, &value)) {
        printf("Error in line %d : %s > Error in Evaluation\n", line, copy);
        error = 1;
        return;
    }

    *root = insert(*root, variable, value);

    if (!strcmp(variable, "_LHS") || !strcmp(variable, "_RHS")) return;

    *(items + *counter) = newItem(variable, value);
    *counter = *counter + 1;
}


void readInput(FILE *file, BSTNode **root, Item** items, int* counter) {
    char input[256];
    int line = 1;
    while (!feof(file)) {
        fgets(input, 256, file);
        if (input[strlen(input) - 1] == '\n')
            input[strlen(input) - 1] = '\0';
        compute(root, items, input, line++, counter);
    }
}

void process(BSTNode **root, Item** items, int* counter) {
    error = 0;
    char filename[32];
    FILE *file;
    int found = 0;
    while (!found) {
        printf("Please enter source file:\n");
        fgets(filename, 32, stdin);
        filename[strlen(filename) - 1] = '\0';
        file = fopen(filename, "r");
        if (file) {
            found = 1;
            readInput(file, root, items, counter);
        } else {
            printf("File not found!\n");
        }
    }
}