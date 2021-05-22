#include <string.h>
#include <stdio.h>
#include <time.h>
#include "main.h"
#include "acllib.h"

const char fontName[][16] = {
    "Consolas", "Courier", "Courier New"
};
char inputText[512] = {0};
int curPosition = 0;
int insertMode = 1;
int textFont = 0;
int textSize = 30;
int textColor = 0;
int maxLength = 63;
int moving = 0;
int mouseHoldSizeMinus = 0;
int mouseHoldSizePlus = 0;
int mouseHoldColorChange = 0;
int mouseHoldFontChange = 0;
int wkButtonPush = 0;  //0: 未按下; 1: 按住; 2: 按键已生效

void paintWKButton(int mode){
    beginPaint();
    if(mode == -1){
        setPenColor(WHITE);
        setBrushColor(WHITE);
        rectangle(300, 300, 700, 700);
        endPaint();
        return;
    }
    setPenColor(BLACK);
    setPenWidth(5);
    setBrushColor(WHITE);
    setTextSize(15);
    paintText(390, 325, "Click button to see our red sun");
    if(mode  == 1){
        setPenColor(WHITE);
        setBrushColor(BLACK);
    }
    rectangle(400, 350, 600, 550);
    line(420, 450, 580, 450);
    line(500, 370, 500, 530);
    endPaint();
}

