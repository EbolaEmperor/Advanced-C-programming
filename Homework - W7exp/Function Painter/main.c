#include "acllib.h"
#include <string.h>
#include <stdio.h>

#define GRAY RGB(50, 50, 50)

typedef struct{
    int n;
    double coef[];
} Polynomial;

double getValue(Polynomial* poly, double x){
    double y = 0, powx = 1;
    for(int i = 0; i < poly -> n; i ++){
        y += poly -> coef[i] * powx;
        powx *= x;
    }
    return y;
}

Polynomial* readPoly(){
    int n;
    scanf("%d", &n);
    Polynomial *poly = (Polynomial*) malloc(sizeof(int) + sizeof(double) * n);
    poly -> n = n;
    for(int i = n - 1; i >= 0; i--){
        scanf("%lf", & poly -> coef[i]);
    }
    return poly;
}

int Setup(){

    //处理读入数据，确定坐标范围
    initConsole();
    Polynomial *poly = readPoly();
    double arrlx, arrrx;
    scanf("%lf%lf", &arrlx, &arrrx);
    double step = (arrrx - arrlx) / 1000.0;
    double arrly = 1e20, arrry = -1e20;
    for(double x = arrlx; x <= arrrx; x += step){
        double y = getValue(poly, x);
        if(y < arrly) arrly = y;
        if(y > arrry) arrry = y;
    }
    initWindow("Function Painter", 200, 200, 800, 500);
    beginPaint();
    double minx = min(arrlx, 0);
    double maxx = max(arrrx, 0);
    double miny = min(arrly, 0);
    double maxy = max(arrry, 0);
    double scaleX = 780.0 / (maxx - minx);
    double scaleY = 480.0 / (maxy - miny);

    //绘制坐标轴、网格线、标定长度
    setPenColor(GRAY);
    line(10, 490 - (0 - miny) * scaleY, 790, 490 - (0 - miny) * scaleY);
    line(10 + (0 - minx) * scaleX, 10, 10 + (0 - minx) * scaleX, 490);
    setPenStyle(PEN_STYLE_DASH);
    static char text[20];
    for(double x = (maxx - minx) / 8; (int)(10 + (x - minx) * scaleX) < 790; x += (maxx - minx) / 8){
        line(10 + (x - minx) * scaleX, 10, 10 + (x - minx) * scaleX, 490);
        sprintf(text, "%.2lf", x);
        paintText(10 + (x - minx) * scaleX + 1, 490 - (0 - miny) * scaleY + 1, text);
    }
    for(double x = - (maxx - minx) / 8; x >= minx; x -= (maxx - minx) / 8){
        line(10 + (x - minx) * scaleX, 10, 10 + (x - minx) * scaleX, 490);
        sprintf(text, "%.2lf", x);
        paintText(10 + (x - minx) * scaleX + 1, 490 - (0 - miny) * scaleY + 1, text);
    }
    for(double y = (maxy - miny) / 5; y <= maxy; y += (maxy - miny) / 5){
        line(10, 490 - (y - miny) * scaleY, 790, 490 - (y - miny) * scaleY);
        sprintf(text, "%.2lf", y);
        paintText(10 + (0 - minx) * scaleX - 10, 490 - (y - miny) * scaleY + 1, text);
    }
    for(double y = - (maxy - miny) / 5; y >= miny; y -= (maxy - miny) / 5){
        line(10, 490 - (y - miny) * scaleY, 790, 490 - (y - miny) * scaleY);
        sprintf(text, "%.2lf", y);
        paintText(10 + (0 - minx) * scaleX - 10, 490 - (y - miny) * scaleY + 1, text);
    }
    paintText(787, 490 - (0 - miny) * scaleY - 2, "x");
    paintText(10 + (0 - minx) * scaleX + 3, 10, "y");

    //绘制函数图像
    setPenStyle(PEN_STYLE_SOLID);
    setPenColor(BLACK);
    setPenWidth(2);
    for(double x = arrlx; x <= arrrx; x += step){
        double y1 = getValue(poly, x);
        double y2 = getValue(poly, x + step);
        putPixel(10 + (x - minx) * scaleX, 490 - (y1 - miny) * scaleY, BLACK);
        line(10 + (x - minx) * scaleX, 490 - (y1 - miny) * scaleY, 10 + (x + step - minx) * scaleX, 490 - (y2 - miny) * scaleY);
    }
    endPaint();
}