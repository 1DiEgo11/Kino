#include <stdio.h >
#include<unistd.h>
#include <stdlib.h>
#include "catalog.h"
#include "user.h"

int main() {
    FILE *out = fopen("Users.txt", "a+");
    Users user = read_user(out);
    char str[29] = "favorite_";
    strcat(str, user.login);
    strcpy(user.favorite_file, str);
    FILE *user_fav = fopen(user.favorite_file, "a+");
//    fclose(out);
//    FILE *o= fopen("Users.txt","w");
//    rewrite(out,user);
//    fclose(o);


    system("chcp 65001");//поддержка русского языка
    system("cls");
    //Создание каталога всех фильмов
    FILE *films = fopen("films.txt", "a+");
    film *film1 = (film *) malloc(sizeof(film));
    catalog *ctlg = (catalog *) malloc(sizeof(catalog));
    for (int i = 0; i < 1; i++) {
        fgets(film1->name, 77, films);
        fgets(film1->release_year, 6, films);
        fgets(film1->location, 38, films);
        fgets(film1->genre, 44, films);
        fgets(film1->rating, 5, films);
    }
    init(ctlg, *film1);
    while (!feof(films)) {
        film *film_new = (film *) malloc(sizeof(film));
        fgets(film_new->name, 77, films);
        if (feof(films))
            break;
        fgets(film_new->release_year, 6, films);
        fgets(film_new->location, 38, films);
        fgets(film_new->genre, 44, films);
        fgets(film_new->rating, 5, films);
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
            printf("%s", p->film.name);
            printf("%s", p->film.release_year);
            printf("%s", p->film.location);
            printf("%s", p->film.genre);
            printf("%s", p->film.rating);
        }
        //В списке всех фильмов передвижение ВПРАВО
        if (move == 'd') {
            system("cls");
            p = p->prev;
            printf("%s", p->film.name);
            printf("%s", p->film.release_year);
            printf("%s", p->film.location);
            printf("%s", p->film.genre);
            printf("%s", p->film.rating);
        }
        if (move == 'q') {
            //тут должно появляся окно настроек пользователя(смена пароля и логина сразу, не по отдельности)
        }
        //Добавление в избранное
        if (move == 'l') {
            user.fav_size++;
            write_in_love(user_fav, p->film);
        }
        // Открыть список любимых
        if (move == 'z') {
            system("cls");
            catalog *love = (catalog *) malloc(sizeof(catalog));
            film *fov_film = (film *) malloc(sizeof(film));
            FILE *film_love = fopen(user.favorite_file, "r");
            for (int i = 0; i < 1; i++) {
                fgets(fov_film->name, 77, film_love);
                fgets(fov_film->release_year, 6, film_love);
                fgets(fov_film->location, 38, film_love);
                fgets(fov_film->genre, 44, film_love);
                fgets(fov_film->rating, 5, film_love);
            }
            init(love, *fov_film);
            while (!feof(film_love)) {
                film *film_new = (film *) malloc(sizeof(film));
                fgets(film_new->name, 77, film_love);
                if (feof(film_love))
                    break;
                fgets(film_new->release_year, 6, film_love);
                fgets(film_new->location, 38, film_love);
                fgets(film_new->genre, 44, film_love);
                fgets(film_new->rating, 5, film_love);
                add(love, *film_new);
            }
            catalog *l = love;
            //Передвижение по списку любимых
            while (1) {
                char move_love;
                scanf("%c", &move_love);
                if (move_love == 'b') {
                    system("cls");
                    printf("Bye!!!");
                    sleep(2);
                    return 0;
                }
                if (move_love == 't') {
                    system("cls");
                    break;

                }
                if (move_love == 'a') {
                    system("cls");
                    if(l->next->film.name[0] == '\n')
                        l = l->next->next;
                    else
                        l = l->next;
                    printf("%s", l->film.name);
                    printf("%s", l->film.release_year);
                    printf("%s", l->film.location);
                    printf("%s", l->film.genre);
                    printf("%s", l->film.rating);
                }
                if (move_love == 'd') {
                    system("cls");
                    l = l->prev;
                    printf("%s", l->film.name);
                    printf("%s", l->film.release_year);
                    printf("%s", l->film.location);
                    printf("%s", l->film.genre);
                    printf("%s", l->film.rating);
                }
            }
        }
        //Удаление из films.txt когда user админ
        if (move == 'o' && user.admin == 1) {
            del(p);
            system("cls");
            p = p->prev;
            printf("%s", p->film.name);
            printf("%s", p->film.release_year);
            printf("%s", p->film.location);
            printf("%s", p->film.genre);
            printf("%s", p->film.rating);
        }
        //Добавление нового фильма в films.txt когда user админ
        if (move == 'n' && user.admin == 1){
            system("cls");
            film *new_film = (film*) malloc(sizeof(film));

            char name[77];
            printf("Введите название фильма:");
            scanf("%s", name);
            name[76] = '\n';
            strcpy(new_film->name, name);

            char release_year[6];
            printf("Введите год выпуска фильма:");
            scanf("%s", release_year);
            strcpy(new_film->release_year, release_year);

            char location[38];
            printf("Введите страну выпуска фильма:");
            scanf("%s", location);
            strcpy(new_film->location, location);

            char genre[44];
            printf("Введите жанр фильма:");
            scanf("%s", genre);
            strcpy(new_film->genre, genre);

            char rating[5];
            printf("Введите рейтинг фильма:");
            scanf("%s", rating);
            strcpy(new_film->rating, rating);

            add(ctlg, *new_film);
        }
    }
    fclose(films);
    //Перезапись файла films.txt так как может быть админ добавил новый фильм
    FILE *rewrite = fopen("films.txt", "w");
    rewrite_films(rewrite, ctlg);
    //Нужна перезапись файла юзеров так как мы изменяем значения fav_size
}

