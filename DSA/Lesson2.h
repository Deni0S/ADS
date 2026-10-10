//
//  Lesson2.h
//  AiSD
//
//  Created by Денис Баринов on 23/11/2018.
//  Copyright © 2018 Денис Баринов. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

void go(int N){
    if (N>1) {
        go(N/2);
    }
    printf("%d", N%2);
}

double step(int a, int b){
    if (b > 1)
        return a*step(a, b-1);
    else
        return a;
}

double step_2(int a, int b){
    if (b > 1) {
        if (b%2 == 0)
            return step_2(a*a, b/2);
        else
            return a*step_2(a*a, (b-1)/2);
    } else
        return a;
}

int calc_r(int a, int b, int p, int m){
    if (b>a)
        if (b%m==0)
            return calc_r(a, b-p, p, m)+calc_r(a, b/m, p, m);
        else
            return calc_r(a, b-p, p, m);
        else if (b==a)
            return 1;
        else
            return 0;
}

void Lesson2() {
    // 1. Реализовать функцию перевода из 10 системы в двоичную используя рекурсию.
    go(654);
    printf("\n");
    
    // 2. Реализовать функцию возведения числа a в степень b:
    // a. без рекурсии;
    int a = 7;
    int b = 7;
    double stepen = a;
    printf("%d в степени %d = ", a, b);
    if (a == 0 && b!=0)
        printf("0 \n");
    else if (b > 0) {
        while (b > 1) {
            stepen *= a;
            b--;
        }
        printf("%0.lf \n", stepen);
    } else if (b < 0) {
        while (b < -1) {
            stepen *= a;
            b++;
        }
        printf("%.10lf \n", 1/stepen);
    } else if (a != 0 && b == 0)
        printf("1 \n");
    else
        printf("невозможно вычислить \n");
    
    // b. рекурсивно;
    a = 7;
    b = 7;
    printf("Рекурсивно: %d в степени %d = ", a, b);
    if (a == 0 && b!=0)
        printf("0 \n");
    else if (b>0)
        printf("%0.lf \n", step(a, b));
    else if (b<0)
        printf("%.10lf \n", 1/step(a, -b));
    else if (a != 0 && b == 0)
        printf("1 \n");
    else
        printf("невозможно вычислить \n");
    
    // c. *рекурсивно, используя свойство чётности степени.
    a = 7;
    b = 7;
    printf("Рекурсивно через четность: %d в степени %d = ", a, b);
    if (a == 0 && b!=0)
        printf("0 \n");
    else if (b>0) {
        printf("%0.lf \n", step_2(a, b));
    } else if (b<0) {
        printf("%.10lf \n", 1/step_2(a, -b));
    }else if (a != 0 && b == 0)
        printf("1 \n");
    else
        printf("невозможно вычислить \n");
    
    // **3. Исполнитель "Калькулятор" преобразует целое число, записанное на экране. У исполнителя две команды, каждой команде присвоен номер: №1 Прибавь 1, №2 Умножь на 2 Первая команда увеличивает число на экране на 1, вторая увеличивает это число в 2 раза. Сколько существует программ, которые число 3 преобразуют в число 20?
    // а) с использованием массива;
    a = 3;
    b = 20;
    int p=1;
    int m=2;
    int calc[100] = {0};
    calc[a] = 1;
    for (int i = a+1; i<=b; i++)
        calc[i] = (i%m==0) ? calc[i/m]+calc[i-p] : calc[i-p];
    printf("Количество программ массивом = %d \n", calc[b]);
    //    for (int i=0; i<=20; i++)
    //        printf("%d ", calc[i]);
    
    // б) с использованием рекурсии.
    printf("Количество программ рекурсивно = %d \n", calc_r(3, 20, 1, 2));
}

