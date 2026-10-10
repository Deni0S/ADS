//
//  Lesson3.h
//  AiSD
//
//  Created by Денис Баринов on 03/12/2018.
//  Copyright © 2018 Денис Баринов. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

void print(int N, int *a) {
    for (int i = 0; i < N; i++)
        printf("%i ", a[i]);
    printf("\n");
}

int search (int *a, int N, int u) {
    for (int i = 0; i < N; i++) {
        //
        int L = 0;
        int R = N-1;
        int m = L+(R-L)/2;
        while (L <= R && a[i] != u) {
            if (a[i] < u)
                L = m + 1;
            else
                R = m - 1;
            m = L+(R-L)/2;
        }
        if (a[i] == u)
            return i;
    }
    return -1;
}

void Lesson3() {
    int array_0[100] = {0};
    int N = 100; //  количество элементов
    int schet; // счетчик действий
    srand(time(NULL));
    for (int i = 0; i < N; i++)
        array_0[i] = rand()%100+1;
    printf("Исходный массив из %d элементов: \n", N);
    print(N, array_0);
    
    // 1. Попробовать оптимизировать пузырьковую сортировку. Сравнить количество операций сравнения оптимизированной и не оптимизированной программы. Написать функции сортировки, которые возвращают количество операций.
    int *array_1 = array_0;
    schet = 0;
    for (int i = 0; i < N; i++) {
        //        schet++;
        for (int j = 0; j < N-1; j++) {
            //            schet++;
            if (array_1[j] > array_1[j+1]) {
                swap(&array_1[j], &array_1[j+1]);
                schet++;
            }
        }
    }
    printf("Пузырьковая сортировка = %d операций: \n", schet);
    print(N, array_1);
    
    // Оптимизированная пузырьковая сортировка
    int *array_2 = array_0;
    schet = 0;
    for (int i = 0; i < N; i++) {
        //        schet++;
        int z = 0;
        for (int j = 0; j < N-1; j++) {
            //            schet++;
            if (array_2[j] > array_2[j+1]) {
                swap(&array_2[j], &array_2[j+1]);
                schet++;
                z++;
            }
        }
        if (z == 0)
            break;
    }
    printf("Оптимизированная пузырьковая сортировка = %d операций: \n", schet);
    print(N, array_2);
    
    // 2. *Реализовать шейкерную сортировку.
    int *array_3 = array_0;
    schet = 0;
    int n = 1;
    for (int i = 0; i < N; i++) {
        //        schet++;
        for (int j = n-1; j < N-n; j++) {
            schet++;
            if (array_3[j] > array_3[j+1]) {
                swap(&array_3[j], &array_3[j+1]);
                //                schet++;
                printf("%d ", schet);
            }
        }
        printf("%d ", schet);
        for (int j = N-n; j > n-1; j--) {
            schet++;
            if (array_3[j] < array_3[j-1]) {
                swap(&array_3[j], &array_3[j-1]);
                //                schet++;
            }
        }
        n++;
    }
    printf("Шейкерная сортировка = %d операций: \n", schet);
    print(N, array_3);
    
    // 3. Реализовать бинарный алгоритм поиска в виде функции, которой передается отсортированный массив. Функция возвращает индекс найденного элемента или -1, если элемент не найден.
    printf("Индекс через бинарный алгоритм = %d \n", search(array_3, N, 6));
    
    // 4. *Подсчитать количество операций для каждой из сортировок и сравнить его с асимптотической сложностью алгоритма.
    printf("          Пузырьковая сортировка \n");
    printf("                   1000    | 10000     | 100000 \n");
    printf("Асимптоматическая  1000000 | 100000000 | 10000000000 \n");
    printf("Точная асимп-ая    999000  | 99990000  | 9999900000 \n");
    printf("Фактическая        999000  | 99990000  | 1409965408 \n");
    printf("          Оптимизированная пузырьковая сортировка \n");
    printf("                   1000    | 10000     | 100000 \n");
    printf("Асимптоматическая  1000000 | 100000000 | 10000000000 \n");
    printf("Точная асимп-ая    999000  | 99990000  | 9999900000 \n");
    printf("Фактическая        999     | 9999      | 99999 \n");
    printf("           Шейкерная сортировка \n");
    printf("                   1000    | 10000     | 100000 \n");
    printf("Асимптоматическая  1000000 | 100000000 | 10000000000 \n");
    printf("Точная асимп-ая    500500  | 50005000  | 5000050000 \n");
    printf("Фактическая        500000  | 50000000  | 705032704 \n");
}
