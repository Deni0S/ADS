//
//  Lesson5.h
//  AiSD
//
//  Created by Денис Баринов on 03/12/2018.
//  Copyright © 2018 Денис Баринов. All rights reserved.

#include <stdio.h>
#include <ctype.h>
#define T char
#define MaxN 100

int N2 = -1;
T Stack [MaxN];
T pop (void);
void push (T i);
void stackNull (void);
void perevod_2 (int M2);
void perevod (int M2);
int posled (char* Mas);
int postfix (char* Mas);
char Queue [MaxN];
int front = MaxN;
int rear = MaxN;
T queuePop (void);
void queuePush (char i);

void Lesson5() {
    // 1. Реализовать перевод из 10 в 2 систему счисления с использованием стека.
    perevod (345);
    
    // 2. Написать программу, которая определяет, является ли введенная скобочная последовательность правильной. Примеры правильных скобочных выражений: (), ([])(), {}(), ([{}]), неправильных — )(, ())({), (, ])}), ([(]) для скобок [,(,{. Например: (2+(2*2)) или [2/{5*(4+7)}]
    posled ("1+(}]2+(2*2))");
    posled ("[2/{5*(4+7)}]");
    
    // 3. **Реализовать алгоритм перевода из инфиксной записи арифметического выражения в постфиксную.
    postfix ("@(a-b)*(c+d)@");
    
    // 4. Реализовать очередь.
    queuePush ('A');
    queuePush ('B');
    queuePush ('C');
    printf("Очередь: ");
    while (rear != front)
        printf("%c", queuePop ());
    printf("\n");
}

//Вытащить последний элемент стека
T pop () {
    if ( N2 != -1 )
        return Stack[N2--];
    else
        printf("Stack is impty");
    return 0;
}

//Добавить в стек
void push (T i){
    if (N2 < MaxN){
        N2++;
        Stack[N2] = i;
    }
    else
        printf("Stack owerflow");
}

//Обнулить стек
void stackNull () {
    while (N2 != -1)
        pop ();
}

//Рекурсия перевода десятичной системы в двоичную
void perevod_2 (int M2){
    if (M2>1) {
        perevod_2 (M2/2);
    }
    push(M2%2);
}

//Фунция перевода из десятичной системы в двоичную
void perevod (int M2) {
    perevod_2 (M2);
    while (N2 != -1)
        printf("%d", pop());
    printf(" - Число %d в двоичной системе \n", M);
}

//Проверка скобочной последовательности
int posled (char* Mas){
    char etalon[6] = "([{}])";
    int i = 0;
    while (Mas[i] != '\0'){
        if (Mas[i] == etalon[0] || Mas[i] == etalon[1] || Mas[i] == etalon[2]){
            push (Mas[i]);
        }
        else if (Mas[i] == etalon[3]){
            if (N2 == -1){
                printf("%s - Не правильная последовательность \n", Mas);
                return 0;
            }
            else if (pop () != etalon[2]){
                printf("%s - Не правильная последовательность \n", Mas);
                stackNull();
                return 0;
            }
        }
        else if (Mas[i] == etalon[4]){
            if (N2 == -1){
                printf("%s - Не правильная последовательность \n", Mas);
                return 0;
            }
            else if (pop () != etalon[1]){
                printf("%s - Не правильная последовательность \n", Mas);
                stackNull();
                return 0;
            }
        }
        else if (Mas[i] == etalon[5]){
            if (N2 == -1){
                printf("%s - Не правильная последовательность \n", Mas);
                return 0;
            }
            else if (pop () != etalon[0]){
                printf("%s - Не правильная последовательность \n", Mas);
                stackNull();
                return 0;
            }
        }
        i++;
    }
    if (N2 != -1){
        printf("%s - Не правильная последовательность \n", Mas);
        stackNull();
        return 0;
    }
    printf("%s - Правильная последовательность \n", Mas);
    return 1;
}