void paintWK(){    //用来绘制翁恺老师的头像
    static const char wk[] = "                      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@OO^                              \0                 ,]]]]@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\]]`                           \0               //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`                   \0              @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\]               \0           ,/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`            \0        O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\\           \0      ,@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@`        \0     ,/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O       \0     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@OO@@@@@@@@@@@@@@@@@@@@@@@\\      \0    \\@@@@@@@@@@@@@@@@@@@@OOOoOoOOOO[\\OOOO@@@@@@OOOOOO/[[[[[[`..**[\\OOO@@@@@@@@@@@@@@@@@@@\\     \0   O@@@@@@@@@@@@@@@@OO/`*[`***..**[`......***............... ........\\OO@@@@@@@@@@@@@@@@@@O    \0  =@@@@@@@@@@@@@OOoo^**.................... ..... ..             .......*,OO@@@@@@@@@@@@@@@@]  \0 /@@@@@@@@@@@@Oo`,**...............  ..   ....                  . .........,OOO@@@@@@@@@@@@@@@.\0@@@@@@@@@@@@Oo^***...................                            .............[O@@@@@@@@@@@@@@/\0@@@@@@@@@@Oo`^*.................. .                               ..............,O@@@@@@@@@@@@@\0@@@@@@@@@O/***....................    ..  ....                     ...............=O@@@@@@@@@@@\0@@@@@@@@o***..................            .                         ..............*\\O@@@@@@@@@@\0@@@@@@@O^*...................   . ................                   ..............=OO@@@@@@@@@\0@@@@@@Oo^*..................             .....                     ................,\\OO@@@@@@@@\0@@@@@@O/`..................                                      .. ...............*,OOO@@@@@@@\0@@@@@@O^*..................                           .             ................*oOOOO@@@@@\0@@@@@OO\\*........................ ...              .. .....`*.......................**=OOO@@@@@\0@@@@OOoo**.........`*,oOOOOO\\`o\\*.........     ..........*\\o/O\\OOO]/OoOO/[]..........**oOOOO@@@\0@@OOOO/**....*,/OOOOOOOO@@@OOOO\\*`*=,..................,]==OOOOOOOOOOOOOO\\ooo`........**[oOO@@@\0@@OOo`***.*,/\\OOOOOOOO[o\\OOoo\\O\\o[/**.*.............****o\\\\[,`[**,/,\\O//OOOOO/\\*.........=oOO@@\0@OOO^*****=OoOOOOOOO/`.......]..**\\\\***`*..........**,o`*..............*\\\\OOOooo*.........*=O@@\0OOo[******ooOOOOo[`................******......................... .  ...*=oOoo\\*.........*=OO@\0Ooo^****,`/oOOOo^**..................*.**.....  .................... .......,[\\oo\\*.......**oO@\0Ooo/*****=oOooo\\*`*`*..]/[[[[\\]*.....***`....    .....*****,]/O[[..,[\\]`...****[o/*......***oO@\0Ooo^****]/OOooo\\o/\\//`]/@@@@@@OOo[[**..***...    .....*[oOOOO@@@@@@@@@O]OO\\]*,**``**.....***\\O@\0Ooo****oo/[oooOOOOOO@@@@@@@@@@\\@@@@\\.,]]O/@[.   .[OOO[[.,@@@O/\\@@@@@@@@@@@OOo^..,`]]]]]]`***=O@\0Oo\\****[[[[[[[\\O@@@@@@OO@@@@O`,[........`O\\.,`,]]]/\\... ......*.......,OOO@@Oo`..........**[\\@@\0O\\O@@@/[[*]]]/OOOOOOOOo]`*,*,/oo/*.....=@OO... ...[OO^. .....,[oo\\\\*...**`**............*.*`/O@\0Ooo/`,*******o/o\\ooOOooooooo[`*........\\Oo....   ...\\^........***.******................**/OO@@\0OOOo/``*******..***.*******............*.*.....  .......................**............,o/[=`=O@\0OOoOOOo`***......**.............................. ....................... ....**.*[[`*..**,\\=OO\0OOoooo/[[[[`.*................... .....,*....... .... *..................  .  .........**,*\\/O^\0OOOOoo\\**......... ........... ......*,`.......   ......`..............................***o==O\\\0OOOOoo/***................. ..  ...... ......  ..  .......*..........................*.**^^/\\O`\0@OOOoooo***.......................*......................................  .........******oooO^\0OOOOOooo`***............  ........**=\\oOOOOo\\\\]]*]]oOOOO\\`**.......................*****==o=oO/\0OOOOOoooo*****..................**=oOO@@@@@@OOOOOOO@@@@@@OOO......................******,=o\\/O/\0OOOOOOooo\\/*****...............***=OOOO[[/[O@@@@@@@@O\\O@@@OO.....................***.***=oo^\\o^\0OOOOOOooooo]]]*****...............*\\OOOO/[*,*oO@@/`*..*......... ..........*************oo^``o^\0=OOOOOoooooooooooo\\`****...........*,`****,*`*.................. ........*****`****.****o\\`,=o^\0=OOOOOoooooooooooOoooo`]**................................................**************o^=o\\=/\0=OOOOOooooooooooOOOOooo`**.........................  ............................*******o\\=o/o\\\0=OOOOOoooooooooooooo/\\^*******,`**..*.......................****,]]`**..............****,o*=`o^\0.OOOOOOooooooo[oo`*,`**,`,/o]o\\oOooo]`/OOOOOOOO]//OOOOOOOO]]]oOOOOOOoo*..............***/ooooo^\0.OOOOOOooooooo^*********][\\oOOOO@OOO@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O\\*.....**.......***oooooo[\0.\\OOOOoOoooo=^****,]******oOOOOOOOOO@@OOo//***....*...*,[*****.............**.......***/ooooo^ \0 [\\OOOOOooooo,]***oo\\******oOOOooo****`**********=**.......*.............******...***=\\oooooO` \0   =OOOOOoooooo]]`=ooooo]***/oo/***,***=ooOOOOOOOOO@@OOo\\`**..........**************,oooooO\\^  \0    \\OOOOOoooooooooooooooo`*oooo\\/o//oooOOOOO@@@@@OOOOOoo`..........****\\ooo*****=ooooOOOOOO   \0    =OOOOOOOooooooooooOOOOooooooooooooooOOOoo/[oo/``***............****=ooo=\\/ooooooOOOOOOO`   \0     =OOOOOOOOOOOOOOOOOOOOooooooooo/[`******.*.*.*...............*..***=ooooooOOOOOOOOOOOO^    \0       OOOOOOOOOOOOOOOOOOOOOoooooooo***............................***oooOOOOOOOOOOOOOOOO^     \0        [OOOOOOOOOOOOOOOOOOOOoooo=o****.,.....................******/ooOOOOOOOOOOOOOOOO[`      \0          \\OOOOOOOOOOOOOOOOOOOooo]/\\]`**.....................****,oooOOOOOOOOOOOOOOOO^         \0           \\@@OOOOOOOOOOOOOOOOOOoooooooo`**************..****]]ooOOOOOOOOOOOOOOOOOOOO          \0             O@@@OOOOOOOOOOOOOOOOOOOoooooOOoooooooOooOoooooOOOOOOOOOOOOOOOOOOOOOOOOoO          \0              ,OOOOOOO@@OOOOOOOOO@OOOOOOOOOOOOOOOOOOOOOOOOOOOOO@@OOOOOOOOOOOOOOOOooO^          \0               =OOOOOOOOOOOOOOOOOOO@@@@@@@@@@@@@@@@@@@OO@@@@@@@@OOOOOOOOOOOOOOOoooooo          \0               =OOOOOOOOOOOOOOOOOOOOO@@@@@@@@@@@@@@@@@@@@@@@@@OOOOOOOOOOOOOOOoooooo^O          \0";
    beginPaint();
    setTextSize(6);
    for(int i = 0; i < 64; i++){
        paintText(350, 230 + 6 * i, wk + 96 * i);
    }
    setTextFont("Consolas");
    setTextSize(100);
    setTextColor(RED);
    paintText(120, 350, "Red");
    paintText(720, 350, "Sun");
    setTextSize(25);
    setTextColor(BLACK);
    paintText(120, 650, "Prof. Weng Kai is our red sun, we can\'t live without Weng Kai.");
    endPaint();
}

