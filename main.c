#include <stdio.h >
#include<unistd.h>
#include <stdlib.h>
#include "catalog.h"
#include "user.h"

int main() {
    int i = 0;
    FILE *out = fopen("Users.txt", "a+");
    Users *userb = read_base(out), *start = read_base(out);
    system("chcp 65001");//поддержка русского языка
    system("cls");
    //Создание каталога всех фильмов
    FILE *films = fopen("films.txt", "r");
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

    printf("Чтобы войти, в аккаунт нажмите e, чтобы зарегистрироваться - r\n");
    char move, login[20], password[20];
    scanf("%c", &move);
    //вход (регистрация)
    if (move == 'e') {
        while (1) {
            printf("login: ");
            scanf("%s", login);
            printf("password: ");
            scanf("%s", password);
            if (enter(login, password, userb) == 1) break;
        }
        printf("Вход успешно выполнен\n");
    } else if (move == 'r') {
        char card[19];
        printf("login: ");
        scanf("%s", login);
        printf("password: ");
        scanf("%s", password);
        printf("card: ");
        gets(card);
        gets(card);
        rgister(login, password, card, out, userb);
        printf("Аккаунт успешно зарегистрирован\n");
        fclose(out);
        FILE *outnew= fopen("Users.txt","a+");
        start= read_base(outnew);
        userb= read_base(outnew);
    }


    while (strcmp(userb->login, login) != 0) userb = userb->prev;
    catalog *ctlg_love;
    if (userb->fav_size == 0) {
        ctlg_love = (catalog *) malloc(sizeof(catalog));
    } else {
        ctlg_love = (catalog *) malloc(sizeof(catalog));
        film *fov_film = (film *) malloc(sizeof(film));
        FILE *film_love = fopen(userb->favorite_file, "r");
        for (int i = 0; i < 1; i++) {
            fgets(fov_film->name, 77, film_love);
            fgets(fov_film->release_year, 6, film_love);
            fgets(fov_film->location, 38, film_love);
            fgets(fov_film->genre, 44, film_love);
            fgets(fov_film->rating, 5, film_love);
        }
        init(ctlg_love, *fov_film);
        while (!feof(film_love)) {
            film *film_new = (film *) malloc(sizeof(film));
            fgets(film_new->name, 77, film_love);
            if (feof(film_love))
                break;
            fgets(film_new->release_year, 6, film_love);
            fgets(film_new->location, 38, film_love);
            fgets(film_new->genre, 44, film_love);
            fgets(film_new->rating, 5, film_love);
            add(ctlg_love, *film_new);
        }
    }

    catalog *p = ctlg;
    while (1) {
        scanf("%c", &move);
        //Завершение программы
        if (move == 'b') {
            FILE *re = fopen("Users.txt", "w");
            rewrite(re, start);
            fclose(re);
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
        if (move == 'q') {
            //тут должно появляся окно настроек пользователя(смена пароля и логина сразу, не по отдельности)
            while (1) {
                printf("login: ");
                scanf("%s", login);
                printf("password: ");
                scanf("%s", password);
                if (enter(login, password, userb) == 1) break;
            }
            while (strcmp(userb->login, login) != 0) userb = userb->prev;
            printf("New login: ");
            scanf("%s", login);
            printf("New password: ");
            scanf("%s", password);
            while (check_login1(login) != 1 || check_login2(login, start) != 1) {
                if (check_login1(login) != 1) printf("Error! Print the correct login\n");
                else printf("Логин занят\n");
                printf("New login: ");
                gets(login);
            }
            strcpy(userb->login, login);
            while (check_pass(password) != 1) {
                printf("Error! Print the correct password\n");
                printf("New password: ");
                gets(password);
            }
            strcpy(userb->password, password);
        }
        //Добавление в избранное
        if (move == 'l') {
            while (strcmp(userb->login, login) != 0) userb = userb->prev;
            if (userb->fav_size == 0) {
                init(ctlg_love, p->film);
                i++;
            }
            if (userb->fav_size > 0) {
                add(ctlg_love, p->film);
            }
            userb->fav_size++;

        }
        // Открыть список любимых
        if (move == 'z') {
            while (strcmp(userb->login, login) != 0) userb = userb->prev;
            if (userb->fav_size == 0) {
                system("cls");
                printf("У вас нет любимых");
                sleep(1);
                system("cls");
                continue;
            }
            //Передвижение по списку любимых
            catalog *l = ctlg_love;
            while (1) {
                char move_love;
                scanf("%c", &move_love);
                if (move_love == 'b') {
                    FILE *re = fopen("Users.txt", "w");
                    rewrite(re, start);
                    fclose(re);
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
                    l = l->next;
                    printf("\n%s", l->film.name);
                    printf("%s", l->film.release_year);
                    printf("%s", l->film.location);
                    printf("%s", l->film.genre);
                    printf("%s", l->film.rating);
                }
                if (move_love == 'd') {
                    system("cls");
                    l = l->prev;
                    printf("\n%s", l->film.name);
                    printf("%s", l->film.release_year);
                    printf("%s", l->film.location);
                    printf("%s", l->film.genre);
                    printf("%s", l->film.rating);
                }
                if (move_love == 'o') {
                    while (strcmp(userb->login, login) != 0) userb = userb->prev;
                    catalog *dl = l;
                    l = l->prev;
                    del(dl);
                    system("cls");
                    printf("\n%s", l->film.name);
                    printf("%s", l->film.release_year);
                    printf("%s", l->film.location);
                    printf("%s", l->film.genre);
                    printf("%s", l->film.rating);
                    userb->fav_size--;
                }
                FILE *re_fav = fopen(userb->favorite_file, "w");
                rewrite_films(re_fav, l);
                fclose(re_fav);
            }

        }
        //Удаление из films.txt когда user админ
        if (move == 'o' && userb->admin == 1) {
            system("cls");
            catalog *l = ctlg_love;
//            while (strcmp(userb->login, login) != 0) userb = userb->prev;
            for (int j = 0; j < userb->fav_size; j++) {
                printf("%s", l->film.name);
                printf("\n%s", p->film.name);
                if (p->film.name == l->film.name) {
                    catalog *dl = l;
                    userb->fav_size--;
                    del(dl);
                    break;
                } else
                    l = l->prev;
            }
            catalog *d = p;
            p = p->prev;
            del(d);
            printf("\n%s", p->film.name);
            printf("%s", p->film.release_year);
            printf("%s", p->film.location);
            printf("%s", p->film.genre);
            printf("%s", p->film.rating);
        }
        //Добавление нового фильма в films.txt когда user админ
        if (move == 'n' && userb->admin == 1) {
            system("cls");
            film *new_film = (film *) malloc(sizeof(film));

            char trash[128];
            fgets(trash, 128, stdin);

            char name[77];
            printf("Введите название фильма:");
            fgets(name, 77, stdin);
            name[76] = '\n';
            strcpy(new_film->name, name);

            char release_year[6];
            printf("Введите год выпуска фильма:");
            fgets(release_year, 6, stdin);
            release_year[5] = '\0';
            strcpy(new_film->release_year, release_year);

            char location[38];
            printf("Введите страну выпуска фильма:");
            fgets(location, 38, stdin);
            location[37] = '\n';
            strcpy(new_film->location, location);

            char genre[44];
            printf("Введите жанр фильма:");
            fgets(genre, 44, stdin);
            genre[43] = '\n';
            strcpy(new_film->genre, genre);

            char rating[5];
            printf("Введите рейтинг фильма:");
            fgets(rating, 5, stdin);
            rating[4] = '\n';
            strcpy(new_film->rating, rating);

            add(ctlg, *new_film);
        }
    }
    //Перезапись файла films.txt так как может быть админ добавил новый фильм
    FILE *rewrite = fopen("films.txt", "w");
    rewrite_films(rewrite, p);
    return 0;
}

