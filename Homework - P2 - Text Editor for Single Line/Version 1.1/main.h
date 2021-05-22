// 绘图系列函数
void paintWKButton(int mode);
void paintWK();
void paintTextBox();
void paintStatusBar();
void paintFunctionBar();
void paintCaret();
void paint();

//事件函数
void keyboardEvent(int key, int event);
void mouseEvent(int x, int y, int key, int event);
void charEvent(char c);
void timeEvent(int tid);

//行为函数
void inputEvent(char c);
void enter();
void updateFontWidth();

//信息获取函数
int calcCaretPos();
int chineseWidth();
int getTextWidth();
int isGBK(int pos);
int isGBKfirst(int pos);