int getTextWidth(){    //获取字体的宽度
    switch (textFont){
        case 0:    //Consolas 字体宽度
            if(textSize >= 32) return (textSize / 2) - 1;
            else if(textSize >= 17) return (textSize - 1) / 2;
            else return textSize / 2;
            break;
        case 1:    //Courier 字体宽度
            if(textSize >= 38) return 25;
            else if(textSize >= 32) return 19;
            else if(textSize >= 26) return 17;
            else if(textSize >= 25) return 16;
            else if(textSize >= 20) return 13;
            else if(textSize >= 16) return 10;
            else return 9;
            break;
        case 2:    //Courier New 字体宽度
            if(textSize == 35 || textSize == 37) return (textSize / 2) + 2;
            else if(textSize == 20 || textSize == 22 || textSize == 26 || textSize == 28) return (textSize / 2);
            else if(textSize <= 16) return 7;
            else return (textSize / 2) + 1;
            break;
    }
}

int chineseWidth(){
    if(textFont != 1) return 2 * getTextWidth() + 1;
    else return  2 * getTextWidth() - 1;
}

int calcCaretPos(){
    int pos = 0;
    int width = getTextWidth();
    for(int i = 0; i < curPosition; i++){
        if(inputText[i] < 0){
            pos += chineseWidth();
            i++;
        }
        else pos += width;
    }
    return pos;
}

void paintTextBox(){    //绘制文本框
    static const COLORREF colorCode[] = {
        BLACK, RED, BLUE, GREEN, CYAN, MAGENTA, YELLOW
    };

    beginPaint();

    //文本框
    setPenWidth(3);
    setPenColor(WHITE);
    setTextColor(BLACK);
    setBrushColor(WHITE);
    rectangle(0, 80, 1000, 130);
    setPenColor(BLACK);
    line(0, 80, 1000, 80);
    line(0, 90 + textSize, 1000, 90 + textSize);

    //文本
    setTextFont(fontName[textFont]);
    setTextSize(textSize);
    setTextColor(colorCode[textColor]);
    paintText(60, 83, inputText);
    setTextColor(BLACK);
    
    //光标
    setCaretPos(60 + calcCaretPos(), 85);

    endPaint();
}

void paintStatusBar(){    //绘制文本框下方的状态栏
    beginPaint();
    setPenColor(WHITE);
    setBrushColor(WHITE);
    rectangle(50, 140, 950, 160);
    setTextFont("Consolas");
    setPenColor(BLACK);
    setTextColor(BLACK);
    setTextSize(20);
    paintText(60, 143, insertMode ? "Mode: Insert" : "Mode: Cover");
    static char length[16];
    sprintf(length, "Max Length: %d", maxLength);
    paintText(800, 143, length);
    sprintf(length, "Length: %d", strlen(inputText));
    paintText(690, 143, length);
    sprintf(length, "Position: %d", curPosition + 1);
    paintText(560, 143, length);
    endPaint();
}

