#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Organization 
{
    int number;
    char name[250];
    char position[250];
    Organization* left;
    Organization* right;
};

Organization* createNewData(int number, char name[], char position[])
{
    Organization* newData = (Organization*)malloc(sizeof(Organization));

    newData->number = number;
    strcpy(newData->name, name);
    strcpy(newData->position, position);
    newData->left = NULL;
    newData->right = NULL;

    return newData;
}

Organization* insertData(Organization* parent, int number, char name[], char position[])
{
    //BST has no data
    if (parent == NULL) {
        return createNewData(number, name, position);
    }

    //BST has parent node
    if (number < parent->number) {
        parent->left = insertData(parent->left, number, name, position);
    } else {
        parent->right = insertData(parent->right, number, name, position);
    }
    
    return parent;
}

void viewDataInOrder(Organization* parent)
{
    if (parent == NULL) {
        return;
    }

    viewDataInOrder(parent->left);
    printf("%d. %s as %s\n", parent->number, parent->name, parent->position);
    viewDataInOrder(parent->right);
}

void viewDataPreOrder(Organization* parent)
{
    if (parent == NULL) {
        return;
    }

    printf("%d. %s as %s\n", parent->number, parent->name, parent->position);
    viewDataPreOrder(parent->left);
    viewDataPreOrder(parent->right);
}

void viewDataPostOrder(Organization* parent)
{
    if (parent == NULL) {
        return;
    }

    viewDataPostOrder(parent->left);
    viewDataPostOrder(parent->right);
    printf("%d. %s as %s\n", parent->number, parent->name, parent->position);
}

Organization* searchData(Organization* parent, int number)
{
    if (parent == NULL) {
        return NULL;
    }

    if (number == parent->number) {
        return parent;
    } else if (number < parent->number) {
        return searchData(parent->left, number);
    } else {
        return searchData(parent->right, number);
    }
}

void updateData(Organization* parent, int number, char name[], char position[])
{
    Organization* search = searchData(parent, number);

    if (search == NULL) {
        printf ("Not Found!\n");
    } else {
        if (strcmp(name, "0") != 0) {
            strcpy(search->name, name);
        } 
        if (strcmp(position, "0") != 0) {
            strcpy(search->position, position);
        } 
    }
}

Organization* findPredecessor(Organization* root)
{
    Organization* current = root;
    while (current && current->right != NULL) {
        current = current->right;
    }

    return current;
}

Organization* findSuccessor(Organization* root)
{
    Organization* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

Organization* deleteData(Organization* parent, int number)
{
    if (parent == NULL) {
        return NULL;
    } else if (number < parent->number) {
        parent->left = deleteData(parent->left, number);
    } else if (number > parent->number) {
        parent->right = deleteData(parent->right, number);
    } else {
        if (!parent->left && !parent->right) {
            parent = NULL;
            free(parent);
            return NULL;
        } else if (!parent->right && parent->left) {
            Organization* temp = parent->left;
            parent = NULL;
            free(parent);
            return temp;
        } else if (!parent->left && parent->right) {
            Organization* temp = parent->right;
            parent = NULL;
            free(parent);
            return temp;
        } else {
            Organization* changer = findPredecessor(parent->left);
            parent->number = changer->number;
            strcpy(parent->name, changer->name);
            strcpy(parent->position, changer->position);
            parent->left = deleteData(parent->left, changer->number);
        }
    }
    return parent;
}

int main()
{
    Organization* root = createNewData(25, "Denzel", "President");
    insertData(root, 20, "Natasha Laurensky", "Vice President I");
    insertData(root, 36, "Jonathan, Cho", "Vice President II");
    insertData(root, 10, "Jonathan Dion", "PR Division");
    insertData(root, 22, "Christoper Kevin", "Art and Sport");
    insertData(root, 30, "Marcellino Oka", "Entrepreneurship");
    insertData(root, 46, "Yoga Angkawijaya", "Leadership");

    updateData(root, 25, "Denzel Caesarian", "0");
    updateData(root, 10, "0", "Public Relation");
    updateData(root, 5, "Laura Gabriella", "Religion"); //Not Found!

    viewDataInOrder(root); 
    printf ("=========================================\n");

    while(root) {
        root = deleteData(root, root->number);
        viewDataInOrder(root); 
        printf ("=========================================\n");
    }
    return 0;
}