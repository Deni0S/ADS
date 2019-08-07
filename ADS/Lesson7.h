//
//  Lesson7.h
//  AiSD
//
//  Created by Денис Баринов on 11/12/2018.
//  Copyright © 2018 Денис Баринов. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define T char
#define MaxN 100
#define G 11

void matrix (void);
int n = 0;
int N7 = -1;
T Stack [MaxN];
T pop7 (void);
void push7 (T i);
char Graf [G][G];
char color[G];
void Null (void);
void grafDepth (char mas[G][G], char a);
char Queue [MaxN];
int front7 = MaxN;
int rear7 = MaxN;
T queuePop7 (void);
void queuePush7 (char p);
void grafWidth (char mas[G][G], char a);
char Dkstr [G][4];
int O [G];
int P [G];
void Deykstra (char mas[G][G], char a);
void DeykstraWay (char mas[G][G], char b) ;

void Lesson7() {
    // 1. Написать функции, которые считывают матрицу смежности из файла и выводят ее на экран
    matrix ();
    
    // 2. Написать рекурсивную функцию обхода графа в глубину.
    printf("Обход в глубину:\n");
    Null ();
    grafDepth (Graf, 'A');
    printf("\n");
    Null ();
    grafDepth (Graf, 'H');
    printf("\n\n");
    
    // 3. Написать функцию обхода графа в ширину.
    printf("Обход в ширину:\n");
    Null ();
    grafWidth (Graf, 'A');
    printf("\n");
    Null ();
    grafWidth (Graf, 'H');
    printf("\n\n");
    
    // 4. Реализовать алгоритм Дейкстра (нахождение наименьшего пути).
    Null ();
    printf("Алгоритм Дейкстра: \n");
    Deykstra (Graf, 'B');
    for (int i = 1; i<G-1; i++)
        printf(" %c", Graf[i][1]);
    printf("\n");
    for (int j = 1; j<G-1; j++)
        printf(" %d", O[j]);
    printf("\n");
    DeykstraWay (Graf, 'D');
    printf("\n\n");
}

// Cчитываем матрицу смежности из файла и выводим на экран
void matrix (){
    FILE* file = fopen("Matrix.txt", "r");
    if (file == NULL) {
        puts("can't open file!");
        exit(1);
    }
    int count;
    fscanf(file, "%d", &count); // считываем количество записей
    char Matrix[count][count];
    for (int i=0; i<count && !feof(file); i++)
        for(int j=0; j<count && !feof(file); j++) {
            fscanf(file, "%c", &Matrix[i][j]);
            printf("%c ", Matrix[i][j]);
            Graf [i][j] = Matrix[i][j];
        }
    fclose(file);
    printf("\n");
}

//Вытащить последний элемент стека
T pop7 () {
    if ( N7 != -1 ) {
        //        printf("%c", Stack[N]);
        return Stack[N7--];
    }
    else
        printf("Stack is empty");
    return 0;
}

//Добавить в стек
void push7 (T i){
    if (N7 < MaxN){
        N7++;
        Stack[N7] = i;
    }
    else
        printf("Stack owerflow");
}

//Обнуление переменных
void Null () {
    while (N7 != -1)
        pop7 ();
    n = 0;
    //    for (int i = 0; i<G; i++)
    //        R[i] = 0;
}

//Функция обхода графа в глубину
void grafDepth (char mas[G][G], char a) {
    if (n == 0) {
        color[n] = a;
        n++;
    }
    int i = 1;
    while (mas[i][1] != a && i != G) {
        i++;
    }
    if (i == G)
        exit(1);
    for (int j = 2; j<G; j++)
        if (mas[i][j] != '0') {
            int g = 0;
            while (color[g] != mas[0][j] && g != n) {
                g++;
            }
            if (g == n) {
                push7 (mas[0][j]);
                color[n] = mas[0][j];
                n++;
            }
        }
    printf("%c", a);
    if (N7 != -1) {
        printf("->");
        grafDepth (mas, pop7());
    }
}

//Удалить элемент из очереди
T queuePop7 () {
    if (rear7 != front7) {
        front7--;
        return Queue[front7];
    }
    else
        printf("The queue is empty");
    return 0;
}

//Добавить элемент в очередь
void queuePush7 (char p) {
    if (rear7 != 0){
        rear7--;
        Queue[rear7] = p;
    }
    else {
        rear7 = MaxN;
        queuePush7 (p);
    }
}

//Функция обхода графа в ширину
void grafWidth (char mas[G][G], char a) {
    if (n == 0) {
        color[n] = a;
        n++;
    }
    int i = 1;
    while (mas[i][1] != a && i != G) {
        i++;
    }
    if (i == G)
        exit(1);
    for (int j = 2; j<G; j++)
        if (mas[i][j] != '0') {
            int g = 0;
            while (color[g] != mas[0][j] && g != n) {
                g++;
            }
            if (g == n) {
                queuePush7 (mas[0][j]);
                color[n] = mas[0][j];
                n++;
            }
        }
    printf("%c", a);
    if (rear7 != front7) {
        printf("->");
        grafWidth (mas, queuePop7());
    }
}

//Нахождение кратчайшего пути по алгоритму Дейкстра
void Deykstra (char mas[G][G], char a) {
    int i = 1;
    while (mas[i][1] != a && i != G) {
        i++;
    }
    if (i == G)
        exit(1);
    if (n == 0)
        n = i;
    O[n] = 0;
    for (int j = 2; j<G; j++)
        if (mas[i][j] != '0'){
            int g = 1;
            while (mas[g][1] != mas[0][j]){
                g++;
            }
            int top = mas[i][j] - '0' + O[i];
            if (top < O[g] || !O[g]) {
                queuePush7 (mas[0][j]);
                O[g] = top;
            }
        }
    if (rear7 != front7) {
        Deykstra (mas, queuePop7());
    }
}

//Наикротчайший путь из точки в вершину
void DeykstraWay (char mas[G][G], char b) {
    printf("%c", b);
    int i = 1;
    while (mas[i][1] != b && i != G) {
        i++;
    }
    if (i == G)
        exit(1);
    for (int j = 2; j<G; j++)
        if (mas[i][j] != '0') {
            int ost;
            ost = O[i] - (mas[i][j] - '0');
            if (ost == O[j-1]){
                printf("->");
                DeykstraWay (mas, mas[0][j]);
            }
        }
}
