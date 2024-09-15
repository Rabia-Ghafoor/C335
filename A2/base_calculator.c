

// Written by Rabia Ghafoor 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define stackSize 10

typedef struct {
    int *data, top, capacity;
} Stack;

Stack* myStack(int capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack-> data = (int *)malloc(capacity * sizeof(int));
    stack-> top = -1;
    stack-> capacity = capacity;
    return stack;
}

void freeStack(Stack *stack) {
    free(stack->data);
    free(stack);
}

int emptyStack(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Additional values can't be added.\n");
        exit(1);
    }
    stack->data[++(stack->top)] = value;
}

int pop(Stack *stack) {
    if (emptyStack(stack)) {
        printf("No values are left to pop.\n");
        exit(1);
    }
    return stack->data[(stack->top)--];
}

// converting binary string to an unsigned integer
unsigned int binaryUnsigned(const char *binStr) {
    unsigned int res = 0;
    for (int i = 2; binStr[i] != '\0'; i++) { // Start at index 2 (after "0b")
        res = (res << 1) + (binStr[i] - '0'); // Shift left and add current binary digit
    }
    return res;
}

// converting hexadecimal string (starting with 0x) to an unsigned integer
unsigned int hexUnsigned(const char *hexStr) {
    unsigned int res = 0;
    for (int i = 2; hexStr[i] != '\0'; i++) { // staring at i= 2 because of 0x
        res = res * 16;


        if (hexStr[i] >= '0' && hexStr[i] <= '9') {
            res += hexStr[i] - '0'; // Convert '0'-'9' to 0-9

        } else if (hexStr[i] >= 'a' && hexStr[i] <= 'f') {
            res += hexStr[i] - 'a' + 10; // Convert 'a'-'f' to 10-15
        }
    }
    return res;
}


unsigned int decimalUnsigned(const char *decStr) {
    unsigned int res = 0;
    // for loop to iterate over decimal string and eventaully convert to unsigned int
    for (int i = 0; decStr[i] != '\0'; i++) {
        res = res * 10 + (decStr[i] - '0'); // multiply by 10 and add current digit
    }
    return res;
}

// checking if a string starts with a given prefix
int stringPrefix(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

// parsing an argument 

unsigned int parseArg(const char *arg) {
    if (stringPrefix(arg, "0b")) { // for binary
        return binaryUnsigned(arg);
    } else if (stringPrefix(arg, "0x")) { // for hexadecimal
        return hexUnsigned(arg);
    } else { // Decimal case
        return decimalUnsigned(arg);
    }
}





int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf(" ./rpn [arguments]\n");
        return 1;
    }

    Stack *stack = myStack(stackSize);


    // iterates over each arg
for (int i = 1; i < argc; i++) {
    if (stringPrefix(argv[i], "0b") || stringPrefix(argv[i], "0x") || (argv[i][0] >= '0' && argv[i][0] <= '9')) {
        unsigned int num = parseArg(argv[i]); // converting the argument to unsigned int
        push(stack, num);


        } 
    
        else if (strcmp(argv[i], "add") == 0) {
                int y = pop(stack), x = pop(stack);
                push(stack, x + y);


        } else if (strcmp(argv[i], "sub") == 0) {
            int y = pop(stack), x = pop(stack);
            push(stack, x - y);


        } else if (strcmp(argv[i], "mult") == 0) {
            int y = pop(stack), x = pop(stack);
            push(stack, x * y);

        } else if (strcmp(argv[i], "div") == 0) {
            int y = pop(stack), x = pop(stack);

            if (y == 0) {
                // error handling 
                printf("Error: Division by zero.\n");
                freeStack(stack);
                return 1;
            }

            push(stack, x / y);

        } else {

            printf("Unknown argument: %s\n", argv[i]);
            freeStack(stack);
            return 1;

        }
    }

    if (!emptyStack(stack)) {

        printf("%d\n", pop(stack));

    } else {
        printf("Error: Stack is empty.\n");
    }

    freeStack(stack);

    return 0;
}
