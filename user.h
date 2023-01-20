#ifndef CINEMA_USER_H
#define CINEMA_USER_H

typedef struct Users{
    char login[20],password[20],card[20];
    int fav_size,admin;
    struct Users *prev;
    char favorite_file[29];
}Users;

Users read_user(FILE *out);
Users *initu(FILE *out);
int check_login1(const char s[20]);
Users* addu(Users *start,FILE *out);
Users* read_base(FILE *out);
Users* getlast(Users *start);
int check_login2(const char s[20],Users *base);
int check_pass(const char s[20]);
int check_card(const char s[19]);
void rgister(const char l[20], const char p[20], const char c[19], FILE *out,Users *base);
int enter(const char l[20],const char p[20],Users *base);
void rewrite(FILE *out,Users *start);

#endif //CINEMA_USER_H
