#include <stdio.h>
#include <string.h>
#define NUM_TERMINALS 6
#define NUM_NON_TERMINALS 3
#define MAX_LENGTH 50// Function to check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '*' || ch == '(' || ch == ')' || ch == 'id' || ch == '$');
}
// Function to get the precedence of an operator
char getPrecedence(char op) {
    switch (op) {
        case '+':
            return 1;
        case '*':
            return 2;
        case '(':
        case ')':
        case 'id':
        case '$':
            return 0;
        default:
            return -1; // Error
    }
}

// Function to initialize the operator precedence parsing table
void initializeTable(char table[][NUM_TERMINALS]) {
    // Terminals: +, *, (, ), id, $
    // Non-terminals: E, T, F
    // Initialize the table with X (no entry)
    for (int i = 0; i < NUM_NON_TERMINALS; i++) {
        for (int j = 0; j < NUM_TERMINALS; j++) {
            table[i][j] = 'X';
        }
    }
    // Fill in the entries based on the grammar
    table[0][0] = '>';  // E + T
    table[0][1] = '<';  // E * T
    table[0][2] = '<';  // E ( E )
    table[0][3] = '>';  // E id
    table[0][5] = '>';  // E $
    table[1][0] = '>';  // T + F
    table[1][1] = '>';  // T * F
    table[1][2] = '<';  // T ( E )
    table[1][3] = '>';  // T id
    table[1][5] = '>';  // T $
    table[2][0] = '<';  // F + T
    table[2][1] = '<';  // F * T
    table[2][2] = '<';  // F ( E )
    table[2][3] = '=';  // F id
    table[2][4] = 'X';  // F $
}

// Function to perform operator precedence parsing
int operatorPrecedenceParsing(char input[], char table[][NUM_TERMINALS]) {
    char stack[MAX_LENGTH];
    int top = -1;

    // Push a dollar sign onto the stack
    stack[++top] = '$';

    // Append a dollar sign to the end of the input
    strcat(input, "$");

    // Initialize the input pointer and stack symbol
    int ip = 0;
    char stackTop = stack[top];

    printf("Stack\t\tInput\t\tAction\n");

    while (stackTop != '$') {
        // Print the current stack and input
        printf("%-10s\t%-15s\t", stack, &input[ip]);

        // Check if the stack top and input symbol have the same precedence
        if (getPrecedence(stackTop) >= getPrecedence(input[ip])) {
            printf("Reduce ");
            // Simulate reducing based on precedence
            // This step is simplified for the given grammar
            top--;
        } else {
            printf("Shift ");
            // Simulate shifting the input symbol onto the stack
            stack[++top] = input[ip++];
        }

        // Move to the next line
        printf("\n");
        // Update the stack top
        stackTop = stack[top];
    }
    // Print the final action
    printf("%-10s\t%-15s\tAccept\n", stack, &input[ip]); 
    return 0;
}
int main() {
    char input[MAX_LENGTH];
    char parsingTable[NUM_NON_TERMINALS][NUM_TERMINALS]; 
    // Input string: "id+id*id"
    printf("Enter the input string: ");
    scanf("%s", input); 
    // Initialize and print the operator precedence parsing table
    initializeTable(parsingTable);
    printf("\nOperator Precedence Parsing Table:\n");
    printf("     +      *      (      )      id      $\n");
    for (int i = 0; i < NUM_NON_TERMINALS; i++) {
        printf("%c  ", 'E' + i);
        for (int j = 0; j < NUM_TERMINALS; j++) {
            printf("  %c    ", parsingTable[i][j]);
        }
        printf("\n");
    }
    // Perform operator precedence parsing
    operatorPrecedenceParsing(input, parsingTable); 
    return 0;
}
