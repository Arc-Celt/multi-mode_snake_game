#include "includes.h"
#include "SnakeGUI.h"
#include "Snake.h"
#include "graphics.h"

int main()
{
    char chBuffer[255];
    char chKey = '0';

    initgraph(BOXX*NUMX, BOXY*NUMY);	    //��ʼ��ͼ�ν���
    setcaption("Gluttonous Snake");		    //���ô��ڱ���
	setcolor(EGERGB(0xFF, 0x0, 0x0));	    //���û滭��ɫΪ��ɫ
	setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));	//���ñ���ɫΪ����

    switch(PrintMenu())
    {
        case 1:
        playmodel1();
        break;

        case 2:
        playmodel2();
        break;

        case 3:
        playmodel3();
        break;

        case 4:
        playmodel4();
        break;

        case 5:
        //�رմ���
	    closegraph();
        return 0;
        break;

        default:
        //��ͣ���ȴ�����
        getch();
        return 0;
        break;
    }

    return 0;
}
