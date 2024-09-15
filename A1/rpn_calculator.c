// Written by Rabia Ghafoor 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// imports 

#define stackSize 10

// storing 10 integers as per the requirement

typedef struct {
    int *data, top, capacity;
} 
Stack;

// Stack function
Stack* myStack(int capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack-> data = (int *)malloc(capacity * sizeof(int));
    stack-> top = -1;
    stack-> capacity = capacity;


    return stack; // returning hte stack
}


void freeStack(Stack *stack) {
    free(stack  ->  data);
    free(stack);
}

// checking if the stack is empty or not 
int emptyStack(Stack * stack) {
    return stack->top == -1;
}

// checking if the stack is full or not 

int isFull(Stack * stack) {
    return stack->top == stack -> capacity - 1;
}


// push operatoins

void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Additonal values can't be added.\n");
        exit(1);
    }
    stack->data[++(stack->top)] = value;
}

int pop(Stack *stack) {
    if (emptyStack(stack)) {
        printf(" No values are left to pop.\n");
        exit(1);
    }
    return stack->data[(stack->top)--];
}

//checking if a string is a number
int isNum(char *arg) {
    char *endptr;
    strtol(arg, &endptr, 10);
    return *endptr == '\0';
}

int main(int argc, char  *argv[]) {
    if (argc < 2) {
        printf(" ./rpn [arguments]\n");
        return 1;
    }

    Stack *stack = myStack(stackSize);

    for (int i = 1; i <   argc; i++) {
        if (isNum(argv[i])) {

            int num = (int)strtol(argv[i], NULL, 10);
            push(stack, num);

        } else if (strcmp(argv[i], "add") == 0) {

            int y = pop(stack), x = pop(stack);

            push(stack, x + y); // add operation




        } else if (strcmp(argv[i], "sub") == 0) {
            int y = pop(stack);
            int x = pop(stack);
            push(stack, x - y); // substract operation
        


        } else if (strcmp(argv[i], "mult") == 0) {
            int y = pop(stack), x = pop(stack);
            push(stack, x * y); // product operation


        } else if (strcmp(argv[i], "div") == 0) { // division by 0
            int y = pop(stack), x = pop(stack);


            if (y == 0) {
                printf("Error: Division by zero.\n");
                freeStack(stack);
                return 1;
            }
            push(stack, x / y); // divioson operation
        } else {
            printf("Unknown argument: %s\n", argv[i]);
            freeStack(stack);
            return 1;
        }
    }

    // prints the result from the top of the stack
    if (!emptyStack(stack)) { 
        printf("%d\n", pop(stack));
    } else {
        printf(" Error .\n");
    }

    freeStack(stack);
    return 0;
}
