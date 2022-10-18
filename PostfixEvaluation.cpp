/* 
2440021376_Denzel Caesarian Iswanto Suhardjo
LI01 - Data Structure (COMP6048)

Topic   : Postfix Evaluation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count = -1, max;

struct Stack {
    int num;
    Stack* next;
} *top;

Stack* createNewStack(int num) {
    Stack* newStack = (Stack*) malloc(sizeof(Stack));
    newStack->num = num;
    newStack->next = NULL;

    return newStack;
}

void push(int num) {
    if (count == max - 1) {
        printf ("Stack Full!\n");
        return;
    } else {
        if (top == NULL) {
            Stack* newStack = createNewStack(num);
            top = newStack;
        } else {
            Stack* newStack = createNewStack(num);
            newStack->next = top;
            top = newStack;
        }
        count++;
    }
}

void pop() {
    if (count == -1) {
        printf ("Stack Empty!\n");
        return;
    } else {
        Stack* tobeDeleted = top;
        top = top->next;
        tobeDeleted->next = NULL;
        tobeDeleted = NULL;
        free(tobeDeleted);

        count--;
    }
}

void print() {
    printf ("Result : %d\n", top->num);
}

int main()
{
    int i, num, a, b;
    int operandCount = 0, operatorCount = 0;
    char op;
    char string[] = "4572+-*";

    max = strlen(string) + 10;

    for (i = 0; i < strlen(string); i++) {
        if (string[i] >= '0' && string[i] <= '9') {
            num = string[i] - '0';
            push(num);
            operandCount++;
        } else if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/') {
            op = string[i];
            operatorCount++;

            if (operatorCount >= operandCount) {
                break;
            }

            switch (op)
            {
            case '+':
                a = top->num;
                b = top->next->num;
                pop();
                pop();
                push(b + a);
                break;
            
            case '-':
                a = top->num;
                b = top->next->num;
                pop();
                pop();
                push(b - a);
                break;

            case '*':
                a = top->num;
                b = top->next->num;
                pop();
                pop();
                push(b * a);
                break;

            case '/':
                a = top->num;
                b = top->next->num;
                pop();
                pop();
                push(b / a);
                break;
            }
        }
    }

    if (operatorCount == operandCount - 1) {
        print();
    } else if (operatorCount < operandCount - 1) {
        printf ("Too many Operand!\n");
    } else if (operatorCount >= operandCount) {
        printf ("Not enough Operand!\n");
    }

    return 0;
}