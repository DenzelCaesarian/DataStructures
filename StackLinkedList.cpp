#include <stdio.h>
#include <stdlib.h>

int count = -1, max;

struct Stack {
    int code;
    Stack* next;
} *top;

Stack* createNewStack(int code) {
    Stack* newStack = (Stack*) malloc(sizeof(Stack));
    newStack->code = code;
    newStack->next = NULL;

    return newStack;
}

void push(int code) {
    if (count == max - 1) {
        printf ("Stack Full!\n");
        return;
    } else {
        if (top == NULL) {
            Stack* newStack = createNewStack(code);
            top = newStack;
        } else {
            Stack* newStack = createNewStack(code);
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

int peek() {
    return top->code;
}

void print() {
    if (count == -1) {
        printf ("No Data!\n");
        return;
    } else {
        int i;

        Stack* currentData = top;
        for(i = count; i >= 0; i--) {
            printf ("%d -> %d\n", currentData->code, i);
            currentData = currentData->next;
        }
    }
}

int main()
{
    int choice, bookCode;
    
    printf ("Input Maximum Capacity: ");
    scanf ("%d", &max);

    while (choice != 5) {
        printf ("What do you want to do?\n");
        printf ("1. Push\n");
        printf ("2. Pop\n");
        printf ("3. Print\n");
        printf ("4. Peek\n");
        printf ("5. End\n");
        printf ("Input Choice: ");
        scanf ("%d", &choice);
        
        switch (choice)
        {
        case 1:
            printf ("Input Book Code: ");
            scanf ("%d", &bookCode);

            push(bookCode);
            break;

        case 2:
            pop();
            break;
        
        case 3:
            print();
            break;

        case 4:
            if (count == -1) {
                printf ("No Data!\n");
            } else {
                printf ("Top Element: %d\n", peek());
            }
            break;
        
        case 5:
            break;
            
        default:
            printf ("Wrong Input! Try Again.");
            break;
        }
    }

    return 0;
}
