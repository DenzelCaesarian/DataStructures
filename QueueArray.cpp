/* 
2440021376_Denzel Caesarian Iswanto Suhardjo
LI01 - Data Structure (COMP6048)

Topic   : Queue Array
*/

#include <stdio.h>
#include <stdlib.h>

int stack[100], front, rear, capacity, total;

void enqueue(int bookCode) {
    if (total == capacity - 1) {
        printf ("Queue Full!\n");
        return;
    } else {
        stack[rear] = bookCode;
        rear++;

        printf ("%d successfully inputed!\n", bookCode);

        total++;
    }
}

void dequeue() {
    if (total == -1) {
        printf ("Queue Empty!\n");
        return;
    } else {
        front++;

        total--;
    }
}

void print() {
    if (total == -1) {
        printf ("No Data!\n");
        return;
    } else {
        int i;
    
        for (i = rear - 1; i >= front; i--) {
            printf ("%d", stack[i]);

            if (i != front) {
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
    scanf ("%d", &capacity);

    rear = 0;
    front = 0;
    total = -1;

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