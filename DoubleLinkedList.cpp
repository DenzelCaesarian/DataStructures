#include <stdio.h>
#include <stdlib.h>

struct LinkedList {
    int data;
    LinkedList* prev;
    LinkedList* next;
} *head, *tail;

int totalData = 0;

LinkedList* createNewData (int num) {
    LinkedList* newData = (LinkedList*) malloc(sizeof(LinkedList));

    newData->data = num;
    newData->next = NULL;
    newData->prev = NULL;

    return newData;
}

void pushHead (int num) {
    if (head == NULL) {
        LinkedList* newData = createNewData(num);
        head = tail = newData;
    } else {
        LinkedList* newData = createNewData(num);
        head->prev = newData;
        newData->next = head;
        head = newData;
    }
    totalData++;
}

void pushTail (int num) {
    if (head == NULL) {
        LinkedList* newData = createNewData(num);
        head = tail = newData;
    } else {
        LinkedList* newData = createNewData(num);
        newData->prev = tail;
        tail->next = newData;
        tail = newData;
    }
    totalData++;
}

void pushMid (int num, int position) {
    if (head == NULL) {
        LinkedList* newData = createNewData(num);
        head = tail = newData;
    } else {
        int count = 1;
        LinkedList* temp = head;
        while (count != position - 1) {
            temp = temp->next;
            count++;
        }

        LinkedList* newData = createNewData(num);
        newData->next = temp->next;
        newData->prev = temp;
        temp->next->prev = newData;
        temp->next = newData;
    }
    totalData++;
}

void popHead () {
    if (head == NULL) {
        printf ("No Data\n");
        return;
    } else {
        LinkedList* temp = head;
        head = head->next;
        head->prev = NULL;
        temp->next = NULL;
        temp = NULL;

        free(temp);
    }
    totalData--;
}

void popTail () {
    if (head == NULL) {
        printf ("No Data\n");
        return;
    } else {
        LinkedList* temp = tail->prev;
        tail = temp;
        temp = tail->next;
        tail->next = NULL;
        temp->prev = NULL;
        temp->next = NULL;
        temp = NULL;

        free(temp);
    }
    totalData--;
}

void popMid (int position) {
    if (head == NULL) {
        printf ("No Data\n");
        return;
    } else {
        int count = 1;
        LinkedList* temp = head;
        while (count != position - 1) {
            temp = temp->next;
            count++;
        }

        LinkedList* tobeDeleted = temp->next;
        temp->next = tobeDeleted->next;
        tobeDeleted->next->prev = temp;
        tobeDeleted->prev = NULL;
        tobeDeleted->next = NULL;
        tobeDeleted = NULL;

        free(tobeDeleted);
    }
    totalData--;
}

void printData () {
    if (head == NULL) {
        printf ("No Data\n");
        return;
    }
    int count = 0;
    LinkedList* currentData = head;
    while (count != totalData) {
        printf ("%d", currentData->data);
        currentData = currentData->next;
        count++;

        if (count != totalData) {
            printf (" -><- ");
        }
    }
}

int main()
{
    pushHead(1);
    pushHead(2);
    pushTail(3);
    pushTail(4);
    pushHead(5);
    pushHead(6);
    pushTail(7);
    pushTail(8);
    pushMid(9, 5);
    pushMid(10, 6);
    popHead();
    popTail();
    popMid(5);
    popMid(6);

    /*  Output Seharusnya :
        NULL <- 5 -><- 2 -><- 1 -><- 9 -><- 3 -><- 7 -> NULL
    */

    printf ("NULL <- ");
    printData();
    printf (" -> NULL\n");

    return 0;
}