void paintFunctionBar(){    //绘制文本框上方的功能区
    static const char colorName[][8] = {
        "Black", "Red", "Blue", "Green", "Cyan", "Magenta", "Yellow"
    };
    
    beginPaint();
    setTextFont("Consolas");
    setPenColor(BLACK);
    setTextBkColor(WHITE);
    setTextColor(BLACK);
    setTextSize(20);
    static char outText[32];
    sprintf(outText, "Size:     %d", textSize);
    paintText(60, 35, outText);
    setPenColor(WHITE);
    setBrushColor(WHITE);
    rectangle(347, 35, 450, 57);
    rectangle(447, 35, 700, 57);
    setPenColor(BLACK);
    sprintf(outText, "Color:     %s", colorName[textColor]);
    paintText(260, 35, outText);
    sprintf(outText, "Font:     %s", fontName[textFont]);
    paintText(465, 35, outText);

    setPenWidth(2);
    setTextSize(19);
    setTextBkColor(EMPTY);
    if(mouseHoldSizeMinus){
        setBrushColor(BLACK);
        setTextColor(WHITE);
    } else {
        setBrushColor(WHITE);
        setTextColor(BLACK);
    }
    rectangle(118, 35, 140, 57);
    paintText(124, 36, "-");

    if(mouseHoldSizePlus){
        setBrushColor(BLACK);
        setTextColor(WHITE);
    } else {
        setBrushColor(WHITE);
        setTextColor(BLACK);
    }
    rectangle(178, 35, 200, 57);
    paintText(184, 36, "+");

    if(mouseHoldColorChange){
        setBrushColor(BLACK);
        setTextColor(WHITE);
    } else {
        setBrushColor(WHITE);
        setTextColor(BLACK);
    }
    rectangle(323, 35, 345, 57);
    setTextSize(12);
    paintText(325, 37, "...");

    if(mouseHoldFontChange){
        setBrushColor(BLACK);
        setTextColor(WHITE);
    } else {
        setBrushColor(WHITE);
        setTextColor(BLACK);
    }
    rectangle(523, 35, 545, 57);
    setTextSize(12);
    paintText(525, 37, "...");

    setTextBkColor(WHITE);
    endPaint();
}

void paintCaret(){
    beginPaint();
    setPenColor(BLACK);
    if(insertMode){
        setPenWidth(2);
        int pos = calcCaretPos();
        line(60 + pos, 84, 60 + pos, 87 + textSize);
    } else {
        setBrushColor(BLACK);
        int pos = calcCaretPos();
        int width = isGBKfirst(curPosition) ? chineseWidth() : getTextWidth();
        rectangle(60 + pos, 84, 60 + pos + width, 87 + textSize);
        setTextColor(WHITE);
        setTextBkColor(EMPTY);
        setTextSize(textSize);
        static char tmps[3];
        if(isGBKfirst(curPosition)){
            tmps[0] = inputText[curPosition];
            tmps[1] = inputText[curPosition + 1];
            tmps[2] = '\0';
        } else {
            tmps[0] = inputText[curPosition];
            tmps[1] = '\0';
        }
        paintText(60 + pos, 83, tmps);
    }
    endPaint();
}

void paint(){    //绘图函数
    paintTextBox();
    paintCaret();
    paintStatusBar();
    paintFunctionBar();
}

void inputEvent(char c){    //处理输入一个字符的事件
    if(insertMode){
        if(strlen(inputText) >= maxLength || c < 0 && strlen(inputText) + 1 >= maxLength){
            MessageBeep(MB_ICONHAND);
            return;
        }
        int n = strlen(inputText);
        for(int i = n; i > curPosition; i--){
            inputText[i] = inputText[i-1];
        }
        inputText[curPosition++] = c;
    } else {
        if(curPosition >= maxLength){
            MessageBeep(MB_ICONHAND);
            return;
        }
        inputText[curPosition++] = c;
    }
}

void updateFontWidth(){
    int preMaxLength = maxLength;
    maxLength = 890 / getTextWidth();
    for(int i=maxLength; i<preMaxLength; i++){
        inputText[i] = 0;
    }
    if(isGBKfirst(maxLength - 1))
        inputText[maxLength - 1] = 0;
    curPosition = min(curPosition, strlen(inputText));
}

