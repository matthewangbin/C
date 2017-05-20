//
//  main.c
//  string_heap
//
//  Created by matthew on 2017/5/20.
//  Copyright © 2017年 matthew. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define  OK  1
#define  FALSE  0
#define  TRUE  1
#define  ERROR  0
#define  INFEASIBLE  -1
#define  OVERFLOW  -2
typedef int Status;
typedef struct
{
    char *ch;
    int length;
}Hstring;
Status StrAssign(Hstring *T,char *chars);
int StrLength(Hstring S);
Status ClearString(Hstring *S);
int Strcompare(Hstring S,Hstring T);
Status Concat(Hstring *T,Hstring S1,Hstring S2);
Status SubString(Hstring *Sub,Hstring S,int pos,int len);
Status StrCopy(Hstring *T,Hstring S);
Status StrInsert(Hstring *S,int pos,Hstring T);
Status StrDelete(Hstring *S,int pos,int len);
Status Index(Hstring S,Hstring T,int pos );
Status Replace(Hstring *S,Hstring T,Hstring V);
int main()
{
    char *c="abdd12345ijk",*d="12",*e="ttttt";
    int len;
    Hstring T,V,S,S1,S2,Sub;
    StrAssign(&S1,c);
    //printf("%c",S1.ch[0]);
    // StrAssign(&S2,d);
    // printf("%s\n %d",S1.ch,S1.length);
    //printf("%s %d\n",T.ch,T.length);
    //ClearString(&T);
    //SubString(&T,S1,7,4);
    StrAssign(&T,d);
    StrAssign(&S2,e);
    // printf("%s\n",T.ch);
    Replace(&S1,T,S2);
    printf("%s",S1.ch);
}
Status StrAssign(Hstring *T,char *chars)
{
    int i;
    char *c=chars;
    for(i=0;*c;i++,c++);
    T->length=i;
    T->ch=(char *)malloc((i+2)*sizeof(char));
    if(!T->ch)
    {
        printf("error\n");
        exit(-1);
    }
    for(i=0,c=chars;i<T->length;i++)
    {
        T->ch[i]=*c;
        c++;
    }
    T->ch[i]='\0';
    return OK;
}
int StrLength(Hstring S)
{
    return S.length;
}
Status ClearString(Hstring *S)
{
    S->length=0;
    free(S->ch);
    S->ch=NULL;
    return OK;
}
int Strcompare(Hstring S,Hstring T)
{
    int i;
    for(i=0;i<S.length&&i<T.length;i++)
    {
        if(S.ch[i]!=T.ch[i])
            return S.ch[i]-T.ch[i];
    }
    return S.length-T.length;
}
Status Concat(Hstring *T,Hstring S1,Hstring S2)
{
    int i,j;
    // if(T->ch) free(T->ch);//
    T->ch=(char *)malloc((S1.length+S2.length+1)*sizeof(char));
    for(i=0;i<S1.length;i++)
    {
        T->ch[i]=S1.ch[i];
    }
    for(i=S1.length,j=0;j<S2.length;j++)
    {
        T->ch[i++]=S2.ch[j];
    }
    T->ch[i]='\0';
    T->length=S1.length+S2.length;
    return OK;
}
Status SubString(Hstring *Sub,Hstring S,int pos,int len)
{
    int i,j;
    if(pos<0||len<0||pos>S.length||len>S.length-pos+1)
    {
        printf("error\n");
        return INFEASIBLE;
    }
    if(len==0)
    {
        Sub->ch=NULL;
        Sub->length=0;
    }
    else
    {
        Sub->ch=(char *)malloc((len+1)*sizeof(char));
        Sub->length=len;
        for(i=0,j=pos-1;i<len;i++,j++)
        {
            Sub->ch[i]=S.ch[j];
        }
        Sub->ch[i]='\0';
    }
    return OK;
}
Status StrCopy(Hstring *T,Hstring S)
{
    int i;
    T->length=S.length;
    T->ch=(char *)malloc((S.length+1)*sizeof(char));
    for(i=0;i<S.length;i++)
        T->ch[i]=S.ch[i];
    T->ch[i]='\0';
    return OK;
}
Status StrInsert(Hstring *S,int pos,Hstring T)
{
    //pos=2 wrong?
    int i,j,k;
    if(pos<1||pos>S->length+1)
    {
        printf("error\n");
        return INFEASIBLE;
    }
    if(T.length)
    {
        if(!(S->ch=(char *)realloc(S->ch,(S->length+T.length+1)*sizeof(char))))
        {
            printf("error\n");
            exit(OVERFLOW);
        }
        for(i=S->length-1;i>=pos-1;i--)
        {
            S->ch[i+T.length]=S->ch[i];
        }
        for(j=0,i=pos-1;j<T.length;j++,i++)
        {
            S->ch[i]=T.ch[j];
        }
        S->length+=T.length;
        S->ch[S->length]='\0';
    }
    return OK;
}
Status StrDelete(Hstring *S,int pos,int len)
{
    int i=1,j,k,m,n;
    if(pos<1||len>S->length||pos+len>S->length+1)
    {
        printf("error\n");
        return INFEASIBLE;
    }
    while(i<=len)
    {
        for(m=S->length,j=pos-1;j<m;j++)
        {
            S->ch[j]=S->ch[j+1];
        }
        i++;
    }
    S->length-=len;
    return OK;
}
Status Index(Hstring S,Hstring T,int pos)
{
    int n,m,i;
    Hstring Sub;
    if(pos>0)
    {
        n=StrLength(S);
        m=StrLength(T);
        i=pos;
        while(i<=n-m+1)
        {
            SubString(&Sub,S,i,m);
            if(Strcompare(Sub,T)!=0)
                ++i;
            else
                return i;
        }
    }
    return FALSE;
}
Status Replace(Hstring *S, Hstring T, Hstring V)
{
    int i=1,j=1,m=StrLength(T),n=StrLength(V);
    while(i<=S->length)          //遍历所有的字符
    {
        j=Index(*S,T,i);         //查找匹配字串的位置
        if(j > 0)                //查找到字串
        {
            StrDelete(S,j,m);    //删除字串
            StrInsert(S,j,V);    //插入替换字串
        }
        i+=n+1;
    }
    return OK;
}
