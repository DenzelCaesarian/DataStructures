#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Song 
{
    int priority;
    char title[250];
    Song* next;
    Song* prev;
} *head, *tail;

Song* createData(int priority, char title[250])
{
    Song* newData = (Song*)malloc(sizeof(Song));

    newData->priority = priority;
    strcpy(newData->title, title);
    newData->next = NULL;
    newData->prev = NULL;

    return newData;
}

bool checkTitle(char title[250])
{
    Song* current = head;

    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            return true;
            break;
        }
        current = current->next;
    }
    return false;
}

void addSong(int priority, char title[250])
{
    if (head == NULL) {
        Song* newData = createData(priority, title);
        head = tail = newData;
    } else {
        if (checkTitle(title)) {
            printf ("Song already in List!\n");
        } else {
            Song* newData = createData(priority, title);

            if (newData->priority >= head->priority) {
                newData->next = head;
                head->prev = newData;
                head = newData;
            } else if (newData->priority < tail->priority) {
                newData->prev = tail;
                tail->next = newData;
                tail = newData;
            } else {
                Song* current = head;

                while (current->next->priority != priority) {
                    current = current->next;
                }

                newData->next = current->next;
                newData->prev = current;
                newData->next->prev = newData;
                current->next = newData;
            }
        }
    }
}

void playSong()
{
    Song* temp = tail;

    tail = temp->prev;
    tail->next = NULL;
    temp->prev = NULL;
    temp = NULL;

    free(temp);
}

void viewList()
{
    if (head == NULL) {
        printf ("No Song in the Queue!\n");
    } else {
        Song* current = head;

        while (current != NULL) {
            printf ("%d - %s\n", current->priority, current->title);
            current = current->next;
        }
    }
}

int main()
{
    addSong(2, "Repeatedly");
    addSong(2, "All I Want");
    addSong(3, "Cinta Tanpa Tapi");
    addSong(1, "Trust Again");
    addSong(3, "Fall on Me");
    addSong(1, "Lead the Way");
    addSong(2, "All I Want");
    viewList();
    printf ("====================\n");
    playSong();
    viewList();
    printf ("====================\n");
    addSong(1, "Broken Vow");
    addSong(1, "Trust Again");
    viewList();
    return 0;
}