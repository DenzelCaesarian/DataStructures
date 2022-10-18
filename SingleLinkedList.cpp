#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Coffee {
    char name[250];
    int price;
    char cupSize[25];
    
    //penghubung
    Coffee* next;
} *head, *tail;

Coffee* makeCoffee (char name[250], int price, char cupSize[25]) {
    //booking memory
    Coffee* newCoffee = (Coffee*) malloc(sizeof(Coffee));
    
    //memasukkan atribut
    strcpy(newCoffee->name, name);
    newCoffee->price = price;
    strcpy(newCoffee->cupSize, cupSize);
    newCoffee->next = NULL;
    
    return newCoffee;
}

void pushHead (char name[250], int price, char cupSize[25]) {
    //cek data (ada / tidak ada)
    if (head == NULL) {
        //tidak ada data
        //membuat data
        Coffee* newCoffee = makeCoffee(name, price, cupSize);
        //memasukkan data baru sebagai head sekaligus tail
        head = tail = newCoffee;
    } else {
        //ada data
        //membuat data
        Coffee* newCoffee = makeCoffee(name, price, cupSize);
        //menghubungkan next newCoffee ke head
        newCoffee->next = head;
        //memindahkan head ke newCoffee
        head = newCoffee;
    }
}

void pushTail (char name[250], int price, char cupSize[25]) {
    //cek data (ada / tidak ada)
    if (head == NULL) {
        //tidak ada data
        //membuat data
        Coffee* newCoffee = makeCoffee(name, price, cupSize);
        //memasukkan data baru sebagai head sekaligus tail
        head = tail = newCoffee;
    } else {
        //ada data
        //membuat data
        Coffee* newCoffee = makeCoffee(name, price, cupSize);
        //menghubungkan next newCoffee ke head
        tail->next = newCoffee;
        //memindahkan head ke newCoffee
        tail = newCoffee;
    }
}

//pushMid berdasarkan harga (terendah - tertinggi)
void pushMid (char name[250], int price, char cupSize[25]) {
    //cek data (ada / tidak ada)
    if (head == NULL) {
        //tidak ada data
        //membuat data
        Coffee* newCoffee = makeCoffee(name, price, cupSize);
        //memasukkan data baru sebagai head sekaligus tail
        head = tail = newCoffee;
    } else {
        if (price < head->price) {
            //harga lebih rendah dari data pertama
            pushHead(name, price, cupSize);
        } else if (price >= tail->price) {
            //harga lebih tinggi dari data terakhir
            pushTail(name, price, cupSize);
        } else {
            //data berada di tengah-tengah
            //membuat temporary
            Coffee* temp = head;
            //iterasi sampai harga data setelah temp > price
            while (temp->next->price <= price) {
                //menggeser temp ke data berikutnya
                temp = temp->next;
            }
            
            //temp berada tepat 1 sebelum data baru
            //membuat data
            Coffee* newCoffee = makeCoffee(name, price, cupSize);
            //menghubungkan next newCoffee ke temp->next
            newCoffee->next = temp->next;
            //menghubungkan next temp ke newCoffee
            temp->next = newCoffee;
        }
    }
}

void popHead () {
    //cek data (ada / tidak ada)
    if (head == NULL) {
        //tidak ada data
        printf ("No Data\n");
        return;
    } else {
        //ada data
        //membuat temporary
        Coffee* temp = head;
        //memindahkan head ke data ke-2
        head = head->next;
        //menghapus hubungan data ke-1 dengan data ke-2
        temp->next = NULL;
        //menghapus temporary
        temp = NULL;
        
        //mengembalikan memory
        free(temp);
    }
}

void popTail () {
    //cek data (ada / tidak ada)
    if (head == NULL) {
        //tidak ada data
        printf ("No Data\n");
        return;
    } else {
        //ada data
        //membuat temporary
        Coffee* temp = head;
        //iterasi sampai temp->next adalah data terakhir
        while (temp->next != tail) {
            //menggeser temp ke data berikutnya
            temp = temp->next;
        }
        
        //temp berada tepat 1 sebelum tail
        //menukar temp dengan tail
        tail = temp;
        temp = tail->next;
        //memutus hubungan tail dengan temp
        tail->next = NULL;
        //menghapus temporary
        temp = NULL;
        
        //mengembalikan memory
        free(temp);
    }
}

//popMid / popSearch untuk menghapus berdasarkan nama
void popMid (char name[250]) {
    //cek data (ada / tidak ada)
    if (head == NULL) {
        //tidak ada data
        printf ("No Data\n");
        return;
    } else {
        if (strcmp(head->name, name) == 0) {
            //data yang ingin dihapus merupakan data ke-1
            popHead();
        } else if (strcmp(tail->name, name) == 0) {
            //data yang ingin dihapus merupakan data terakhir
            popTail();
        } else {
            //data yang ingin dihapus berada di tengah-tengah
            //membuat temporary
            Coffee* temp = head;
            //iterasi sampai temp berada tepat 1 sebelum data yang ingin dihapus
            while (temp->next != tail && strcmp(temp->next->name, name) != 0) {
                //menggeser temp ke data berikutnya
                temp = temp->next;
            }
            
            //temp berada tepat 1 sebelum data yang ingin dihapus
            //membuat variabel penyimpanan
            Coffee* tobeDeleted = temp->next;
            //menghubungkan next temp ke next data yang akan dihapus
            //semisal data ke-3 akan dihapus, maka menghubungkan data ke-2 dengan data ke-4
            temp->next = tobeDeleted->next;
            //memutus hubungan data yang akan dihapus dengan data berikutnya
            //semisal data ke-3 akan dihapus, maka memutuskan hubungan data ke-3 dengan data ke-4
            tobeDeleted->next = NULL;
            //menghapus tobeDeleted
            tobeDeleted = NULL;
            
            //mengembalikan memory
            free(tobeDeleted);
        }
    }
}

void printData () {
    //cek data (ada / tidak ada)
    if (head == NULL) {
        //tidak ada data
        printf ("No Data\n");
        return;
    }
    //iterasi dari head sampai tail
    Coffee* currentData = head;
    while (currentData != NULL) {
        printf ("%s - %d - %s\n", currentData->name, currentData->price, currentData->cupSize);
        //memindahkan currentData ke next
        currentData = currentData->next;
    }
}

int main()
{
    pushMid("Americano", 16500, "Grande");
    pushMid("Espresso", 11000, "Small");
    pushMid("Green Tea Latte", 27000, "Venti");
    pushMid("Cotton Candy Frappucino", 30500, "Grande");
    pushMid("Asian Dolce Latte", 22000, "Small");
    
    printData();
    
    return 0;
}
