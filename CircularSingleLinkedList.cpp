#include <stdio.h>
#include <stdlib.h>

struct LinkedList {
    int data;
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
        tail->next = head;
    } else {
        LinkedList* newData = createNewData(num);
        newData->next = head;
        head = newData;
    }
    totalData++;
}

void pushTail (int num) {
    if (head == NULL) {
        LinkedList* newData = createNewData(num);
        head = tail = newData;
        head->next = tail;
        tail->next = head;
    } else {
        LinkedList* newData = createNewData(num);
        tail->next = newData;
        tail = newData;
        tail->next = head;
    }
    totalData++;
}

void pushMid (int num, int position) {
    if (head == NULL) {
        LinkedList* newData = createNewData(num);
        head = tail = newData;
        head->next = tail;
        tail->next = head;
    } else {
        int count = 1;
        LinkedList* temp = head;
        while (count != position - 1) {
            temp = temp->next;
            count++;
        }

        LinkedList* newData = createNewData(num);
        newData->next = temp->next;
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
        tail->next = head;
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
        LinkedList* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }

        tail = temp;
        temp = tail->next;
        tail->next = head;
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
        printf ("%d, Next: %d\n", currentData->data, currentData->next->data);
        currentData = currentData->next;
        count++;
    }
}

int main()
{
    pushHead(1);
    pushHead(2);
    pushHead(3);
    pushHead(4);
    pushTail(5);
    pushTail(6);
    pushTail(7);
    pushTail(8);
    pushMid(9,3);
    pushMid(10,4);
    pushMid(11,9);
    pushMid(12,10);
    popHead();
    popTail();
    popMid(5);
    popMid(6);

    /*  Output Seharusnya :
        3, Next: 9
        9, Next: 10
        10, Next: 2
        2, Next: 5
        5, Next: 11
        11, Next: 12
        12, Next: 7
        7, Next: 3
    */

    printData();
    return 0;
}