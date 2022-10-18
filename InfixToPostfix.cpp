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
    1+2*8/4-9+4*2       -> 128*4/9-42*++
*/

int main()
{
    int i, j, k;
    int num, a, b;
    int operandCount = 0, operatorCount = 0;

    char op;
    char output[100], operators[100];
    char string[] = "1+7*5";

    j = -1;
    k = -1;
    for(i = 0; i < strlen(string); i++) {
        if (string[i] >= '0' && string[i] <= '9') {
            j++;
            output[j] = string[i];
        } else if (string[i] == ')') {
            while (operators[k] != '(') {
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
    
    printf("%s\n", output);
    max = strlen(output) + 10;

    for (i = 0; i < strlen(output); i++) {
        if (output[i] >= '0' && output[i] <= '9') {
            num = output[i] - '0';
            push(num);
            operandCount++;
        } else if (output[i] == '+' || output[i] == '-' || output[i] == '*' || output[i] == '/') {
            op = output[i];
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
