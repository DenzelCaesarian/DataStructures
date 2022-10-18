/* 
2440021376_Denzel Caesarian Iswanto Suhardjo
LI01 - Data Structure (COMP6048)

Topic   : Stack Array
*/

#include <stdio.h>
#include <stdlib.h>

int stack[100], top, capacity, total;

void push(int bookCode) {
    if (top == capacity - 1) {
        printf ("Stack Full!\n");
        return;
    } else {
        top++;
        stack[top] = bookCode;

        printf ("%d successfully inputed!\n", bookCode);

        total++;
    }
}

void pop() {
    if (top == -1) {
        printf ("Stack Empty!\n");
        return;
    } else {
        top--;

        total--;
    }
}

int peek() {
    return stack[top];
}

void print() {
    if (top == -1) {
        printf ("No Data!\n");
        return;
    } else {
        int i;
    
        for (i = total - 1; i >= 0; i--) {
            printf ("%d -> %d\n", stack[i], i);
        }
    }
}

int main() 
{
    int choice, bookCode;
    
    printf ("Input Maximum Capacity: ");
    scanf ("%d", &capacity);

    top = -1;

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
            if (top == -1) {
                printf ("No Data!\n");
            } else {
                printf ("Top Element: %d\n", peek());
            }
            break;

        case 5:
            break;
            
        default:
            printf ("Wrong Input! Try Again.\n");
            break;
        }
    }
    return 0;
}