void mouseEvent(int x, int y, int key, int event){
    if(event == BUTTON_DOWN){
        if(key == LEFT_BUTTON){
            if(x>=118 && x<=140 && y>=35 && y<=57){
                if(textSize == 15) return;
                mouseHoldSizeMinus = 1;
                textSize--;
                updateFontWidth();
            }
            if(x>=178 && x<=200 && y>=35 && y<=57){
                if(textSize == 40) return;
                mouseHoldSizePlus = 1;
                textSize++;
                updateFontWidth();
            }
            if(x>=323 && x<=345 && y>=35 && y<=57){
                mouseHoldColorChange = 1;
                textColor = (textColor + 1) % 7;
            }
            if(x>=523 && x<=545 && y>=35 && y<=57){
                mouseHoldFontChange = 1;
                textFont = (textFont + 1) % 3;
                updateFontWidth();
            }
            if(wkButtonPush == 0 && x>=400 && x<=600 && y>=350 && y<=550){
                paintWKButton(1);
                wkButtonPush = 1;
            }
        }
        paint();
    } else if(event == BUTTON_UP){
        if(key == LEFT_BUTTON){
            mouseHoldSizeMinus = 0;
            mouseHoldSizePlus = 0;
            mouseHoldColorChange = 0;
            mouseHoldFontChange = 0;
            if(wkButtonPush == 1){
                paintWKButton(-1);
                paintWK();
                wkButtonPush = 2;
            }
        }
        paint();
    }
}

void enter(){
    printf("%s\n", inputText);
    memset(inputText, 0, sizeof(inputText));
    curPosition = 0;
}

int isGBK(int pos){    //判断pos位置上的字符是不是中文的GBK编码
    for(int i = 0; i < pos; i++){
        if(inputText[i] < 0){
            if(pos == i + 1) return 1;
            i++;
        }
    }
    return inputText[pos] < 0;
}

int isGBKfirst(int pos){    //判断pos位置上的字符是不是中文GBK编码中的第一个编码
    if(inputText[pos] >= 0) return 0;
    for(int i = 0; i < pos; i++){
        if(inputText[i] < 0){
            if(++i == pos) return 0;
        }
    }
    return inputText[pos] < 0;
}

void keyboardEvent(int key, int event){    //处理键盘事件
    if(event == KEY_UP){
        if(key == VK_LEFT || key == VK_RIGHT) moving = 0;
        return;
    }
    if(key == VK_BACK){
        if(curPosition){
            int n = strlen(inputText);
            int times = isGBK(curPosition - 1) ? 2 : 1;
            while(times--){
                inputText[--curPosition] = 0;
                for(int i = curPosition; i < n; i++){
                    inputText[i] = inputText[i+1];
                }
            }
        } else {
            MessageBeep(MB_ICONHAND);
        }
    } else if(key == VK_DELETE){
        int n = strlen(inputText);
        if(curPosition != n){
            int times = isGBK(curPosition) ? 2 : 1;
            while(times--){
                for(int i = curPosition; i < n; i ++){
                    inputText[i] = inputText[i+1];
                }
            }
        } else {
            MessageBeep(MB_ICONHAND);
        }
    } else {
        int step = 1;
        switch (key){
            case VK_INSERT: insertMode ^= 1; break;
            case VK_LEFT:
                moving = 1;
                if(isGBK(curPosition - 1)) step = 2;
                if(curPosition > 0) curPosition -= step;
                else MessageBeep(MB_ICONHAND);
                break;
            case VK_RIGHT:
                moving = 1;
                if(isGBK(curPosition)) step = 2;
                if(curPosition < strlen(inputText)) curPosition += step;
                else MessageBeep(MB_ICONHAND);
                break;
            case VK_HOME: curPosition = 0; break;
            case VK_END: curPosition = strlen(inputText); break;
            case VK_RETURN: enter(); break;
        }
    }
    paint();    //输入完成后重新绘制
}

void charEvent(char c){
    if(c >= 0 && c < 32) return;
    inputEvent(c);
    paint();
}

void timeEvent(int tid){    //时间戳，用来处理光标的显示与消失
    if(clock()%1000 < 500){
        paintCaret();
    } else {
        paintTextBox();
    }
}

int Setup(){
    initWindow("Text Editor for Single Line                       developed by Ebola", 200, 50, 1000, 700);
    initConsole();
    registerKeyboardEvent(keyboardEvent);
    registerCharEvent(charEvent);
    registerMouseEvent(mouseEvent);
    registerTimerEvent(timeEvent);
    startTimer(0, 250);
    paint();
    paintWKButton(0);
    return 0;
}