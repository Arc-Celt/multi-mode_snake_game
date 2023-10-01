//#define _INCLUDES_H
#ifndef _INCLUDES_H
#define _INCLUDES_H


#pragma execution_character_set("utf-8")

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <graphics.h>					//包含EGE的头文件

#include <conio.h>                       //键盘输入响应


#define ROW 48 //游戏区行数
#define COL 48 //游戏区列数

#define EMPTY 0 //标记空（什么也没有）
#define WALL 1 //标记墙
#define FOOD 2 //标记食物
#define BODY 3 //标记蛇身
#define HEAD 4 //标记蛇头
#define TAIL 5 //标记蛇尾

#define UP 72 //方向键：上
#define DOWN 80 //方向键：下
#define LEFT 75 //方向键：左
#define RIGHT 77 //方向键：右
#define SPACE 32 //暂停
#define ESC 27 //退出

#define BOXX 10 //x方向单元大小像素
#define BOXY 10 //y方向单元大小像素

#define NUMX 64 //x方向窗口单元数
#define NUMY 64 //y方向窗口单元数

#define EDGEX 2 //x方向窗口边缘
#define EDGEY 1 //y方向窗口边缘

//蛇头
typedef struct SnakeHead{
    int snakelen; //记录蛇身长度
    int x; //蛇头横坐标
    int y; //蛇头纵坐标1

    struct SnakeBody *body; //第一个蛇身结点
}SnakeHead, *LPSnakeHead;

//蛇身
typedef struct SnakeBody{
    int x; //蛇身横坐标
    int y; //蛇身纵坐标
    struct SnakeBody *next; //下一个蛇身结点
}SnakeBody, *LPSnakeBody;

//记录游戏区各个位置的状态
int ground[ROW][COL];



//--------------------GUI---------------------------

//------------------按钮-------------------------
struct ButtonStates
{
	bool enable;	/* 可用状态 */
	bool visible;	/* 可见状态 */
	bool pressed;	/* 按下状态 */
	bool checkable; /* 可选状态 */
	bool checked;	/* 选中状态 */
	bool hovered;	/* 悬停状态 */
	bool focused;	/* 焦点状态 */
};

// 圆形按钮
struct CircleButton
{
	unsigned int id;
	int x, y;		/* 圆心*/
	int radius;		/* 半径*/
	color_t normalColor;
	color_t pressedColor;
	char text[20];
	ButtonStates state;
};

#define BUTTON_SIZE		5
#define BUTTON_ID_ZERO	((unsigned int)0)
#define BUTTON_MIN_ID	0
#define BUTTON_MAX_ID	BUTTON_SIZE

//定义按钮，确定区域
CircleButton buttonArray[BUTTON_SIZE];
















#endif

