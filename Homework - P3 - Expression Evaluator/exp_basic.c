#include <stdio.h>
#include <ctype.h>

int lower(char op1, char op2){  //判断运算符op1的优先级是否比op2更低
    return (op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/' || op2 == '%');
}

int calc(int a, int b, char op){
    switch (op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '%': return a % b;
    }
}

int work(){
    int res = 0, lastnum = 0;
    char lastop = '\0', op = '\0';
    static char lastch = '\0';
    char ch = getchar();
    while(!isspace(ch)){
        int x = 0, needcalc = 0;
        if(isdigit(ch) || ch == '-' && !isdigit(lastch) && lastch != ')'){
            int fg = 1;
            if(ch == '-') fg = -1, lastch = ch, ch = getchar();
            while(isdigit(ch)) x = x * 10 + (ch - '0'), lastch = ch, ch = getchar();
            x *= fg;
            needcalc = 1;
        } else {
            if(ch == '(') x = work(), needcalc = 1;
            else if(ch == ')') break;
            else {
                if(!lastop) lastop = ch;
                else op = ch;
            }
            lastch = ch, ch = getchar();
        }

        if(needcalc){
            if(!lastop) res = x;
            else if(!op) lastnum = x;
            else{
                if(lower(lastop, op)){
                    lastnum = calc(lastnum, x, op);
                } else {
                    res = calc(res, lastnum, lastop);
                    lastnum = x;
                    lastop = op;
                }
                op = '\0';
            }
        }
    }
    if(lastop) res = calc(res, lastnum, lastop);
    return res;
}

int main(){
    printf("%d\n", work());
    return 0;
}