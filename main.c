#include <stdio.h>
#include <malloc.h>

typedef struct film{
    char name[200];
    char release_year[200];
    char location[200];
    char genre[200];
    char rating[200];
}film;

typedef struct catalog{
    film film;
    struct catalog *next;
    struct catalog *prev;
}catalog;

struct catalog *init(catalog *ctlg, film film1){
//    catalog *ctlg = (catalog*)malloc(sizeof(catalog));
    ctlg->film = film1;
    ctlg->next = ctlg;
    ctlg->prev = ctlg;
    return (ctlg);
}

struct catalog *add(catalog *catalog1, film film1){
    catalog *temp = (catalog*) malloc(sizeof(catalog));
    temp->film = film1;
    temp->next = catalog1->next;
    temp->prev = catalog1;
    catalog1->next = temp;
    return (catalog1);
}

void print(catalog *catalog1){
    catalog *p = catalog1;
    do{
        printf("%s", p->film.name);
        printf("%s", p->film.release_year);
        printf("%s", p->film.location);
        printf("%s", p->film.genre);
        printf("%s", p->film.rating);
        p = p->next;
    }while(p != catalog1);
}

int main() {
    FILE *films = fopen("films.txt", "r");
    film *film1 = (film*) malloc(sizeof(film));
    catalog *ctlg = (catalog*)malloc(sizeof(catalog));
    for (int i = 0; i < 1; i++){
        fgets(film1->name, 200, films);
        fgets(film1->release_year, 200, films);
        fgets(film1->location, 200, films);
        fgets(film1->genre, 200, films);
        fgets(film1->rating, 4, films);
    }
    init(ctlg, *film1);
    print(ctlg);
}
