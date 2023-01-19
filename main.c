#include <stdio.h >
#include<unistd.h>
#include <stdlib.h>
#include "catalog.h"
#include "user.h"

int main() {
    FILE *out = fopen("Users.txt", "a+");
//    Users user = read_user(out);
    char str[29] = "favorite_";
//    strcat(str, user.login);
//    strcpy(user.favorite_file, str);
//    FILE *user_fav = fopen(user.favorite_file, "a+");
    Users *userb= read_base(out);
    system("chcp 65001");//поддержка русского языка
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
    printf("Чтобы войти, в аккаунт нажмите e, чтобы зарегистрироваться - r\n");
    char move,login[20],password[20];
    scanf("%c",&move);
    //вход (регистрация)
    if (move=='e'){
        while (1){
            printf("login: ");
            scanf("%s",login);
            printf ("password: ");
            scanf("%s",password);
            if( enter(login,password,userb)==1) break;
        }
        printf("Вход успешно выполнен\n");
    }
    else if (move=='r'){
        char card[19];
        printf("login: ");
        scanf("%s",login);
        printf ("password: ");
        scanf("%s",password);
        printf("card: ");
        gets(card);
        gets(card);
        rgister(login,password,card,out,userb);
        printf("Аккаунт успешно зарегистрирован\n");
    }
    fclose(out);
    while (1) {
        FILE *outt= fopen("Users.txt", "a+");
        Users *start= read_base(outt);
//        char move;
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
            while (1){
                printf("login: ");
                scanf("%s",login);
                printf ("password: ");
                scanf("%s",password);
                if( enter(login,password,userb)==1) break;
            }
            while (strcmp(userb->login,login)!=0) userb=userb->prev;
            printf("New login: ");
            scanf("%s",login);
            printf("New password: ");
            scanf("%s",password);
            while (check_login1(login)!=1 || check_login2(login,start)!=1){
                if (check_login1(login)!=1) printf("Error! Print the correct login\n");
                else printf("Логин занят\n");
                printf("New login: ");
                gets(login);
            }
            strcpy(userb->login,login);
            while (check_pass(password)!=1){
                printf("Error! Print the correct password\n");
                printf("New password: ");
                gets(password);
            }
            strcpy(userb->password,password);
            FILE *re= fopen("Users.txt","w");
            rewrite(re,start);
            fclose(re);
        }
        //Добавление в избранное
        if (move == 'l') {
            while (strcmp(userb->login,login)!=0) userb=userb->prev;
            userb->fav_size++;
            printf("%s",userb->login);
            FILE *user_fav = fopen(userb->favorite_file, "a+");
            write_in_love(user_fav, p->film);
            FILE *re= fopen("Users.txt","w");
            rewrite(re,start);
            fclose(re);
        }
        // Открыть список любимых
        if (move == 'z') {
            system("cls");
            catalog *love = (catalog *) malloc(sizeof(catalog));
            film *fov_film = (film *) malloc(sizeof(film));
            FILE *film_love = fopen(userb->favorite_file, "r");
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
        if (move == 'o' && userb->admin == 1){
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

