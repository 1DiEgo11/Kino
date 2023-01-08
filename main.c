#include <stdio.h >
#include<unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <malloc.h>

typedef struct film {
    char name[200];
    char release_year[200];
    char location[200];
    char genre[200];
    char rating[200];
} film;

typedef struct catalog {
    film film;
    struct catalog *next;
    struct catalog *prev;
} catalog;

struct catalog *init(catalog *ctlg, film film1) {
    ctlg->film = film1;
    ctlg->next = ctlg;
    ctlg->prev = ctlg;
    return (ctlg);
}

void *add(catalog *catalog1, film film1) {
    catalog *temp = catalog1;
    do {
        catalog1 = catalog1->next;
    } while (temp != catalog1);
    temp = catalog1->next;
    catalog *new = (catalog *) malloc(sizeof(catalog));
    new->film = film1;
    new->next = temp;
    new->prev = catalog1;
    temp->prev = new;
    catalog1->next = new;
}

void print(catalog *catalog1) {
    catalog *p = catalog1;
    while (1) {
        char move;
        scanf("%c", &move);
        if (move == 'b') {
            system("cls");
            printf("Bye!!!");
            sleep(10);
            break;
        } else {
            switch (move) {
                case 'a':
                    system("cls");
                    p = p->next;
                    printf("\n%s", p->film.name);
                    printf("%s", p->film.release_year);
                    printf("%s", p->film.location);
                    printf("%s", p->film.genre);
                    printf("%s", p->film.rating);
                    break;
                case 'd':
                    system("cls");
                    p = p->prev;
                    printf("\n%s", p->film.name);
                    printf("%s", p->film.release_year);
                    printf("%s", p->film.location);
                    printf("%s", p->film.genre);
                    printf("%s", p->film.rating);
                    break;
            }
        }
    }
}


int main() {
    FILE *films = fopen("films.txt", "r");
    film *film1 = (film *) malloc(sizeof(film));
    catalog *ctlg = (catalog *) malloc(sizeof(catalog));
    for (int i = 0; i < 1; i++) {
        fgets(film1->name, 200, films);
        fgets(film1->release_year, 200, films);
        fgets(film1->location, 200, films);
        fgets(film1->genre, 200, films);
        fgets(film1->rating, 200, films);
    }
    init(ctlg, *film1);
    for (int i = 0; i < 30; i++) {
        film *film_new = (film *) malloc(sizeof(film));
        fgets(film_new->name, 200, films);
        fgets(film_new->release_year, 200, films);
        fgets(film_new->location, 200, films);
        fgets(film_new->genre, 200, films);
        fgets(film_new->rating, 200, films);
        add(ctlg, *film_new);
    }
    print(ctlg);
}