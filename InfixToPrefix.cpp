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

int score(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}

/*  Test Case
    (4+2)+(3*(5-1))     -> 42+351-*+
    4*(5-(7+2))         -> 4572+-*
    ((3+4)*2)/7         -> 34+2*7/
    2+5*3               -> 253*+
    2*5+3               -> 25*3+
*/

int main()
{
    int i, j, k;
    int num, a, b;
    int operandCount = 0, operatorCount = 0;

    char op;
    char output[100], operators[100];
    char string[] = "(A-(B*(C+D))-E/F)";

    j = -1;
    k = -1;
    for(i = strlen(string) - 1; i >= 0; i--) {
        if (string[i] >= '0' && string[i] <= '9' || string[i] >= 'A' && string[i] <= 'Z') {
            j++;
            output[j] = string[i];
        } else if (string[i] == '(') {
            while (operators[k] != ')') {
                j++;
                output[j] = operators[k];
                operators[k] = '\0';
                k--;
            }
            operators[k] = '\0';
            k--;
        } else {
            if (string[i] == '+' || string[i] == '-' || string[i] == '*' || string[i] == '/') {
                if (j != -1 && score(operators[k]) >= score(string[i])) {
                    j++;
                    output[j] = operators[k];
                    operators[k] = string[i];
                } else {
                    k++;
                    operators[k] = string[i];
                }
            } else {
                k++;
                operators[k] = string[i];
            }
        }
    }
    while (k != -1) {
        j++;
        output[j] = operators[k];
        k--;
    }

    int l, m;
    char finalOutput[100] = "\0";

    m = 0;
    for (l = strlen(output) - 1; l >= 0; l--) {
        finalOutput[m] = output[l];
        m++;
    }

    printf ("%s\n", finalOutput);
    max = strlen(finalOutput) + 10;

    for (i = strlen(finalOutput) - 1; i >= 0; i--) {
        if (finalOutput[i] >= '0' && finalOutput[i] <= '9') {
            num = finalOutput[i] - '0';
            push(num);
            operandCount++; 
        } else if (finalOutput[i] == '+' || finalOutput[i] == '-' || finalOutput[i] == '*' || finalOutput[i] == '/') {
            op = finalOutput[i];
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
                push(a + b);
                break;
            
            case '-':
                a = top->num;
                b = top->next->num;
                pop();
                pop();
                push(a - b);
                break;

            case '*':
                a = top->num;
                b = top->next->num;
                pop();
                pop();
                push(a * b);
                break;

            case '/':
                a = top->num;
                b = top->next->num;
                pop();
                pop();
                push(a / b);
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
