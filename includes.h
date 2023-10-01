//#define _INCLUDES_H
#ifndef _INCLUDES_H
#define _INCLUDES_H


#pragma execution_character_set("utf-8")

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <graphics.h>					//����EGE��ͷ�ļ�

#include <conio.h>                       //����������Ӧ


#define ROW 48 //��Ϸ������
#define COL 48 //��Ϸ������

#define EMPTY 0 //��ǿգ�ʲôҲû�У�
#define WALL 1 //���ǽ
#define FOOD 2 //���ʳ��
#define BODY 3 //�������
#define HEAD 4 //�����ͷ
#define TAIL 5 //�����β

#define UP 72 //���������
#define DOWN 80 //���������
#define LEFT 75 //���������
#define RIGHT 77 //���������
#define SPACE 32 //��ͣ
#define ESC 27 //�˳�

#define BOXX 10 //x����Ԫ��С����
#define BOXY 10 //y����Ԫ��С����

#define NUMX 64 //x���򴰿ڵ�Ԫ��
#define NUMY 64 //y���򴰿ڵ�Ԫ��

#define EDGEX 2 //x���򴰿ڱ�Ե
#define EDGEY 1 //y���򴰿ڱ�Ե

//��ͷ
typedef struct SnakeHead{
    int snakelen; //��¼������
    int x; //��ͷ������
    int y; //��ͷ������1

    struct SnakeBody *body; //��һ��������
}SnakeHead, *LPSnakeHead;

//����
typedef struct SnakeBody{
    int x; //���������
    int y; //����������
    struct SnakeBody *next; //��һ��������
}SnakeBody, *LPSnakeBody;

//��¼��Ϸ������λ�õ�״̬
int ground[ROW][COL];



//--------------------GUI---------------------------

//------------------��ť-------------------------
struct ButtonStates
{
	bool enable;	/* ����״̬ */
	bool visible;	/* �ɼ�״̬ */
	bool pressed;	/* ����״̬ */
	bool checkable; /* ��ѡ״̬ */
	bool checked;	/* ѡ��״̬ */
	bool hovered;	/* ��ͣ״̬ */
	bool focused;	/* ����״̬ */
};

// Բ�ΰ�ť
struct CircleButton
{
	unsigned int id;
	int x, y;		/* Բ��*/
	int radius;		/* �뾶*/
	color_t normalColor;
	color_t pressedColor;
	char text[20];
	ButtonStates state;
};

#define BUTTON_SIZE		5
#define BUTTON_ID_ZERO	((unsigned int)0)
#define BUTTON_MIN_ID	0
#define BUTTON_MAX_ID	BUTTON_SIZE

//���尴ť��ȷ������
CircleButton buttonArray[BUTTON_SIZE];
















#endif

