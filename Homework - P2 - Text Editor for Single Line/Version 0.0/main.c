#include <string.h>
#include <stdio.h>
#include <time.h>
#include "acllib.h"

char inputText[512] = {0};
int curPosition = 0;
int insertMode = 1;
int textSize = 30;
int maxLength = 63;
int moving = 0;

void paintTextBox(){    //绘制文本框
    beginPaint();

    //文本框
    setPenWidth(3);
    setPenColor(WHITE);
    setTextColor(BLACK);
    setBrushColor(WHITE);
    rectangle(50, 80, 955, 130);
    setPenColor(BLACK);
    rectangle(50, 80, 955, 90 + textSize);

    //文本
    setTextFont("Consolas");
    setTextSize(textSize);
    setTextColor(BLACK);
    paintText(60, 83, inputText);
    setTextColor(BLACK);
    
    //光标
    int width = 14;
    setCaretPos(60 + width * curPosition, 85);

    endPaint();
}

void paint(){    //绘图函数
    paintTextBox();
}

void inputEvent(char c){    //处理输入一个字符的事件
    if(insertMode){
        if(strlen(inputText) >= maxLength){
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


void enter(){
    printf("%s\n", inputText);
    memset(inputText, 0, sizeof(inputText));
    curPosition = 0;
}

void resetCaretSize(){
    if(insertMode){
        setCaretSize(2, textSize);
    } else {
        setCaretSize(14, textSize);
    }
    showCaret();
}

void keyboardEvent(int key, int event){    //处理键盘事件
    static int shift = 0;
    if(event == KEY_UP){
        if(key == VK_SHIFT) shift = 0;
        if(key == VK_LEFT || key == VK_RIGHT) moving = 0;
    }
    if(event != KEY_DOWN){
        return;
    }
    if(key == VK_SHIFT){
        shift = 1;
    } else if(key >= 48 && key <= 57){
        if(shift){
            switch (key){
                case 48: inputEvent(')'); break;
                case 49: inputEvent('!'); break;
                case 50: inputEvent('@'); break;
                case 51: inputEvent('#'); break;
                case 52: inputEvent('$'); break;
                case 53: inputEvent('%'); break;
                case 54: inputEvent('^'); break;
                case 55: inputEvent('&'); break;
                case 56: inputEvent('*'); break;
                case 57: inputEvent('('); break;
            }
        } else {
            inputEvent(key);
        }
    } else if(key >= 65 && key <= 90){
        int caps = GetKeyState(VK_CAPITAL);
        inputEvent((caps || shift) ? key : (key + 32));
    } else if(key == VK_BACK){
        if(curPosition != 0){
            int n = strlen(inputText);
            inputText[--curPosition] = 0;
            for(int i = curPosition; i < n; i++){
                inputText[i] = inputText[i+1];
            }
        } else {
            MessageBeep(MB_ICONHAND);
        }
    } else if(key == VK_DELETE){
        int n = strlen(inputText);
        if(curPosition != n){
            for(int i = curPosition; i < n; i ++){
                inputText[i] = inputText[i+1];
            }
        } else {
            MessageBeep(MB_ICONHAND);
        }
    } else {
        switch (key){
            case VK_OEM_1: inputEvent(shift ? ':' : ';'); break;
            case VK_OEM_2: inputEvent(shift ? '?' : '/'); break;
            case VK_OEM_3: inputEvent(shift ? '~' : '`'); break;
            case VK_OEM_4: inputEvent(shift ? '{' : '['); break;
            case VK_OEM_5: inputEvent(shift ? '|' : '\\'); break;
            case VK_OEM_6: inputEvent(shift ? '}' : ']'); break;
            case VK_OEM_7: inputEvent(shift ? '\"' : '\''); break;
            case VK_OEM_PLUS: inputEvent(shift ? '+' : '='); break;
            case VK_OEM_MINUS: inputEvent(shift ? '_' : '-'); break;
            case VK_OEM_COMMA: inputEvent(shift ? '<' : ','); break;
            case VK_OEM_PERIOD: inputEvent(shift ? '>' : '.'); break;
            case VK_SPACE: inputEvent(' '); break;
            case VK_TAB: inputEvent(' '); break;
            case VK_INSERT: insertMode ^= 1; resetCaretSize(); break;
            case VK_LEFT: moving = 1; if(curPosition > 0) curPosition--; else MessageBeep(MB_ICONHAND); break;
            case VK_RIGHT: moving = 1; if(curPosition < strlen(inputText)) curPosition++; else MessageBeep(MB_ICONHAND); break;
            case VK_HOME: curPosition = 0; break;
            case VK_END: curPosition = strlen(inputText); break;
            case VK_RETURN: enter(); break;
        }
    }
    paint();    //输入完成后重新绘制
}

int Setup(){
    initWindow("Text Editor for Single Line                       developed by Ebola", 200, 50, 1000, 300);
    initConsole();
    setCaretSize(2, textSize);
    setCaretPos(60 + 14 * curPosition, 85);
    showCaret();
    registerKeyboardEvent(keyboardEvent);
    paint();
    return 0;
}