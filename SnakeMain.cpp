#include "includes.h"
#include "SnakeGUI.h"
#include "Snake.h"
#include "graphics.h"

int main()
{
    char chBuffer[255];
    char chKey = '0';

    initgraph(BOXX*NUMX, BOXY*NUMY);	    //初始化图形界面
    setcaption("Gluttonous Snake");		    //设置窗口标题
	setcolor(EGERGB(0xFF, 0x0, 0x0));	    //设置绘画颜色为红色
	setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));	//设置背景色为纯白

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
        //关闭窗口
	    closegraph();
        return 0;
        break;

        default:
        //暂停，等待按键
        getch();
        return 0;
        break;
    }

    return 0;
}
