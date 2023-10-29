#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Node {
    int data;
    struct Node* next;
};

typedef struct Node Node;

struct Student {
    int studentNumber;
    char name[50];
    int age;
    struct Student* next;
};

typedef struct Student Student;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Yeterli bellek olmadigi icin yer acilamadi\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addToFront(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void addToEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void processNumbers(Node** head) {
    int num;
    
    printf("sayilari giriniz(-1'e basarak cikabilirsiniz): \n");
    
    while (1) {
        scanf("%d", &num);
        
        if (num == -1) {
            break;
        }
        
        if (num % 2 != 0) {
            // eger cift sayi ise listenin basina ekler
            addToFront(head, num);
        } else {
            // eger tek sayi ise listenin sonuna ekler
            addToEnd(head, num);
        }
    }
    printf("listedeki sayilar: ");
    printList(*head); // sayilari yazar
    
}
// Function to sort the numbers in descending order using bubble sort
void bubbleSort(Node* head) {
    int swapped, i;
    Node* ptr1;
    Node* lptr = NULL;

    // liste bos mu diye kontrol eder
    if (head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data < ptr1->next->data) {
                // buyuk kucuk karsýlastirmasi yapip yer degistirir
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void generateRandomNumbers(Node** head, int count) {
    srand(time(NULL)); // rastgele sayilar olusturur
    for (int i = 0; i < count; i++) {
        int num = rand() % 1000;  // 1000-0 arasinda sayilar olusturur
        addToFront(head, num);
    }
}

Student* createStudent(int studentNumber, const char* name, int age) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    if (newStudent == NULL) {
        fprintf(stderr, "bellek hatasi\n");
        exit(EXIT_FAILURE);
    }
    newStudent->studentNumber = studentNumber;
    strcpy(newStudent->name, name);
    newStudent->age = age;
    newStudent->next = NULL;
    return newStudent;
}

void addStudent(Student** head, int studentNumber, const char* name, int age) {
    Student* newStudent = createStudent(studentNumber, name, age);
    if (*head == NULL) {
        // Eðer liste bossa, yeni ogrenci dugumu liste basi olacak
        *head = newStudent;
    } else {
        // Liste boþ deðilse, listenin sonuna gidip yeni öðrenci düðümünü ekleyin
        Student* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
}

void printStudents(Student* head) {
    int count = 0;
    Student* temp = head;
    printf("ogrenci bilgileri:\n");
    while (temp != NULL) {
        printf("ogrenci numarasi: %d, ismi: %s, yasi: %d\n", temp->studentNumber, temp->name, temp->age);
        temp = temp->next;
        count++;
    }
    printf("toplam ogrenci sayisi: %d\n", count);
}

void searchStudent(Student* head, const char* name) {
    Student* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("ogrenci numarasi: %d, ismi: %s, yasi: %d\n", temp->studentNumber, temp->name, temp->age);
            return;
        }
        temp = temp->next;
    }
    printf("ogrenci bulunamadi.\n");
}

void deleteNextNode(Student* head, const char* name) {
    Student* temp = head;

    // ogrenciyi ismini kullanarak bulmak icin tarar
    while (temp != NULL && strcmp(temp->name, name) != 0) {
        temp = temp->next;
    }

    // eger ogrenci var ve son node da degilse isleme devam eder
    if (temp != NULL && temp->next != NULL) {
        Student* toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
        printf("bu isimden (%s) sonraki ogrenci silindi.\n", name);
    } else {
        printf("bu isim bulanamadi ya da sonraki node bos\n");
    }
    
}

void printLongestName(Student* head) {
    Student* temp = head;
    int maxLength = 0;
    Student* longestNameStudent = NULL;
    while (temp != NULL) {
        int nameLength = strlen(temp->name);
        if (nameLength > maxLength) {
            maxLength = nameLength;
            longestNameStudent = temp;
        }
        temp = temp->next;
    }
    if (longestNameStudent != NULL) {
        printf("en uzun isme sahip ogrenci: ogrenci numarasi: %d, ismi: %s, yasi: %d\n", 
               longestNameStudent->studentNumber, longestNameStudent->name, longestNameStudent->age);
    } else {
        printf("ogrenci bulunamadi.\n");
    }
}

int main() {
    Node* numbersList = NULL;
    Student* studentsList = NULL;
    int choice;
    
    while (1) {
        printf("\nKullanici arayuzu:\n");
        printf("1. listeye sayi ekle (tek ise listenin basina, cift ise listenin sonuna)\n");
        printf("2. 100 rastgele sayiyi sirala (buyukten kucuge)\n");
        printf("3. yeni ogrenci ekle\n");
        printf("4. isme gore ogrenci ara\n");
        printf("5. girilen isimden sonraki ogrenciyi sil\n");
        printf("6. en uzun isme sahip ogrenciyi yaz\n");
        printf("7. Cikis\n");
        printf("Yapmak istediginiz islemi seciniz: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                processNumbers(&numbersList);
                break;
            case 2:
                generateRandomNumbers(&numbersList, 100);
                printf("rastgele olusturulmus sayilar:\n");
                printList(numbersList);
                bubbleSort(numbersList); // sayilari sirala
                printf("Buyukten kucuge siralanmis rastgele sayilar:\n");
                printList(numbersList);
                break;
            case 3: {
                int studentNumber, age;
                char name[50];
                printf("ogrencinin bilgilerini giriniz (ogrencinin numarasi, ismi, yasi): ");
                scanf("%d %s %d", &studentNumber, name, &age);
                addStudent(&studentsList, studentNumber, name, age);
                printf("Ogrenci listeye eklendi\n");
                break;
            }
            case 4: {
                char name[50];
                printf("Aranicak ogrenci ismini giriniz: ");
                scanf("%s", name);
                searchStudent(studentsList, name);
                break;
            }
            case 5: {
                char name[50];
                printf("Girilen isimden sonraki silinecek ogrenciyi giriniz: ");
                scanf("%s", name);
                deleteNextNode(studentsList, name);
                break;
            }
            case 6:
                printLongestName(studentsList);
                break;
            case 7:
                // cýkýs yapmadan once bellekleri bosaltiyoruz
                while (numbersList != NULL) {
                    Node* temp = numbersList;
                    numbersList = numbersList->next;
                    free(temp);
                }
                while (studentsList != NULL) {
                    Student* temp = studentsList;
                    studentsList = studentsList->next;
                    free(temp);
                }
                exit(0);
            default:
                printf("gecersiz giris tekrar giriniz: \n");
        }
    }
    
    return 0;
}
