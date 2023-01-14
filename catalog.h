
#ifndef KINO_CATALOG_H
#define KINO_CATALOG_H

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

struct catalog *init(catalog *ctlg, film film1);

void *add(catalog *catalog1, film film1);

#endif //KINO_CATALOG_H
