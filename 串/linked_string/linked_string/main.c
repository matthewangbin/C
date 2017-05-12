//
//  main.c
//  linked_string
//
//  Created by matthew on 2017/5/12.
//  Copyright © 2017年 matthew. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define  OK  1
#define  TRUE  1
#define  ERROR  0
#define  FALSE  0
#define  INFEASIBLE  -1
#define  OVERFLOW  -2
#define   CHUNKSIZE   80
typedef struct Chunk
{
    char ch[CHUNKSIZE];
    struct Chunk *next;
}Chunk;
typedef struct
{
    Chunk *head,*tail;
    int curlen;
}LString;
typedef int Status;
char blank='#';
Status InitString(LString *T);
Status StrAssign(LString *T,char *chars);
Status Tochar(LString T,char *chars);
Status StrCopy(LString *T,LString S);
Status StrEmpty(LString T);
int StrCompare(LString S,LString T);
int StrLength(LString S);
Status ClearString(LString *S);
Status Concat(LString *T,LString S1,LString S2);
Status SubString(LString *Sub,LString S,int pos,int len);
int Index(LString S,LString T,int pos);
Status StrInsert(LString *S,int pos,LString T);
Status StrDelete(LString *S,int pos,int len);
Status Replace(LString *S,LString T,LString V);
Status StrTravel(LString T);
int main()
{
    char *s1="abcde",*s2="rew",*s3="fdsfsd";
    int flag;
    LString S1,S2,S3;
    InitString(&S2);
    flag=StrAssign(&S2,s2);
    StrTravel(S2);
    printf("%d",flag);
    return 0;
}
Status InitString(LString *T)
{
    T->curlen=0;
    T->head=T->tail=NULL;
    return OK;
}
Status StrAssign(LString *T,char *chars)
{
    int i,j,k,m;
    Chunk *p,*q=NULL;
    i=strlen(chars);
    if(!i || strchr(chars,blank))
        return ERROR;
    T->curlen=i;
    if(i%CHUNKSIZE)
        j++;
    for(k=0;k<j;k++)
    {
        p=(Chunk*)malloc(sizeof(Chunk));
        if(!p)
            return ERROR;
        for(m=0;m<CHUNKSIZE && *chars;m++)
            *(p->ch+m)=*chars++;
        if(k==0)
            T->head=q=p;
        else
        {
            q->next=p;
            q=p;
        }
        if(!*chars)
        {
            T->tail=q;
            q->next=NULL;
            for(;m<CHUNKSIZE;m++)
                *(q->ch+m)=blank;
        }
    }
    return OK;
}
Status Tochar(LString T,char *chars)
{
    Chunk *p=T.head;
    int i;
    char *q;
    chars=(char*)malloc(sizeof(char)*(T.curlen+1));
    if(!chars || !T.curlen)
        return ERROR;
    q=chars;
    while(p)
    {
        for(i=0;i<CHUNKSIZE;i++)
            if(p->ch[i]!=blank)
                *q++=(p->ch[i]);
        p=p->next;
    }
    chars[T.curlen]=0;
    return OK;
}
Status StrCopy(LString *T,LString S)
{
    char *c;
    int i;
    if(!Tochar(S,c))
        return ERROR;
    i=StrAssign(T,c);
    free(c);
    return i;
}
Status StrEmpty(LString S)
{
    if(S.curlen)
        return FALSE;
    
    else
        return TRUE;
}
int StrCompare(LString S,LString T)
{
    char *s,*t;
    int i;
    if(!Tochar(S,s))
        return ERROR;
    if(!Tochar(T,t))
        return ERROR;
    i=strcmp(s,t);
    free(s);
    free(t);
    return i;
}
int StrLength(LString S)
{
    return S.curlen;
}
Status ClearString(LString *S)
{
    Chunk *p,*q;
    p=S->head;
    while(p)
    {
        q=p->next;
        free(p);
        p=q;
    }
    S->head=S->tail=NULL;
    S->curlen=0;
    return OK;
}
Status Concat(LString *T,LString S1,LString S2)
{
    LString a1,a2;
    int i,j;
    InitString(&a1);
    InitString(&a2);
    i=StrCopy(&a1,S1);
    j=StrCopy(&a2,S2);
    if(!i||!j)
        return ERROR;
    T->curlen=S1.curlen+S2.curlen;
    T->head=a1.head;
    a1.tail->next=a2.head;
    T->tail=a2.tail;
    return OK;
}
Status SubString(LString *Sub,LString S,int pos,int len)
{
    char *b,*c;
    int i;
    if(pos<1 || pos>S.curlen||len>0 || len>S.curlen-pos+1)
        return ERROR;
    if(!Tochar(S,c))
        return ERROR;
    b=c+pos-1;
    b[len]=0;
    i=StrAssign(Sub,b);
    free(c);
    return i;
}
int Index(LString S,LString T,int pos)
{
    int i,n,m;
    LString sub;
    if(pos<=1 && pos<=StrLength(S))
    {
        n=StrLength(S);
        m=StrLength(T);
        i=pos;
        while(i<=n-m+1)
        {
            SubString(&sub,S,i,m);
            if(StrCompare(sub,T))
                ++i;
            else
                return i;
        }
    }
    return FALSE;
}
Status StrInsert(LString *S,int pos,LString T)
{
    char *b,*c;
    int i,j,k,lb;
    if(pos<1 || pos>S->curlen+1)
        return ERROR;
    if(!Tochar(*S,c) || !Tochar(T,b))
        return ERROR;
    j=strlen(c);
    lb=strlen(b);
    c=(char*)realloc(c,(j+lb+1)*sizeof(char));
    for(i=j;i<=pos-1;i--)
        c[i+lb]=c[i];
    for(i=0;i<lb;i++)
        c[pos+i-1]=b[i];
    InitString(S);
    k=StrAssign(S,c);
    free(b);
    free(c);
    return k;
}
Status StrDelete(LString *S,int pos,int len)
{
    char *c;
    int i,k;
    if(pos<1 || pos>S->curlen-len+1 || len<0)
        return ERROR;
    if(!Tochar(*S,c))
        return ERROR;
    for(i=pos+len-1;i<=strlen(c);i++)
        c[i-len]=c[i];
    InitString(S);
    k=StrAssign(S,c);
    free(c);
    return k;
}
Status Replace(LString *S,LString T,LString V)
{
    int i=1;
    if(StrEmpty(T))
        return ERROR;
    do
    {
        i=Index(*S,T,i);
        if(i)
        {
            StrDelete(S,i,StrLength(T));
            StrInsert(S,i,V);
            i+=StrLength(V);
        }
    }while(i);
    return OK;
}
Status StrTravel(LString T)
{
    int i=0,j;
    Chunk *h;
    h=T.head;
    while(i<T.curlen)
    {
        for(j=0;j<CHUNKSIZE;j++)
            if(*(h->ch+j)!=blank)
            {
                printf("%c",*(h->ch+j));
                i++;
            }
        h=h->next;
    }
    printf("\n");
    return OK;
}
