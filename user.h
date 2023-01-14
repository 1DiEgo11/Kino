#ifndef CINEMA_USER_H
#define CINEMA_USER_H

typedef struct Users{
    char login[20],password[20],card[20];
    int fav_size,admin;
    struct Users *prev;
}Users;

Users read_user(FILE *out);
Users* read_base(FILE *out);
int check_login1(const char s[20]);
int check_pass(const char s[20]);
int check_card(const char s[19]);
void rgister(const char l[20], const char p[20], const char c[19], FILE *out);
void rewrite(FILE *out,Users *start);

#endif //CINEMA_USER_H
