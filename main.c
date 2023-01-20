#include <stdio.h >
#include<unistd.h>
#include <stdlib.h>
#include "catalog.h"
#include "user.h"
#include "draw_A.h"
#include "drawing.h"

const unsigned short DEFAULT_WINDOW_WIDTH = 45;

void draw_movie_info_window(catalog *p) {
    // Размеры окна
    const unsigned short width = DEFAULT_WINDOW_WIDTH;
    const unsigned short height = 15;

    // Координаты левого верхнего угла окна
    short x = calculate_window_x(width);
    short y = calculate_window_y(height);

    char *content[] = {p->film.name,
                       p->film.genre,
                       p->film.location,
                       p->film.rating,
                       "",
                       p->film.release_year};

    clear_viewport();
    draw_stars_around_window(x, y, width, height);
    draw_window(x, y, width, height, content, 6);
}

int main() {
    hello();

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

    rl();
    char move, login[20], password[20];
    scanf("%c", &move);
    //вход (регистрация)
    if (move == 'e') {
        system("cls");
        while (1) {
            a(8);
            b(8);
            printf("!LOG IN!");
            a(4);
            b(8);
            printf("USER NAME\n\n");
            b(8);
            scanf("%s", login);
            a(2);
            b(8);
            printf("PASSWORD\n\n");
            b(8);
            scanf("%s", password);
            b(8);
            if (enter(login, password, userb) == 1) break;
        }
        printf("Вход успешно выполнен\n");
    } else if (move == 'r'){
        system("cls");
        char card[19];
        a(8);
        b(7);
        printf("!REGISTR ACCOUNT!");
        a(4);
        b(6);
        printf("   USER NAME(до 15 символов)\n\n");
        b(8);
        scanf("%s", login);
        a(2);
        b(6);
        printf("    PASSWORD(до 20 символов)\n\n");
        b(8);
        scanf("%s", password);
        a(2);
        b(7);
        printf("   CARD NOMBER\n\n");
        b(8);
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
    system("cls");
    a(3);
    b(7);
    printf("Настройки\n");
    b(7);
    printf("(press q)");
    a(2);
    b(7);
    printf("Избранное\n");
    b(7);
    printf("(press za)\n");
    a(2);
    b(7);
    printf("Все фильмы\n");
    b(7);
    printf("(press a)\n");
    b(7);
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
            draw_movie_info_window(p);
//            printf("\n%s", p->film.name);
//            printf("%s", p->film.release_year);
//            printf("%s", p->film.location);
//            printf("%s", p->film.genre);
//            printf("%s", p->film.rating);
        }
        //В списке всех фильмов передвижение ВПРАВО
        if (move == 'd') {
            system("cls");
            p = p->prev;
            draw_movie_info_window(p);
//            printf("\n%s", p->film.name);
//            printf("%s", p->film.release_year);
//            printf("%s", p->film.location);
//            printf("%s", p->film.genre);
//            printf("%s", p->film.rating);
        }
        if (move == 'q') {
            system("cls");
            a(8);
            b(6);
            printf("СМЕНА ДАННЫХ");
            while (1) {
                a(4);
                b(6);
                printf("USER NAME\n\n");
                b(6);
                scanf("%s", login);
                a(2);
                b(6);
                printf("PASSWORD)\n\n");
                b(6);
                scanf("%s", password);
                a(2);
                b(8);
                if (enter(login, password, userb) == 1) break;
            }
            system("cls");
            while (strcmp(userb->login, login) != 0) userb = userb->prev;
            a(8);
            b(6);
            printf("Смена ДАННЫХ");
            a(4);
            b(6);
            printf("NEW USER NAME(до 15 символов)\n\n");
            b(8);
            scanf("%s", login);
            a(2);
            b(6);
            printf("NEW PASSWORD(до 20 символов)\n\n");
            b(8);
            scanf("%s\n", password);
            while (check_login1(login) != 1 || check_login2(login, start) != 1) {
                if (check_login1(login) != 1) printf("\t\t\t\t\tError! Print the correct login\n");
                else printf("\t\t\t\t\tЛогин занят\n");
                a(2);
                b(6);
                printf("NEW USER NAME(до 20 символов)\n\n");
                gets(login);
                b(8);
            }
            strcpy(userb->login, login);
            while (check_pass(password) != 1) {
                printf("\t\t\t\t\tError! Print the correct password\n");
                a(2);
                b(6);
                printf("NEW PASSWORD(до 20 символов)\n\n");
                gets(password);
                b(8);
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
                a(2);
                b(7);
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
                    draw_movie_info_window(l);
//                    printf("\n%s", l->film.name);
//                    printf("%s", l->film.release_year);
//                    printf("%s", l->film.location);
//                    printf("%s", l->film.genre);
//                    printf("%s", l->film.rating);
                }
                if (move_love == 'd') {
                    system("cls");
                    l = l->prev;
                    draw_movie_info_window(l);
//                    printf("\n%s", l->film.name);
//                    printf("%s", l->film.release_year);
//                    printf("%s", l->film.location);
//                    printf("%s", l->film.genre);
//                    printf("%s", l->film.rating);
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
                if (strcmp(p->film.name, l->film.name) == 0) {
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
            draw_movie_info_window(p);
//            printf("\n%s", p->film.name);
//            printf("%s", p->film.release_year);
//            printf("%s", p->film.location);
//            printf("%s", p->film.genre);
//            printf("%s", p->film.rating);
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

