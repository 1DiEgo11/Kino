#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user.h"


Users read_user(FILE *out){
    char trash[10],c[21],card[20];
    int fav,adm,cr1;
    Users user;
    fscanf(out,"%s%s%s%s%s",trash,user.login,trash,user.password,trash);
    fgets(c,21,out);
    for (int i=0;i<20;i++) card[i]=c[i+1];
    fscanf(out,"%s%d%s%d",trash,&user.fav_size,trash,&user.admin);
    strcpy(user.card,card);
    printf("%s\n%s\n%s\n",user.login,user.password,card);
    printf("%d\n%d\n\n",user.fav_size,user.admin);
    return user;
}

Users* read_base(FILE *out){
    Users *start,*temp,user;
    user= read_user(out);
    temp=(Users*) malloc(sizeof (Users));
    strcpy(temp->login,user.login);
    strcpy(temp->password,user.password);
    strcpy(temp->card,user.card);
    temp->fav_size=user.fav_size;
    temp->admin=user.admin;
    temp->prev=NULL;
    start=temp;
    while (fgetc(out)!=EOF){
        user= read_user(out);
        temp=(Users*) malloc(sizeof (Users));
        strcpy(temp->login,user.login);
        strcpy(temp->password,user.password);
        strcpy(temp->card,user.card);
        temp->fav_size=user.fav_size;
        temp->admin=user.admin;
        temp->prev=start;
        start=temp;
        char t[2];
        fgets(t,2,out);
        fgets(t,2,out);
        fgets(t,2,out);
    }
    return start;
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

int chek_login2(const char s[20],FILE *out){
    Users *base;
    while
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

void rgister(const char l[20], const char p[20], const char c[19], FILE *out){
    char lp[20],card[19];
    if (check_login1(l)!=1){
        printf("Error! Print the correct login\n");
        gets(lp);
        while (check_login1(lp)!=1){
            printf("Error! Print the correct login\n");
            gets(lp);
        }
        fprintf(out,"login: %s\n",lp);
    }
    else fprintf(out,"login: %s\n",l);
    if (check_pass(p)!=1){
        printf("Error! Print the correct password\n");
        gets(lp);
        while (check_pass(lp)!=1){
            printf("Error! Print the correct password\n");
            gets(lp);
        }
        fprintf(out,"password: %s\n",lp);
    }
    else fprintf(out,"password: %s\n",p);
    if (check_card(c)!=1){
        printf("Error! Print the correct card\n");
        gets(card);
        while (check_card(card)!=1){
            printf("Error! Print the correct card\n");
            gets(card);
        }
        fprintf(out,"card: %s\n",card);
    }
    else fprintf(out,"card: %s\n",c);
    fprintf(out,"favorite: %d\n",0);
    fprintf(out,"isAdmin: %d\n\n\n",0);
}

void rewrite(FILE *out,Users *start){
    while (start->prev!=NULL){
        fprintf(out,"login: %s\n",start->login);
        fprintf(out,"password: %s\n",start->password);
        fprintf(out,"card: %s\n",start->card);
        fprintf(out,"favorite: %d\n",start->fav_size);
        fprintf(out,"isAdmin: %d\n\n\n",start->admin);
        start=start->prev;
    }
    fprintf(out,"login: %s\n",start->login);
    fprintf(out,"password: %s\n",start->password);
    fprintf(out,"card: %s\n",start->card);
    fprintf(out,"favorite: %d\n",start->fav_size);
    fprintf(out,"isAdmin: %d\n\n\n",start->admin);
}