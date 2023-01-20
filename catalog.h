#ifndef KINO_CATALOG_H
#define KINO_CATALOG_H

typedef struct film {
    char name[77];
    char release_year[6];
    char location[38];
    char genre[44];
    char rating[5];
} film;

typedef struct catalog {
    film film;
    struct catalog *next;
    struct catalog *prev;
} catalog;

struct catalog *init(catalog *ctlg, film film1);

void *add(catalog *catalog1, film film1);

void *del(catalog *catalog1);

void write_in_love_file(FILE *out, film film1);

void rewrite_films(FILE *out, catalog *catalog1);

#endif //KINO_CATALOG_H
