#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct stack{
    int val;
    struct stack* next;
};

int top(struct stack *st){
    return st -> val;
}

struct stack* pop(struct stack* st){
    struct stack* p = st -> next;
    free(st);
    return p;
}

struct stack* push(struct stack* st, int x){
    struct stack* p = (struct stack*)malloc(sizeof(struct stack));
    p -> val = x;
    p -> next = st;
    return p;
}

int priority(char op){
    switch(op){
        case '~': return 2;
        case '*': case '/': case '%': return 3;
        case '+': case '-': return 4;
        case '<': case '>': return 5;
        case '&': return 6;
        case '^': return 7;
        case '|': return 8;
    }
}

int calc(int a, int b, char op){
    switch(op){
        case '*': return a * b;
        case '/': return a / b;
        case '%': return a % b;
        case '+': return a + b;
        case '-': return a - b;
        case '<': return a << b;
        case '>': return a >> b;
        case '&': return a & b;
        case '^': return a ^ b;
        case '|': return a | b;
    }
}

void deal(struct stack** op, struct stack** num, int pri){
    struct stack* opt = *op;
    struct stack* numt = *num;
    while(opt && priority(top(opt)) <= pri){
        char p = top(opt); opt = pop(opt);
        if(p == '~'){
            int a = top(numt); numt = pop(numt);
            numt = push(numt, ~a);
        } else {
            int b = top(numt); numt = pop(numt);
            int a = top(numt); numt = pop(numt);
            numt = push(numt, calc(a, b, p));
        }
    }
    *op = opt;
    *num = numt;
}

int work(){
    static char lastch = '\0';
    char ch = getchar();
    struct stack* op = NULL;
    struct stack* num = NULL;
    while(!isspace(ch)){
        if(isdigit(ch) || ch == '-' && !isdigit(lastch) && lastch != ')'){
            int x = 0, fg = 1;
            if(ch == '-') fg = -1, lastch = ch, ch = getchar();
            while(isdigit(ch)) x = x * 10 + (ch - '0'), lastch = ch, ch = getchar();
            num = push(num, x * fg);
        } else {
            if(ch == '(') num = push(num, work());
            else if(ch == ')') break;
            else{
                deal(&op, &num, priority(ch));
                op = push(op, ch);
            }
            lastch = ch, ch = getchar();
        }
    }
    deal(&op, &num, 8);
    return top(num);
}

int main(){
    printf("%d\n", work());
    return 0;
}