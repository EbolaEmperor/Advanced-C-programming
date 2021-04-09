#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../pstring.h"

#define N 2000

PString* psCreate(const char* s){
    PString* str = (PString*) malloc(sizeof(int) + sizeof(char) * (strlen(s)));
    str -> length = strlen(s);
    memcpy(str -> content, s, sizeof(char) * str -> length);
    return str;
}

void psFree(PString *ps){
    free(ps);
}

void psPrint(const PString* ps){
    for(int i = 0; i < ps -> length; i++)
        putchar(ps -> content[i]);
}

PString* psReadWord(){
    static char s[N];
    char ch = getchar();
    int len = 0;
    while(isspace(ch)) ch = getchar();
    while(!isspace(ch)) s[len++] = ch, ch = getchar();
    s[len] = '\0';
    return psCreate(s);
}

PString* psReadLine(){
    static char s[N];
    char ch = getchar();
    int len = 0;
    while(ch != '\n') s[len++] = ch, ch = getchar();
    s[len] = '\0';
    return psCreate(s);
}

int psLength(const PString* ps){
    return ps -> length;
}

PString* psClone(const PString *ps){
    PString* str = (PString*) malloc(sizeof(int) + sizeof(char) * ps -> length);
    memcpy(str -> content, ps -> content, sizeof(char) * ps -> length);
    str -> length = ps -> length;
    return str;
}

PString* psConcat(const PString* ps1, const PString* ps2){
    PString* str = (PString*) malloc(sizeof(int) + sizeof(char) * (ps1 -> length + ps2 -> length));
    str -> length = ps1 -> length + ps2 -> length;
    memcpy(str -> content, ps1 -> content, sizeof(char) * ps1 -> length);
    memcpy(str -> content + ps1 -> length, ps2 -> content, sizeof(char) * ps2 -> length);
    return str;
}

int psCompare(const PString* ps1, const PString* ps2){
    int n = (ps1 -> length < ps2 -> length) ? ps1 -> length : ps2 -> length;
    for(int i = 0; i < n; i++){
        if(ps1 -> content[i] < ps2 -> content[i]) return -1;
        if(ps1 -> content[i] > ps2 -> content[i]) return 1;
    }
    if(ps1 -> length == ps2 -> length) return 0;
    return (ps1 -> length < ps2 -> length) ? -1 : 1;
}

int psFindChar(const PString* ps, char ch){
    for(int i = 0; i < ps -> length; i++){
        if(ps -> content[i] == ch) return i;
    }
    return -1;
}

int psFindString(const PString* ps1, const PString* ps2){
    for(int i = 0; i < ps1 -> length - ps2 -> length; i++){
        int good = 1;
        for(int j = 0; j < ps2 -> length; j++){
            if(ps1 -> content[i + j] != ps2 -> content[j]){
                good = 0;
                break;
            }
        }
        if(good) return i;
    }
    return -1;
}

PString* psTrim(const PString* ps){
    int begin = 0, end = ps -> length;
    while(begin < end && isspace(ps -> content[begin])) begin ++;
    if(begin == end) return psCreate("");
    while(begin < end && isspace(ps -> content[end - 1])) end --;
    return psSubstring(ps, begin, end);
}

PString* psLower(const PString* ps){
    PString *newp = psClone(ps);
    for(int i = 0; i < newp -> length; i++){
        newp -> content[i] = tolower(newp -> content[i]);
    }
    return newp;
}

PString* psUpper(const PString* ps){
    PString *newp = psClone(ps);
    for(int i = 0; i < newp -> length; i++){
        newp -> content[i] = toupper(newp -> content[i]);
    }
    return newp;
}

PString* psSubstring(const PString* ps, int begin, int end){
    PString *str = (PString*) malloc(sizeof(int) + sizeof(char) * (end - begin));
    str -> length = end - begin;
    memcpy(str -> content, ps -> content + begin, sizeof(char) * (end - begin));
    return str;
}

PString* psReplace(const PString* ps, char ch1, char ch2){
    PString *newp = psClone(ps);
    for(int i = 0; i < ps -> length; i++){
        if(ps -> content[i] == ch1) newp -> content[i] = ch2;
    }
    return newp;
}

char psChar(const PString* ps, int index){
    return ps -> content[index];
}

int psBeginWith(const PString* ps1, const PString* ps2){
    if(ps1 -> length < ps2 ->length){
        return 0;
    }
    return (psCompare(psSubstring(ps1, 0, ps2 -> length), ps2) == 0);
}