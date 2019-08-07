//
//  Lesson4.h
//  AiSD
//
//  Created by Денис Баринов on 01/12/2018.
//  Copyright © 2018 Денис Баринов. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define K 3
#define L 3
#define W 12
#define R 11
#define N 8
#define M 8

// 1
void Print1(int n, int m, int a[K][L]);
// 2
void Print2(int n, int m, char a[n][m]);
int lcs_length(char * A, char * B);
// 3
int board[N][M];
int SearchSolution(int n);
int CheckBoardQueen(void);
int CheckQueen(int x, int y);
int CheckBoardHorse(int z);
int CheckHorse (int x, int y, int z);
void Print3(int n, int m, int a[N][M]);
void Zero(int n, int m, int a[N][M]);
void Pause(int key);

void Lesson4() {
    // 1. *Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием и нахождение количество маршрутов. Например, карта 3 на 3:
    // 1 1 1
    // 0 1 0
    // 0 1 0
    int Map[K][L] = {
        1, 1, 1,
        0, 1, 0,
        0, 1, 0
    };
    int A[K][L];
    int i, j;
    for (j = 0; j < K; j++)
        if (Map[0][j] == 1)
            A[0][j] = 1;
        else
            A[0][j] = 0;
    for (i = 1; i < L; i++){
        if (Map[i][0] == 1)
            A[i][0] = 1;
        else
            A[i][0] = 0;
        for (j = 1; j < K; j++)
            if (Map[i][j] == 1)
                A[i][j] = A[i][j-1] + A[i-1][j];
            else
                A[i][j] = 0;
    }
    Print1 (K, L, A);
    
    // 2. Решить задачу о нахождении длины максимальной последовательности с помощью матрицы.
    char SequenceA [W] = {"  GEEKBRAINS"};
    char SequenceB [R] = {"  GEEKMINDS"};
    char Sequence [R][W];
    int MaxSeq = 0;
    for(j = 0; j < W; j++)
        Sequence[0][j] = SequenceA[j];
    for(i = 0; i < R; i++)
        Sequence[i][0] = SequenceB[i];
    j = 1;
    for(i = 2; i < R; i++){
        for(int z = i; z < R; z++)
            for(int n = j; n < W; n++){
                if(Sequence[z][0] == Sequence[0][n]){
                    for(j = j; j < n; j++)
                        for(int f = i; f < R; f++)
                            Sequence[f][j] = MaxSeq;
                    for(i = i; i < z; i++)
                        for(int f = j; f < W; f++)
                            Sequence[i][f] = MaxSeq;
                    MaxSeq++;
                    for (int f = i; f < R; f++)
                        Sequence[f][j] = MaxSeq;
                    for (int f = j; f < W; f++)
                        Sequence[i][f] = MaxSeq;
                    j++;
                    z = R;
                    n = W;
                }
            }
        for (int f = i; f < R; f++)
            Sequence[f][j] = MaxSeq;
        for (int f = j; f < W; f++)
            Sequence[i][f] = MaxSeq;
    }
    Print2 (R, W, Sequence);
    
    // 3. ***Требуется обойти конём шахматную доску размером NxM, пройдя через все поля доски по одному разу. Здесь алгоритм решения такой же как и в задаче о 8 ферзях. Разница только в проверке положения коня.
    Zero(N, M, board);
    SearchSolution(1);
    Print3(N, M, board);
    //    getchar();
    printf("\n");
}

// 1:
void Print1(int n, int m, int a[K][L]){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++)
            printf("%4d", a[i][j]);
        printf("\n");
    }
    printf("\n");
}

// 2:
void Print2 (int n, int m, char a[n][m]){
    int i, j;
    for(i = 0; i < n; i++){
        for(j = 0; j < m; j++)
            if (i == 0 || j == 0)
                printf("%4c", a[i][j]);
            else
                printf("%4d", a[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Решение через рекурсию
//int lcs_length(char * A, char * B){
//    if (*A == '\0' || *B == '\0') return 0;
//    else if (*A == *B) return 1 + lcs_length(A + 1, B + 1);
//    else return  max (lcs_length(A + 1, B), lcs_length(A, B + 1));
//}

// 3:
int SearchSolution(int n){
    // Если проверка доски возвращает 0, то эта расстановка не подходит
    if (CheckBoardHorse(n) == 0) return 0;
    // Решение найдено когда заполнена последняя клетка
    if (n == 65) return 1;
    //    // 9 ферзя не ставим. Решение найдено
    //    if (CheckBoardQueen() == 0) return 0;
    //    if (n == 9) return 1;
    int row;
    int col;
    for (row = 0; row < N; row++)
        for (col = 0; col < M; col++){
            if (board[row][col]==0){
                // Расширяем test_solution
                board[row][col]=n;
                // Рекурсивно проверяем, ведёт ли это к решению.
                if (SearchSolution(n+1)) return 1;
                // Если мы дошли до этой строки, данное частичное решение не приводит к полному
                board[row][col]=0;
            }
        }
    return 0;
}

// Проверка всей доски для Коня
int CheckBoardHorse(int z){
    int i, j;
    if (z < 3)
        return 1;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            if (board[i][j] == z-1)
                if (CheckHorse(i, j, z) == 0)
                    return 0;
    return 1;
}

// Проверка хода Коня
int CheckHorse (int x, int y, int z){
    int i, j = 0;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            // Если нашли клетку, где конь был до этого
            if (board[i][j] == (z-2)) {
                // Если не буквой Г
                if (abs(i - x) != 2 && abs(j - y) != 2)
                    return 0;
                if (abs(j - y) != 1 && abs(i - x) != 1)
                    return 0;
            }
    // Если мы дошли до этого места, то всё в порядке
    return 1;
}

// Проверка всей доски для Ферзя
int CheckBoardQueen(){
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            if (board[i][j] != 0)
                if (CheckQueen(i, j) == 0)
                    return 0;
    return 1;
}

// Проверка определённого Ферзя
int CheckQueen (int x, int y){
    int i, j;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            // Если нашли фигуру
            if (board[i][j] != 0)
                // Если это не наша фигура
                if (!(i == x && j == y)){
                    // Лежат на одной вертикали или горизонтали
                    if (i - x == 0 || j - y == 0)
                        return 0;
                    // Лежат на одной диагонали
                    if (abs(i - x) == abs(j - y))
                        return 0;
                }
    // Если мы дошли до этого места, то всё в порядке
    return 1;
}

// Выводим доску на экран
void Print3 (int n, int m, int a[N][M]){
    int i, j;
    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++)
            printf ("%4d", a[i][j]);
        printf ("\n");
    }
}

// Очищаем доску
void Zero (int n, int m, int a[N][M]){
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            a[i][j] = 0;
}

// Ожидание ввода
void Pause (int key){
    if (key == 1)
        getchar();
    else
        for (int i = 0; i < 100000000; i++);
}
