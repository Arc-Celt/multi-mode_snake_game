#include "includes.h"

//--------------------------------------GUI----------------------------------------
//绘制主界面
int PrintMenu();

//--------------------界面-----------------------
//启动模式1(单人模式)
void playmodel1();

//启动模式2(双人模式)
void playmodel2();

//启动模式3(穿墙模式)
void playmodel3();

//启动模式4(随机墙体模式)
void playmodel4();

//-----------------按钮------------------------------------

void initButton(CircleButton* button, int x, int y, int radius);

void initAllButtons();

//初始化按钮状态
void initButtonState(CircleButton* button);

// 判断点(x, y)是否在按钮点击区域内部
bool insideButton(const CircleButton* button, int x, int y);

CircleButton* findButton(unsigned int id);

// 绘制按钮
void drawButton(const CircleButton* buttonArray);

// 绘制所有按钮
void drawAllButtons();

// 查找 (x, y) 所在的按钮，返回按钮ID, 没有返回 -1
int searchButton(int x, int y);

// 绘制
void draw();

// 颜色插值, t 范围为 (0.0 ~ 1.0)，分别对应colorA和colorB
color_t interpColor(color_t colorA, color_t colorB, float t);


//-----------------音乐音效------------------------------------

//定义全局变量音乐,0是按钮1是吃2是死亡3是结束游戏

//打开并播放s路径下的音乐文件，如果打开并成功播放了返回1，否则返回0
int openmusicfile(char *s,int num);

//关闭音乐
int closemusicplay(int num);
