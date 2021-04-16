#include "acllib.h"

int Setup(){
    initWindow("test", 200, 200, 350, 300);
    beginPaint();
    setPenWidth(4);
    setBrushColor(EMPTY);
    rectangle(110, 100, 150, 125);
    rectangle(185, 100, 225, 125);
    line(150, 111, 185, 111);
    setBrushColor(BLACK);
    ellipse(145, 140, 150, 145);
    ellipse(183, 140, 188, 145);
    paintText(100, 170, "Too young too simple");
    paintText(110, 190, "Sometimes naiive");
    endPaint();
    return 0;
}