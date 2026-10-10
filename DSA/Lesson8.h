//
//  Lesson8.h
//  AiSD
//
//  Created by Денис Баринов on 14/12/2018.
//  Copyright © 2018 Денис Баринов. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

void CountSort (int *array, int k); // k - длина массива A
void swap8(int *a, int *b);
void QuickSort (int *array, int first, int last); // first, last - номера первого и последнего элементов
void Merge (int *array, int left, int right);
void MergeSort (int *array, int left, int right); // left - первый элемент, right - последний элемент

void Lesson8() {
    // 1. Реализовать сортировку подсчетом.
    int array1 [15] = {1, 4, 2, 4, 9, 55, 42, 3, 4, 1, 7, 9, 99, 4, 7};
    CountSort (array1, 15);
    
    // 2. Реализовать быструю сортировку.
    int array2 [15] = {7, 4, 99, 51, 65, 63, 9, 34, 77, 90, 59, 47, 1, 14, 17};
    QuickSort (array2, 0, 15);
    for (int i = 0; i<15; i++)
        printf("%d ", array2[i]);
    printf("- Быстрая\n\n");
    
    // 3. *Реализовать сортировку слиянием.
    int array3 [15] = {8, 1, 19, 5, 34, 3, 32, 67, 80, 4, 15, 7, 11 , 99, 40};
    MergeSort (array3, 0, 14);
    for (int i = 0; i<15; i++)
        printf("%d ", array3[i]);
    printf("- Слиянием\n\n");
    
    // 4. Проанализировать время работы каждого из вида сортировок для 100, 10000, 1000000 элементов. Заполнить таблицу.
}

//Сортировка подсчетом
void CountSort (int *array, int k) {
    int max = 0;
    for (int i = 0; i<k; i++)
        if (array[i]>=max)
            max = array[i]+1;
    int counter [max];
    for (int i = 0; i<max; i++)
        counter [i] = 0;
    for (int i = 0; i<k; i++)
        counter[array[i]]++;
    int b = 0;
    for (int j = 0; j<max; j++)
        for (int i = 0; i<counter[j]; i++)
            array[b++] = j;
    for (int i = 0; i<k; i++)
        printf("%d ", array[i]);
    printf("- Подсчетом\n\n");
}

//Обмен значений
void swap8(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Быстрая сортировка
void QuickSort (int *array, int first, int last) {
    int i = first, j = last, x = array [(first + last)/2];
    do {
        while (array[i]<x)
            i++;
        while (array[j]>x)
            j--;
        if (i <= j) {
            if (array [i] > array [j])
                swap8 (&array[i], &array[j]);
            i++;
            j--;
        }
    } while (i <= j);
    if (i < last)
        QuickSort (array, i, last);
    if (first < j)
        QuickSort (array, first, j);
}

//Слияние двух частей
void Merge (int *array, int left, int right) {
    int middle = (right+left)/2;
    int start = left;
    int final = middle+1;
    int mas[15];
    for (int i=left; i<=right; i++) {
        if ((start <= middle) && (final > right || array [start] < array [final])) {
            mas [i] = array [start];
            start++;
        }
        else {
            mas [i] = array [final];
            final++;
        }
    }
    for (int i=left; i<=right; i++)
        array [i] = mas [i];
}

//Сортировка слиянием
void MergeSort (int *array, int left, int right) {
    if (left < right) {
        if (right - left == 1) {
            if (array [right] < array [left])
                swap8 (&array [right], &array [left]);
        }
        else {
            MergeSort (array, left, (right+left)/2);
            MergeSort (array, (right+left+2)/2, right);
            Merge (array, left, right);
        }
    }
}
