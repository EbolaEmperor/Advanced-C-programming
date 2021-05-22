// 绘图系列函数
void paintWKButton(int mode);
void paintWK();
void paintTextBox();
void paintStatusBar();
void paintFunctionBar();
void paint();

//事件函数
void keyboardEvent(int key, int event);
void mouseEvent(int x, int y, int key, int event);
void charEvent(char c);

//行为函数
void inputEvent(char c);
void enter();
void updateFontWidth();
void resetCaretSize();

//信息获取函数
int calcCaretPos();
int isGBK(int pos);
int getTextWidth(int textSize);