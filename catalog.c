#include <stdlib.h>
#include <stdio.h>
#include "catalog.h"

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

void *del(catalog *catalog1){
    catalog *next, *prev;
    prev = catalog1->prev;
    next = catalog1->next;
    prev->next = catalog1->next;
    next->prev = catalog1->prev;
    free(catalog1);
}

void write_in_love(FILE *out, film film1) {
    fprintf(out, "%s", film1.name);
    fprintf(out, "%s", film1.release_year);
    fprintf(out, "%s", film1.location);
    fprintf(out, "%s", film1.genre);
    fprintf(out, "%s", film1.rating);
}

void rewrite_films(FILE *out, catalog *catalog1){
    fprintf(out, "%s", catalog1->film.name);
    fprintf(out, "%s", catalog1->film.release_year);
    fprintf(out, "%s", catalog1->film.location);
    fprintf(out, "%s", catalog1->film.genre);
    fprintf(out, "%s", catalog1->film.rating);

    catalog *p = catalog1->prev;
    while (p != catalog1){
        fprintf(out, "%s", p->film.name);
        fprintf(out, "%s", p->film.release_year);
        fprintf(out, "%s", p->film.location);
        fprintf(out, "%s", p->film.genre);
        fprintf(out, "%s", p->film.rating);
        p = p->prev;
    }
}