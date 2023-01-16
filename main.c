#include <stdio.h >
#include<unistd.h>
#include <stdlib.h>
#include "catalog.h"
#include "user.h"

int main() {
    int start;
    FILE *out= fopen("Users.txt","a+");
    Users *user= read_base(out);
    fclose(out);
    FILE *o= fopen("Users.txt","w");
    rewrite(out,user);
    fclose(o);


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
        //Завершение программы
        if (move == 'b') {
            system("cls");
            printf("Bye!!!");
            sleep(2);
            break;
        }
        //В списке всех фильмов передвижение ВЛЕВО
        if (move == 'a') {
            system("cls");
            p = p->next;
            printf("\n%s", p->film.name);
            printf("%s", p->film.release_year);
            printf("%s", p->film.location);
            printf("%s", p->film.genre);
            printf("%s", p->film.rating);
        }
        //В списке всех фильмов передвижение ВПРАВО
        if (move == 'd') {
            system("cls");
            p = p->prev;
            printf("\n%s", p->film.name);
            printf("%s", p->film.release_year);
            printf("%s", p->film.location);
            printf("%s", p->film.genre);
            printf("%s", p->film.rating);
        }
        if (move == 'q'){
            //тут должно появляся окно настроек пользователя(смена пароля и логина сразу, не по отдельности)
        }
        if (move == 'l'){
            //Добавление в избранное
        }
        if (move == 'z'){
            // Открыть список любимых
        }
        //Удаление из films.txt когда user админ
        if (move == 'o' && user->admin == 1){
            del(p);
            system("cls");
            p = p->prev;
            printf("\n%s", p->film.name);
            printf("%s", p->film.release_year);
            printf("%s", p->film.location);
            printf("%s", p->film.genre);
            printf("%s", p->film.rating);
        }
//        if (move == '')
    }
}

