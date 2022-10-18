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

    return newData;
}

void pushHead (int num) {
    if (head == NULL) {
        LinkedList* newData = createNewData(num);
        head = tail = newData;
        head->next = tail;
        head->prev = tail;
        tail->next = head;
        tail->prev = head;
    } else {
        LinkedList* newData = createNewData(num);
        head->prev = newData;
        newData->next = head;
        newData->prev = tail;
        head = newData;
    }
    totalData++;
}

void pushTail (int num) {
    if (head == NULL) {
        LinkedList* newData = createNewData(num);
        head = tail = newData;
        head->next = tail;
        head->prev = tail;
        tail->next = head;
        tail->prev = head;
    } else {
        LinkedList* newData = createNewData(num);
        newData->prev = tail;
        tail->next = newData;
        newData->next = head;
        head->prev = newData;
        tail = newData;
    }
    totalData++;
}

void pushMid (int num, int position) {
    if (head == NULL) {
        LinkedList* newData = createNewData(num);
        head = tail = newData;
        head->next = tail;
        head->prev = tail;
        tail->next = head;
        tail->prev = head;
    } else {
        int count = 1;
        LinkedList* temp = head;
        while (count != position - 1) {
            temp = temp->next;
            count++;
        }

        LinkedList* newData = createNewData(num);
        newData->next = temp->next;
        temp->next->prev = newData;
        newData->prev = temp;
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
        head->prev = tail;
        tail->next = head;
        temp->next = NULL;
        temp->prev = NULL;
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
        tail->next = head;
        head->prev = tail;
        temp->next = NULL;
        temp->prev = NULL;
        temp = NULL;

        free(temp);
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
        printf ("%d, Prev: %d, Next: %d\n", currentData->data, currentData->prev->data, currentData->next->data);
        currentData = currentData->next;
        count++;
    }
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

int main()
{
    pushHead(1);
    pushTail(2);
    pushHead(3);
    pushTail(4);
    pushHead(5);
    pushTail(6);
    pushHead(7);
    pushTail(8);
    pushMid(9, 2);
    pushMid(10, 9);
    popHead();
    popTail();
    popMid(5);
    popMid(6);

    /*  Output Seharusnya :
        9, Prev: 10, Next: 5
        5, Prev: 9, Next: 3
        3, Prev: 5, Next: 1
        1, Prev: 3, Next: 4
        4, Prev: 1, Next: 10
        10, Prev: 4, Next: 9
    */

    printData();
    return 0;
}