//Перевод в постфиксную форму
int postfix (char* Mas){
    if (posled (Mas) == 1) {
        char etalon[12] = "@+-*^/([{}])";
        char tehas;
        if (Mas[0] == etalon[0]){
            tehas = Mas[0];
            push (Mas[0]);
        }
        else {
            printf ("Запись должна начинаться с символа @ (┴) \n");
            return 0;
        }
        int i = 0;
        do {
            i++;
            if (isalpha(Mas[i]))
                printf("%c", Mas[i]);
            else if (tehas == etalon[0] || tehas == etalon[6] || tehas == etalon[7] || tehas == etalon[8]){
                if (Mas[i] == etalon[1] || Mas[i] == etalon[2] || Mas[i] == etalon[3] || Mas[i] == etalon[4] || Mas[i] == etalon[5] || Mas[i] == etalon[6] || Mas[i] == etalon[7] || Mas[i] == etalon[8]){
                    tehas = Mas[i];
                    push(Mas[i]);
                }
                else if (Mas[i] == etalon[9] || Mas[i] == etalon[10] || Mas[i] == etalon[11]){
                    if (tehas == etalon[6] || tehas == etalon[7] || tehas == etalon[8]){
                        pop();
                        tehas = pop();
                        push(tehas);
                    }
                    else
                        printf("Error");
                }
                else if (Mas[i] == etalon[0] || tehas == etalon[0]){
                    if (tehas == etalon[6] || tehas == etalon[7] || tehas == etalon[8] || Mas[i] == etalon[9] || Mas[i] == etalon[10] || Mas[i] == etalon[11]){
                        printf("Ошибка. Формула некорректно сбалансирована! \n");
                        stackNull();
                        return 0;
                    }
                }
                else
                    printf("Error");
            }
            else if (tehas == etalon[1] || tehas == etalon[2] || Mas[i] == etalon[4]){
                if (Mas[i] == etalon[0] || Mas[i] == etalon[1] || Mas[i] == etalon[2] || Mas[i] == etalon[4] || Mas[i] == etalon[9] || Mas[i] == etalon[10] || Mas[i] == etalon[11]){
                    printf("%c", pop());
                    tehas = pop();
                    push(tehas);
                    i--;
                }
                else if (Mas[i] == etalon[3] || Mas[i] == etalon[5] || Mas[i] == etalon[6] || Mas[i] == etalon[7] || Mas[i] == etalon[8]){
                    tehas = Mas[i];
                    push(Mas[i]);
                }
                else
                    printf("Error");
            }
            else if (tehas == etalon[3] || tehas == etalon[5]){
                if (Mas[i] == etalon[0] || Mas[i] == etalon[1] || Mas[i] == etalon[2] || Mas[i] == etalon[3] || Mas[i] == etalon[4] || Mas[i] == etalon[5] || Mas[i] == etalon[9] || Mas[i] == etalon[10] || Mas[i] == etalon[11]){
                    printf("%c", pop());
                    tehas = pop();
                    push(tehas);
                    i--;
                }
                else if (Mas[i] == etalon[6] || Mas[i] == etalon[7] || Mas[i] == etalon[8]){
                    tehas = Mas[i];
                    push(Mas[i]);
                }
                else
                    printf("Error");
            }
            else
                printf("Error");
        } while (Mas[i] != etalon[0] /*|| Mas[i] != '\0'*/);
        //        if (Mas[i] == '\0')
        printf(" - Постфиксная запись выражения \n");
        stackNull();
        return 1;
    }
    else {
        printf ("Перевод в постфиксную запись невозможен \n");
        stackNull();
        return 0;
    }
}

//Удалить элемент из очереди
T queuePop () {
    if (rear != front) {
        front--;
        return Queue[front];
    }
    else
        printf("The queue is empty");
    return 0;
}

//Добавить элемент в очередь
void queuePush (char i) {
    if (rear != 0){
        rear--;
        Queue[rear] = i;
    }
    else {
        rear = MaxN;
        queuePush (i);
    }
}
