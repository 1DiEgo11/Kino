#include <stdio.h >
#include<unistd.h>
#include <stdlib.h>
#include "catalog.h"


int main() {
    system("chcp 65001");
    system("cls");
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
    while (!feof(films)) {
        film *film_new = (film *) malloc(sizeof(film));
        fgets(film_new->name, 200, films);
        fgets(film_new->release_year, 200, films);
        fgets(film_new->location, 200, films);
        fgets(film_new->genre, 200, films);
        fgets(film_new->rating, 200, films);
        add(ctlg, *film_new);
    }

    catalog *p = ctlg;
    while (1) {
        char move;
        scanf("%c", &move);
        if (move == 'b') {
            system("cls");
            printf("Bye!!!");
            sleep(2);
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