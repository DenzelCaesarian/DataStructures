#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define SIZE 256

struct Monster {
    char monsterID[10];
    char monsterName[100];
    char monsterType[100];
    double monsterSize;
    char monsterLocation[200];
    Monster* next;
    Monster* prev;
};

Monster* head[SIZE];
Monster* tail[SIZE];

Monster* makeData (char monsterID[], char monsterName[], char monsterType[], double monsterSize, char monsterLocation[])
{
    Monster* newData = (Monster*)malloc(sizeof(Monster));

    strcpy(newData->monsterID, monsterID);
    strcpy(newData->monsterName, monsterName);
    strcpy(newData->monsterType, monsterType);
    newData->monsterSize = monsterSize;
    strcpy(newData->monsterLocation, monsterLocation);
    newData->next = NULL;
    newData->prev = NULL;

    return newData;
}

bool isvalidName (char name[])
{
    char firstLetter = name[0];
    return (strlen(name) >= 3 && strlen(name) <= 20) && (toupper(firstLetter) == firstLetter);
}

bool isvalidType (char type[])
{
    return (strcmp(type, "Large") == 0 || strcmp(type, "Small") == 0 || strcmp(type, "Endemic") == 0 || strcmp(type, "Pets") == 0);
}

bool isvalidSize (double size)
{
    return size >= 100 && size <= 5000;
}

bool isvalidLocation (char location[])
{
    char string[] = " Biome";
    int i, j, len1, len2, start;

    len1 = strlen(location);
    len2 = strlen(string);

    start = len1 - len2;

    for (i = start, j = 0; i < len1; i++, j++) {
        if (location[i] != string[j]) {
            return false;
        } 
    }

    return true;
}

int hashValue (char monsterID[]) 
{
    int i, sum;

    sum = 0;
    for (i = 0; i < strlen(monsterID); i++) {
        sum += monsterID[i];
    }

    return sum % SIZE;
}

void insertNewMonster () 
{
    char monsterID[10];
    char monsterName[100];
    char monsterType[100];
    double monsterSize;
    char monsterLocation[200];
    
    do {
        printf ("Input monster name [3 - 20 character & starts with Capital Letter]: ");
        scanf ("%[^\n]", monsterName);
        getchar();
    } while (!isvalidName(monsterName));

    do {
        printf ("Input monster type [Large | Small | Endemic | Pets] (case sensitive): ");
        scanf ("%[^\n]", monsterType);
        getchar();
    } while (!isvalidType(monsterType));

    do {
        printf ("Input monster size [100.0 - 5000.0] (inclusive): ");
        scanf ("%lf", &monsterSize);
        getchar();
    } while (!isvalidSize(monsterSize));

    do {
        printf ("Input monster location [endswith ' Biome'] (case sensitive): ");
        scanf ("%[^\n]", monsterLocation);
        getchar();
    } while (!isvalidLocation(monsterLocation));

    int i;
    for (i = 0; i < 3; i++) {
        monsterID[i] = toupper(monsterName[i]);
    }
    for (i = 3; i < 6; i++) {
        monsterID[i] = rand() % 10 + '0';
    }
    printf ("Monster ID: %s\n", monsterID);

    int key;
    Monster* newData = makeData(monsterID, monsterName, monsterType, monsterSize, monsterLocation);
    key = hashValue(monsterID);

    if (head[key] == NULL) {
        head[key] = tail[key] = newData;
    } else {
        tail[key]->next = newData;
        newData->prev = tail[key];
        tail[key] = newData;
    }

    printf ("New monster successfully added!\n");
    printf ("Press enter to continue...\n");
    getchar();
}

void printMonster ()
{
    int i;

    for (i = 0; i < SIZE; i++) {
        if (head[i] != NULL) {
            Monster* temp = head[i];
            
            printf ("==========================\n");
            printf ("[%d]\n", i);
            while (temp != tail[i]) {
                printf ("ID         : %s\n", temp->monsterID);
                printf ("Name       : %s\n", temp->monsterName);
                printf ("Type       : %s\n", temp->monsterType);
                printf ("Size       : %.2lf\n", temp->monsterSize);
                printf ("Location   : %s\n", temp->monsterLocation);
                printf ("--------------------------\n");
                temp = temp->next;
            }
            printf ("ID         : %s\n", temp->monsterID);
            printf ("Name       : %s\n", temp->monsterName);
            printf ("Type       : %s\n", temp->monsterType);
            printf ("Size       : %.2lf\n", temp->monsterSize);
            printf ("Location   : %s\n", temp->monsterLocation);
            printf ("==========================\n");
        }
    }
}

