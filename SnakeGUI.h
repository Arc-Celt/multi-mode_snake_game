#include "includes.h"

//--------------------------------------GUI----------------------------------------
//����������
int PrintMenu();

//--------------------����-----------------------
//����ģʽ1(����ģʽ)
void playmodel1();

//����ģʽ2(˫��ģʽ)
void playmodel2();

//����ģʽ3(��ǽģʽ)
void playmodel3();

//����ģʽ4(���ǽ��ģʽ)
void playmodel4();

//-----------------��ť------------------------------------

void initButton(CircleButton* button, int x, int y, int radius);

void initAllButtons();

//��ʼ����ť״̬
void initButtonState(CircleButton* button);

// �жϵ�(x, y)�Ƿ��ڰ�ť��������ڲ�
bool insideButton(const CircleButton* button, int x, int y);

CircleButton* findButton(unsigned int id);

// ���ư�ť
void drawButton(const CircleButton* buttonArray);

// �������а�ť
void drawAllButtons();

// ���� (x, y) ���ڵİ�ť�����ذ�ťID, û�з��� -1
int searchButton(int x, int y);

// ����
void draw();

// ��ɫ��ֵ, t ��ΧΪ (0.0 ~ 1.0)���ֱ��ӦcolorA��colorB
color_t interpColor(color_t colorA, color_t colorB, float t);


//-----------------������Ч------------------------------------

//����ȫ�ֱ�������,0�ǰ�ť1�ǳ�2������3�ǽ�����Ϸ

//�򿪲�����s·���µ������ļ�������򿪲��ɹ������˷���1�����򷵻�0
int openmusicfile(char *s,int num);

//�ر�����
int closemusicplay(int num);
