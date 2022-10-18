#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

struct Data 
{
    int number;
    Data* next;
    Data* prev;
};

Data* head[SIZE];
Data* tail[SIZE];

Data* makeData (int number)
{
    Data* newData = (Data*)malloc(sizeof(Data));
    newData->number = number;
    newData->next = NULL;
    newData->prev = NULL;

    return newData;
}

int divisionHashing (int number)
{
    return number % SIZE;
}

int midSquareHashing (int number)
{
    char string[100];
    int i, j, digit, key;
    long long int square;

    square = number * number;
    sprintf (string, "%lld", square);
    digit = strlen(string);

    if (digit % 2 == 0) {
        if (digit == 2) {
            key = square % SIZE;
        } else {
            j = 0;
            i = (digit - 2) / 2;

            for (j = 0; j < i; j++) {
                square /= 10;
            }
            key = (square % 100) % SIZE;
        }
    } else {
        if (digit == 1) {
            key = square % SIZE;
        } else {
            j = 0;
            i = (digit - 1) / 2;

            for (j = 0; j < i; j++) {
                square /= 10;
            }
            key = (square % 10) % SIZE;
        }
    }

    return key;
}

int foldingHashing (int number)
{
    long long int sum;
    char string[100], temp[100];
    int i, j, k, digit, count, value[25];

    sprintf (string, "%d", number);
    digit = strlen(string);

    sum = 0;
    count = 0;
    if (digit < 2) {
        for (i = 0; i < digit; i++) {
            sum += string[i] - '0';
        }
    } else {
        j = 0;
        k = 0;
        for (i = 0; i < digit; i++) {
            count++;
            temp[j] = string[i];
            j++;

            if (count == 3) {
                value[k] = atoi(temp);
                temp[0] = '\0';
                temp[1] = '\0';
                temp[2] = '\0';
                j = 0;
                k++;
                count = 0;
            } else if (count < 3 && i == digit - 1) {
                value[k] = atoi(temp);
                j = 0;
                k++;
            }
        }

        for (i = 0; i < k; i++) {
            sum += value[i];
        }
    }

    return sum;
}

void insertData (int number) 
{
    int key = divisionHashing(number);

    if (head[key] == NULL) {
        Data* newData = makeData(number);
        head[key] = tail[key] = newData;
    } else {
        Data* newData = makeData(number);
        tail[key]->next = newData;
        newData->prev = tail[key];
        tail[key] = newData;
    }
}

void deleteData (int number)
{
    int key = divisionHashing(number);

    if (head[key] == NULL) {
        printf ("No Data\n");
    } else {
        if (head[key]->number == number) {
            if (head[key]->next == NULL) {
                head[key]->next = NULL;
                head[key]->prev = NULL;
                
                head[key] = tail[key] = NULL;
                free (head[key]);
            } else {
                Data* tobeDeleted;

                tobeDeleted = head[key];
                head[key] = tobeDeleted->next;
                head[key]->prev = NULL;
                tobeDeleted->next = NULL;

                tobeDeleted = NULL;
                free (tobeDeleted);
            }
        } else if (tail[key]->number == number) {
            Data* tobeDeleted;

            tobeDeleted = tail[key];
            tail[key] = tobeDeleted->prev;
            tail[key]->next = NULL;
            tobeDeleted->prev = NULL;

            tobeDeleted = NULL;
            free (tobeDeleted);
        } else {
            int status;
            Data* temp = head[key];
            Data* tobeDeleted;

            status = 0;
            while (temp->next->number != number) {
                temp = temp->next;
                if (temp->next == tail[key] && temp->number != number) {
                    status = 1;
                    break;
                }
            }

            if (status == 1) {
                printf ("No Data\n");
            } else {
                tobeDeleted = temp->next;
                temp->next = tobeDeleted->next;
                tobeDeleted->next->prev = temp;
                tobeDeleted->next = NULL;
                tobeDeleted->prev = NULL;

                tobeDeleted = NULL;
                free (tobeDeleted);
            }
        }
    }
}

void printData ()
{
    int i;

    for (i = 0; i < SIZE; i++) {
        if (head[i] == NULL) {
            printf ("[%d] null\n", i);
        } else {
            Data* temp = head[i];
            
            printf ("[%d]", i);
            while (temp != tail[i]) {
                printf (" %d ||", temp->number);
                temp = temp->next;
            }
            printf (" %d\n", tail[i]->number);
        }
    }
}

int main () 
{
    insertData(10);
    insertData(20);
    insertData(30);
    insertData(25);
    insertData(1);
    insertData(8);
    insertData(94);
    insertData(78);
    deleteData(25);

    printf ("%d\n", foldingHashing(21017));
    printf ("Mod %d\n", foldingHashing(21017) % 1000);
    return 0;
}