void deleteMonster ()
{
    printMonster();
    char tobeDeletedID[10];

    printf ("Input monster ID to remove: ");
    scanf ("%[^\n]", tobeDeletedID);

    int key = hashValue(tobeDeletedID);

    if (head[key] == NULL) {
        printf ("Monster not found...\n");
    } else {
        if (strcmp(head[key]->monsterID, tobeDeletedID) == 0) {
            if (head[key]->next == NULL) {
                head[key]->next = NULL;
                head[key]->prev = NULL;
                
                head[key] = tail[key] = NULL;
                free (head[key]);
            } else {
                Monster* tobeDeleted;

                tobeDeleted = head[key];
                head[key] = tobeDeleted->next;
                head[key]->prev = NULL;
                tobeDeleted->next = NULL;

                tobeDeleted = NULL;
                free (tobeDeleted);
            }
        } else if (strcmp(tail[key]->monsterID, tobeDeletedID) == 0) {
            Monster* tobeDeleted;

            tobeDeleted = tail[key];
            tail[key] = tobeDeleted->prev;
            tail[key]->next = NULL;
            tobeDeleted->prev = NULL;

            tobeDeleted = NULL;
            free (tobeDeleted);
        } else {
            int status;
            Monster* temp = head[key];
            Monster* tobeDeleted;

            status = 0;
            while (strcmp(temp->next->monsterID, tobeDeletedID) != 0) {
                temp = temp->next;
                if (temp->next == tail[key] && strcmp(temp->monsterID, tobeDeletedID) != 0) {
                    status = 1;
                    break;
                }
            }

            if (status == 1) {
                printf ("Monster not found...\n");
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
    printf ("Monster successfully deleted!\n");
    printf ("Press enter to continue...\n");
    getchar();
}

void updateMonster ()
{
    printMonster();
    char tobeUpdatedID[10];
    Monster* tobeUpdated;

    printf ("Input monster ID to update: ");
    scanf ("%[^\n]", tobeUpdatedID);
    getchar();

    int key = hashValue(tobeUpdatedID);

    if (head[key] == NULL) {
        printf ("Monster not found...\n");
        return;
    } else {
        if (strcmp(head[key]->monsterID, tobeUpdatedID) == 0) {
            tobeUpdated = head[key];
        } else if (strcmp(tail[key]->monsterID, tobeUpdatedID) == 0) {
            tobeUpdated = tail[key];
        } else {
            int status;
            Monster* temp = head[key];

            status = 0;
            while (strcmp(temp->next->monsterID, tobeUpdatedID) != 0) {
                temp = temp->next;
                if (temp->next == tail[key] && strcmp(temp->monsterID, tobeUpdatedID) != 0) {
                    status = 1;
                    break;
                }
            }

            if (status == 1) {
                printf ("Monster not found...\n");
            } else {
                tobeUpdated = temp->next;
            }
        }
    }

    printf ("[Input 0 to skip update]\n");

    char monsterID[10];
    char monsterName[100];
    char monsterType[100];
    double monsterSize;
    char monsterLocation[200];
    
    do {
        printf ("Input monster name [3 - 20 character & starts with Capital Letter]: ");
        scanf ("%[^\n]", monsterName);
        getchar();

        if (strcmp(monsterName, "0") == 0) {
            break;
        }
    } while (!isvalidName(monsterName));

    do {
        printf ("Input monster type [Large | Small | Endemic | Pets] (case sensitive): ");
        scanf ("%[^\n]", monsterType);
        getchar();
        if (strcmp(monsterType, "0") == 0) {
            break;
        }
    } while (!isvalidType(monsterType));

    do {
        printf ("Input monster size [100.0 - 5000.0] (inclusive): ");
        scanf ("%lf", &monsterSize);
        getchar();
        if (monsterSize == 0) {
            break;
        }
    } while (!isvalidSize(monsterSize));

    do {
        printf ("Input monster location [endswith ' Biome'] (case sensitive): ");
        scanf ("%[^\n]", monsterLocation);
        getchar();
        if (strcmp(monsterLocation, "0") == 0) {
            break;
        }
    } while (!isvalidLocation(monsterLocation));

    if (strcmp(monsterName, "0") != 0) {
        printf ("%s\n", monsterName);
        strcpy(tobeUpdated->monsterName, monsterName);
    }

    if (strcmp(monsterType, "0") != 0) {
        strcpy(tobeUpdated->monsterType, monsterType);
    }

    if (monsterSize != 0) {
        tobeUpdated->monsterSize = monsterSize;
    }

    if (strcmp(monsterLocation, "0") != 0) {
        strcpy(tobeUpdated->monsterLocation, monsterLocation);
    }

    printf ("Monster successfully updated!\n");
    printf ("Press enter to continue...\n");
    getchar();
}

int main ()
{
    srand(time(NULL));

    int chooseCode;

    do {
        printf ("==========================\n");
        printf ("<< Monster Encyclopedia >>\n");
        printf ("==========================\n");
        printf ("1. Insert New Monster\n");
        printf ("2. Change Monster Data\n");
        printf ("3. Remove Monster\n");
        printf ("4. Close Book\n");

        do {
            printf ("Choose: ");
            scanf ("%d", &chooseCode);
            getchar();
        } while (chooseCode < 1 || chooseCode > 4);

        switch (chooseCode)
        {
        case 1:
            insertNewMonster();
            printMonster();
            break;
        
        case 2:
            updateMonster();
            printMonster();
            break;

        case 3:
            deleteMonster();
            printMonster();
            break;
        }

    } while (chooseCode != 4);
    printf ("Thank you for using monster book!\n");

    return 0;
}