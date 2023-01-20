#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"


Users read_user(FILE *out){
    char trash[10],c[21],card[20];
    Users user;
    fscanf(out,"%s%s%s%s%s",trash,user.login,trash,user.password,trash);
    fgets(c,21,out);
    for (int i=0;i<20;i++) card[i]=c[i+1];
    fscanf(out,"%s%d%s%d%s%s",trash,&user.fav_size,trash,&user.admin,trash,user.favorite_file);
    strcpy(user.card,card);
//    printf("\nUU\n%s\n%s\n%s\n%d\n%d\n%p\nUU\n\n",user.login,user.password,user.card,user.fav_size,user.admin,&user);
//    printf("\nUU\n%s\n%p\nUU\n\n",user.login,&user);
    return user;
}

Users *initu(FILE *out){
    Users *start,user;
    start=(Users*) malloc(sizeof (Users));
    user= read_user(out);
    strcpy(start->login,user.login);
    strcpy(start->password,user.password);
    strcpy(start->card,user.card);
    strcpy(start->favorite_file,user.favorite_file);
    start->fav_size=user.fav_size;
    start->admin=user.admin;
    start->prev=NULL;
    return start;
}

Users* addu(Users *start,FILE *out){
    Users user,*temp,*p;
    user= read_user(out);
    temp=(Users*) malloc(sizeof (Users));
    p=start;
    strcpy(temp->login,user.login);
    strcpy(temp->password,user.password);
    strcpy(temp->card,user.card);
    strcpy(temp->favorite_file,user.favorite_file);
    temp->fav_size=user.fav_size;
    temp->admin=user.admin;
    temp->prev=p;
//    printf("\nUU\n%s\n%s\n%s\n%d\n%d\n%p\nUU\n\n",temp->login,temp->password,temp->card,temp->fav_size,temp->admin,temp);
    return temp;
}

int check_login1(const char s[20]){
    for (int i = 0; i < 20; ++i) {
        if (s[i]=='\0'){
            if (i>1) return 1;
            else return 0;
        }
        if ((48<=s[i] && s[i]<=57 || 65<=s[i] && s[i]<=90 || 97<=s[i] && s[i]<=122)==0){
            return 0;
        }
    }
    return 1;
}


Users* read_base(FILE *out){
    Users *start,*temp;
    start= initu(out);
    while (fgetc(out)!=EOF){
        temp=start;
        start=addu(start,out);
    }
    start->prev=temp;
    start=start->prev;
    return start;
}

int check_login2(const char s[20],Users *base){
    while (base->prev!=NULL){
        if (strcasecmp(s,base->login)==0) return 0;
        base=base->prev;
    }
    if (strcasecmp(s,base->login)==0) return 0;
    else return 1;
}

int check_pass(const char s[20]){
    int digit=0,low=0,high=0;
    for (int i = 0; i < 20; ++i) {
        if (s[i]=='\0'){
            if (i<6)  return 0;
            else break;
        }
        if ((48<=s[i] && s[i]<=57 || 65<=s[i] && s[i]<=90 || 97<=s[i] && s[i]<=122)==0) return 0;
        if (48<=s[i] && s[i]<=57) digit++;
        if (65<=s[i] && s[i]<=90) high++;
        if (97<=s[i] && s[i]<=122) low++;
    }
    if (digit==0 || high==0 || low==0) return 0;
    else return 1;
}

int check_card(const char s[19]){
    int count=0;
    for (int i=0;i<19;++i){
        if(48<=s[i] && s[i]<=57) count+=1;
        else if (s[i]!=' ') return 0;
    }
    if (count==16) return 1;
    else return 0;
}

void rgister(const char l[20], const char p[20], const char c[19], FILE *out,Users *base){
    char lp[20],card[19];
    int a=0;
    if (check_login1(l)!=1 || check_login2(l,base)!=1){
        if (check_login1(l)!=1) printf("Error! Print the correct login\n");
        else printf("Логин занят\n");
        printf("login: ");
        gets(lp);
        while (check_login1(lp)!=1 || check_login2(lp,base)!=1){
            if (check_login1(lp)!=1) printf("Error! Print the correct login\n");
            else printf("Логин занят\n");
            printf("login: ");
            gets(lp);
            a+=1;
        }
        fprintf(out,"login: %s\n",lp);
    }
    else fprintf(out,"login: %s\n",l);
    if (check_pass(p)!=1){
        printf("Error! Print the correct password\n");
        printf("password: ");
        gets(lp);
        while (check_pass(lp)!=1){
            printf("Error! Print the correct password\n");
            printf("password: ");
            gets(lp);
        }
        fprintf(out,"password: %s\n",lp);
    }
    else fprintf(out,"password: %s\n",p);
    if (check_card(c)!=1){
        printf("Error! Print the correct card\n");
        printf("card: ");
        gets(card);
        while (check_card(card)!=1){
            printf("Error! Print the correct card\n");
            printf("card: ");
            gets(card);
        }
        fprintf(out,"card: %s\n",card);
    }
    else fprintf(out,"card: %s\n",c);
    fprintf(out,"favorite: %d\n",0);
    fprintf(out,"isAdmin: %d\n",0);
    char fav[29]="favorite_";
    if (a!=0) strcat(fav,lp);
    else strcat(fav,l);
    fprintf(out,"isAdmin: %s\n\n\n",fav);
}

int enter(const char l[20],const char p[20],Users *base){
    while (base->prev!=NULL){
//        printf("%s\n",base->login);
        if (strcasecmp(base->login,l)==0){
            if  (strcmp(base->password,p)==0) return 1;
            else {
                printf("Error! Wrong password!\n");
                return 0;
            }
        }
        base=base->prev;
    }
    if (strcasecmp(base->login,l)==0){
        if  (strcmp(base->password,p)==0) return 1;
        else {
            printf("Error! Wrong password!\n");
            return 0;
        }
    }
    else {
        printf("Wrong login\n");
        return 0;
    }
}

void rewrite(FILE *out,Users *start) {
    while (start->prev != NULL) {
        fprintf(out, "login: %s\n", start->login);
        fprintf(out, "password: %s\n", start->password);
        fprintf(out, "card: %s\n", start->card);
        fprintf(out, "favorite: %d\n", start->fav_size);
        fprintf(out, "isAdmin: %d\n", start->admin);
        fprintf(out, "favoritef: %s\n\n\n", start->favorite_file);
        start = start->prev;
    }
    fprintf(out, "login: %s\n", start->login);
    fprintf(out, "password: %s\n", start->password);
    fprintf(out, "card: %s\n", start->card);
    fprintf(out, "favorite: %d\n", start->fav_size);
    fprintf(out, "isAdmin: %d\n", start->admin);
    fprintf(out, "favoritef: %s\n\n\n", start->favorite_file);
}