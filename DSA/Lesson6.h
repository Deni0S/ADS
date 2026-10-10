//
//  Lesson6.h
//  AiSD
//
//  Created by Денис Баринов on 10/12/2018.
//  Copyright © 2018 Денис Баринов. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

void hashFunc (char* Mas);
typedef int U;

typedef struct Node {
    U data;
    char name;
    U age;
    U weight;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;
void printTree (Node *root);
void insert (Node **head, int value);
void preOrderTravers (Node* root);
void inOrderTravers (Node *root);
void postOrderTravers (Node *root);
void searchTree (Node *root, int key);
FILE* file;
Node* balanseTree (int n);
void comandTree(void);

Node* balansStud (int m);
void searchAge (Node *root, int key);
void searchWeight (Node *root, int key);
void printStudent (Node* root);
void baseStud (void);

void Lesson6() {
    // 1. Реализовать простейшую хэш-функцию. На вход функции подается строка, на выходе сумма кодов символов.
    hashFunc ("N53gedr/");
    
    // 2. Переписать программу, реализующее двоичное дерево поиска.
    Node *Tree = NULL;
    insert (&Tree, 6);
    insert (&Tree, 8);
    insert (&Tree, 4);
    insert (&Tree, 55);
    printf("Скобочная запись дерева: ");
    printTree(Tree);
    
    //  а) Добавить в него обход дерева различными способами;
    printf("\nPreOrderTravers: ");
    preOrderTravers(Tree);
    printf("\nInOrderTravers: ");
    inOrderTravers(Tree);
    printf("\nPostOrderTravers: ");
    postOrderTravers(Tree);
    printf("\n");
    
    //  б) Реализовать поиск в двоичном дереве поиска;
    searchTree(Tree, 55);
    
    //  в) *Добавить в программу обработку командной строки с помощью которой можно указывать из какого файла считывать данные, каким образом обходить дерево.
    comandTree();
    
    // 3. *Разработать базу данных студентов из двух полей “Имя”, “Возраст”, “Табельный номер” в которой использовать все знания, полученные на уроках. Считайте данные в двоичное дерево поиска. Реализуйте поиск по какому-нибудь полю базы данных (возраст, вес).
    baseStud ();
}

//Hash функция
void hashFunc (char* Mas){
    int i = 0;
    int hash = 0;
    while (Mas[i] != '\0'){
        hash += (Mas[i]);
        i++;
    }
    printf("%d \n", hash);
}


// Распечатывание двоичного дерева в виде скобочной записи
void printTree (Node *root){
    if (root) {
        printf("%d", root->data);
        if (root->left || root->right) {
            printf("(");
            
            if (root->left)
                printTree (root->left);
            else
                printf("NULL");
            printf(",");
            
            if (root->right)
                printTree (root->right);
            else
                printf("NULL");
            printf(")");
        }
    }
}

//Создание нового узла
Node* getFreeNode(U value, Node *parent){
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp -> left = tmp -> right = NULL;
    tmp -> data = value;
    tmp -> parent = parent;
    return tmp;
}

//Вставка узла
void insert (Node **head, int value){
    Node *tmp = NULL;
    if (*head == NULL) {
        *head = getFreeNode(value, NULL);
        return;
    }
    tmp = *head;
    while (tmp) {
        if (value > tmp -> data) {
            if (tmp -> right) {
                tmp = tmp -> right;
                continue;
            }
            else {
                tmp->right = getFreeNode(value, tmp);
                return;
            }
        }
        else if (value < tmp -> data) {
            if (tmp -> left) {
                tmp = tmp -> left;
                continue;
            }
            else {
                tmp -> left = getFreeNode(value, tmp);
                return;
            }
        }
        else {
            exit(2);  //Дерево построено неправильно
        }
    }
}

//Обход дерева в прямом порядке
void preOrderTravers (Node* root){
    if (root) {
        printf("%d ", root->data);
        preOrderTravers(root->left);
        preOrderTravers(root->right);
    }
}

//Обход дерева симметрично
void inOrderTravers (Node *root){
    if (root) {
        preOrderTravers(root->left);
        printf("%d ", root->data);
        preOrderTravers(root->right);
    }
}

//Обход дерева в обратном порядке
void postOrderTravers (Node *root){
    if (root) {
        preOrderTravers(root->left);
        preOrderTravers(root->right);
        printf("%d ", root->data);
    }
}

//Поиск в двоичном дереве
void searchTree (Node *root, int key){
    if (root) {
        if (root->data == key)
            printf("Найден искомый символ: %d \n", key);
        searchTree(root->left, key);
        searchTree(root->right, key);
    }
}

//Построить идеально сбалансированное дерево
Node* balansTree (int n) {
    Node* newNode;
    int x, nl, nr;
    if (n==0)
        newNode = NULL;
    else {
        fscanf (file, "%d", &x);
        nl = n/2;
        nr = n-nl-1;
        newNode = (Node*) malloc(sizeof(Node));
        newNode->data = x;
        newNode->left = balansTree(nl);
        newNode->right = balansTree(nr);
    }
    return newNode;
}

//Обработка командной строки для дерева
void comandTree (){
    Node *Tree = NULL;
    char put;
    printf("Введите полный путь файла - data.txt: ");
    scanf("%s", &put);
    file = fopen(&put, "r");
    if (file == NULL) {
        puts("can't open file!");
        exit(1);
    }
    int count;
    fscanf(file, "%d", &count); // считываем количество записей
    Tree = balansTree(count);
    fclose(file);
    printTree(Tree);
    printf("\n");
    int a;
    printf("Введите цифру варианта обхода дерева: 1.Прямой порядок 2.Симметрично 3.Обратный порядок");
    scanf("%d", &a);
    switch (a) {
        case 1:
            preOrderTravers(Tree);
            break;
        case 2:
            inOrderTravers(Tree);
            break;
        case 3:
            postOrderTravers(Tree);
            break;
        default:
            printf("Неверно введена цифра");
            break;
    }
}



//Построить идеально сбалансированное дерево студентов
Node* balansStud (int m) {
    Node* newNode;
    int d, a, w, nl, nr;
    char n;
    if (m==0)
        newNode = NULL;
    else {
        fscanf (file, "%d%s%d%d", &d, &n, &a, &w);
        newNode = (Node*) malloc(sizeof(Node));
        nl = m/2;
        nr = m-nl-1;
        newNode->data = d;
        newNode->name = n;
        newNode->age = a;
        newNode->weight = w;
        newNode->left = balansStud(nl);
        newNode->right = balansStud(nr);
    }
    return newNode;
}

//Поиск возраста студентов
void searchAge (Node *root, int key){
    if (root) {
        if (root->age == key){
            if (root->age == 11 || root->age == 12 || root->age == 13 || root->age == 14)
                printf("\n %d %c %d лет %d кг", root->data, root->name, root->age, root->weight);
            else if (root->age % 10 == 1)
                printf("\n %d %c %d год %d кг", root->data, root->name, root->age, root->weight);
            else if (root->age % 10 == 2 || root->age % 10 == 3 || root->age % 10 == 4)
                printf("\n %d %c %d года %d кг", root->data, root->name, root->age, root->weight);
            else
                printf("\n %d %c %d лет %d кг", root->data, root->name, root->age, root->weight);
        }
        searchAge(root->left, key);
        searchAge(root->right, key);
    }
}

//Поиск веса студентов
void searchWeight (Node *root, int key){
    if (root) {
        if (root->weight == key){
            if (root->age == 11 || root->age == 12 || root->age == 13 || root->age == 14)
                printf("\n %d %c %d лет %d кг", root->data, root->name, root->age, root->weight);
            else if (root->age % 10 == 1)
                printf("\n %d %c %d год %d кг", root->data, root->name, root->age, root->weight);
            else if (root->age % 10 == 2 || root->age % 10 == 3 || root->age % 10 == 4)
                printf("\n %d %c %d года %d кг", root->data, root->name, root->age, root->weight);
            else
                printf("\n %d %c %d лет %d кг", root->data, root->name, root->age, root->weight);
        }
        searchWeight(root->left, key);
        searchWeight(root->right, key);
    }
}

//Вывод всех студентов
void printStudent (Node* root){
    if (root) {
        if (root->age == 11 || root->age == 12 || root->age == 13 || root->age == 14)
            printf("\n %d %c %d лет %d кг", root->data, root->name, root->age, root->weight);
        else if (root->age % 10 == 1)
            printf("\n %d %c %d год %d кг", root->data, root->name, root->age, root->weight);
        else if (root->age % 10 == 2 || root->age % 10 == 3 || root->age % 10 == 4)
            printf("\n %d %c %d года %d кг", root->data, root->name, root->age, root->weight);
        else
            printf("\n %d %c %d лет %d кг", root->data, root->name, root->age, root->weight);
        printStudent(root->left);
        printStudent(root->right);
    }
}

//Управление базой данных студентов
void baseStud (){
    Node *Stud = NULL;
    file = fopen("stud.txt", "r");
    if (file == NULL) {
        puts("can't open file!");
        exit(1);
    }
    int count;
    fscanf(file, "%d", &count); // считываем количество записей
    Stud = balansStud(count);
    fclose(file);
    printf("Cтуденты соответсвующие возрасту 19: ");
    searchAge (Stud, 19);
    printf("\n");
    printf("Cтуденты соответсвующие весу 59: ");
    searchWeight (Stud, 59);
    printf("\n");
    printf("Все студенты в базе: ");
    printStudent (Stud);
    printf("\n");
}
