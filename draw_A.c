#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "draw_A.h"

int a(int a) {
    while (a > 0) {
        printf("\n");
        a = a - 1;
    }
}

int b(int b) {
    while (b > 0) {
        printf("\t");
        b = b - 1;

    }
}

int c(int c) {
    while (c > 0) {
        b(5);
        printf("#");
        b(4);
        printf("#\n");
        c = c - 1;

    }
}

void hello(){
    a(8);//а - отступ сверху, б - отступ слева
    b(5);
    printf("#################################\n");
    c(3);
    printf("\t\t\t\t\t#\t");
    printf(" !ONLINE CINEMA!\t#\n");
    printf("\t\t\t\t\t#\t");
    printf("     KINA.NET\t\t#\n");
    c(3);
    b(5);
    printf("#################################\n");
    sleep(2);
    system("cls");
}

void rl(){
    a(10);
    b(8);
    printf("_________\n\n");
    b(8);
    printf(">WELCOME<\n");
    b(8);
    printf("_________\n\n\n");
    b(7);
    printf("registr account\n");
    b(8);
    printf("(press r)\n\n\n");
    b(7);
    printf("log in account\n");
    b(8);
    printf("(press e)\n\n");
    b(9);
}

