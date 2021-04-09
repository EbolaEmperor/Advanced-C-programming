#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
typedef struct node
{   
  int coef;             /* 系数 */
  int exp;              /* 指数 */
  struct node *next;
} polynomial;

//--------------------------------------------------------------------------
// 注：虚线框内部分是本地测试所必要的，无需提交
polynomial * create_polynomial();
void print_polynomial(polynomial *poly);
polynomial * add_polynomial(polynomial *polyA, polynomial *polyB);
polynomial * subtract_polynomial(polynomial *polyA, polynomial *polyB);
polynomial * multiply_polynomial(polynomial *polyA, polynomial *polyB);
//--------------------------------------------------------------------------


/* 提示：递交的答案将会自动插入此处 */

int main(void)
{
    polynomial *polyA,*polyB;     

    polyA=create_polynomial();  /* 其中函数create_polynomial()用于读入并创建多项式A的链表，请自行实现 */ 
    polyB=create_polynomial();  /* 读入并创建多项式B的链表 */
    printf("A=");
    print_polynomial(polyA);   /* 输出多项式A */
    printf("B=");
    print_polynomial(polyB);  /* 输出多项式B */

    printf("A+B=");
    print_polynomial(add_polynomial(polyA,polyB) );
    printf("A-B=");
    print_polynomial(subtract_polynomial(polyA,polyB) );
    printf("A*B=");
    print_polynomial(multiply_polynomial(polyA,polyB));
    return 0;
}

/* 请在这里填写答案 */

//  输出函数非常坑，这里记录一下
//  坑点一：若系数已经有负号则不要再输出+
//  坑点二：系数为1或-1时应当根据习惯有所省略
//  坑点三：次数为零应该省略x^0
//  坑点四：次数为一应省略^1
void print(polynomial *p, int *isFirst){
    if(p -> coef){
        if(*isFirst){
            *isFirst = 0;
        } else {
            if(p -> coef > 0) printf("+");
        }
        if(p -> exp == 0){
            printf("%d", p -> coef);
        } else if(p -> exp == 1){
            if(p -> coef == 1) printf("x");
            else if(p -> coef == -1) printf("-x");
            else printf("%dx", p -> coef);
        } else {
            if(p -> coef == 1) printf("x^%d", p -> exp);
            else if(p -> coef == -1) printf("-x^%d", p -> exp);
            else printf("%dx^%d", p -> coef, p -> exp);
        }
    }
}

void removeNext(polynomial *p){
    polynomial *q = p -> next;
    p -> next = q -> next;
    free(q);
}

polynomial * insertNext(polynomial *p, int coef, int exp){
    p -> next = (polynomial *) malloc(sizeof(polynomial));
    p = p -> next;
    p -> coef = coef;
    p -> exp = exp;
    p -> next = NULL;
    return p;
}

void swapValue(polynomial *p, polynomial *q){
    int coef = p -> coef;
    int exp = p -> exp;
    p -> coef = q -> coef;
    p -> exp = q -> exp;
    q -> coef = coef;
    q -> exp = exp;
}

void sort_polynomial(polynomial *poly){
    for(polynomial *p = poly; p -> next; p = p -> next){
        for(polynomial *q = p; q -> next; q = q -> next){
            if(q -> next -> exp > p -> next -> exp){
                swapValue(p -> next, q -> next);
            }
        }
    }
}

void add_coef(polynomial *poly, int coef, int exp){
    while(poly -> next){
        if(poly -> next -> exp == exp){
            poly -> next -> coef += coef;
            return;
        }
        poly = poly -> next;
    }
    poly = insertNext(poly, coef, exp);
}

polynomial * create_polynomial(){
    polynomial *head = (polynomial *) malloc(sizeof(polynomial));
    head -> next = NULL;
    int n, coef, exp;
    scanf("%d", &n);
    while(n--){
        scanf("%d %d", &coef, &exp);
        add_coef(head, coef, exp);
    }
    sort_polynomial(head);
    return head;
}

void print_polynomial(polynomial *poly){
    polynomial *p = poly;
    int *isFirst = (int*) malloc(sizeof(int));
    *isFirst = 1;
    while(p -> next){
        print(p -> next, isFirst);
        p = p -> next;
    }
    if(*isFirst) printf("0");
    printf("\n");
}

polynomial * add_polynomial(polynomial *polyA, polynomial *polyB){
    polynomial *res = (polynomial *) malloc(sizeof(polynomial));
    res -> next = NULL;
    for(; polyA -> next; polyA = polyA -> next){
        add_coef(res, polyA -> next -> coef, polyA -> next -> exp);
    }
    for(; polyB -> next; polyB = polyB -> next){
        add_coef(res, polyB -> next -> coef, polyB -> next -> exp);
    }
    sort_polynomial(res);
    return res;
}

polynomial * subtract_polynomial(polynomial *polyA, polynomial *polyB){
    polynomial *res = (polynomial *) malloc(sizeof(polynomial));
    res -> next = NULL;
    for(; polyA -> next; polyA = polyA -> next){
        add_coef(res, polyA -> next -> coef, polyA -> next -> exp);
    }
    for(; polyB -> next; polyB = polyB -> next){
        add_coef(res, - polyB -> next -> coef, polyB -> next -> exp);
    }
    sort_polynomial(res);
    return res;
}

polynomial * multiply_polynomial(polynomial *polyA, polynomial *polyB){
    polynomial *res = (polynomial *) malloc(sizeof(polynomial));
    res -> next = NULL;
    for(polynomial *p = polyA; p -> next; p = p -> next){
        for(polynomial *q = polyB; q -> next; q = q -> next){
            add_coef(res, p -> next -> coef * q -> next -> coef, p -> next -> exp + q -> next -> exp);
        }
    }
    sort_polynomial(res);
    return res;
}