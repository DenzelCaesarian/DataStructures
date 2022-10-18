#include <stdio.h>
#include <stdlib.h>

int count = -1, max;

struct Stack {
    int code;
    Stack* next;
} *top, *front, *rear;

Stack* createNewStack(int code) {
    Stack* newStack = (Stack*) malloc(sizeof(Stack));
    newStack->code = code;
    newStack->next = NULL;

    return newStack;
}

void enqueue(int code) {
    if (count == max - 1) {
        printf ("Queue Full!\n");
        return;
    } else {
        if (front == NULL) {
            Stack* newStack = createNewStack(code);
            front = rear = newStack;
        } else {
            Stack* newStack = createNewStack(code);
            newStack->next = rear;
            rear = newStack;
        }
        count++;
    }
}

void dequeue() {
    if (count == -1) {
        printf ("Queue Empty!\n");
        return;
    } else {
        if (count == 0) {
            front = rear = NULL;
            count--;
        } else {
            Stack* temp = rear;

            while (temp->next != front) {
                temp = temp->next;
            }

            Stack* tobeDeleted = temp->next;
            front = temp;
            front->next = NULL;
            tobeDeleted = NULL;
            free(tobeDeleted);

            count--;
        }
    }
}

void print() {
    if (count == -1) {
        printf ("No Data!\n");
        return;
    } else {
        int i;

        Stack* currentData = rear;
        for (i = 0; i <= count; i++) {
            printf ("%d", currentData->code);
            currentData = currentData->next;

            if (currentData != NULL) {
                printf (" -> ");
            }
        }
        printf("\n");
    }
}

int main()
{
    int choice, bookCode;
    
    printf ("Input Maximum Capacity: ");
    scanf ("%d", &max);

    while (choice != 4) {
        printf ("What do you want to do?\n");
        printf ("1. Add\n");
        printf ("2. Delete\n");
        printf ("3. Print\n");
        printf ("4. End\n");
        printf ("Input Choice: ");
        scanf ("%d", &choice);
        
        switch (choice)
        {
        case 1:
            printf ("Input Book Code: ");
            scanf ("%d", &bookCode);

            enqueue(bookCode);
            break;

        case 2:
            dequeue();
            break;
        
        case 3:
            print();
            break;

        case 4:
            break;
            
        default:
            printf ("Wrong Input! Try Again.");
            break;
        }
    }

    return 0;
}
