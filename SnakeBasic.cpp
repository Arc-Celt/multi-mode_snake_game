#include "includes.h"
#include "SnakeGUI.h"
#include "Snake.h"

//SnakeBasic.cpp用于存放实现蛇、食物、场地的相关基本操作

//隐藏光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; //定义光标信息的结构体变量
	curInfo.dwSize = 1; //如果没赋值的话，光标隐藏无效
	curInfo.bVisible = FALSE; //将光标设置为不可见
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorInfo(handle, &curInfo); //设置光标信息
}

//光标跳转
void CursorJump(int x, int y)
{
	COORD pos; //定义光标位置的结构体变量
	pos.X = x; //横坐标
	pos.Y = y; //纵坐标
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //获取控制台句柄
	SetConsoleCursorPosition(handle, pos); //设置光标位置
}

//颜色设置
void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //颜色设置
	//注：SetConsoleTextAttribute是一个API（应用程序编程接口）
}

//初始化场地
void InitGround()
{
    int i, j;
    //color(6); //颜色设置为土黄色

    //initgraph(800, 600, INIT_RENDERMANUAL);		//初始化图形环境，创建宽高为640x480的窗口
	//setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));	//设置背景色为纯白
    ege_enable_aa(true);					//开启抗锯齿
    //system("cls");
	cleardevice();
     for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            if (i == 0 || i == ROW-1 || j == 0 || j == COL-1)//墙
            {
                ground[i][j] = WALL;
            }
            else//空
            {
                ground[i][j] = EMPTY;
            }
        }
    } 

    setlinewidth(6);
    rectangle(BOXX*EDGEX-3,BOXY*EDGEY-3,BOXX*(ROW+EDGEX-1)+3,BOXY*(COL+EDGEY-1)+3);
    delay_fps(10);
}

//初始化空场地
void InitEmptyGround()
{
    int i, j;
    //initgraph(800, 600, INIT_RENDERMANUAL);		//初始化图形环境，创建宽高为640x480的窗口
	//setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));	//设置背景色为纯白
    ege_enable_aa(true);					//开启抗锯齿
    system("cls");
	cleardevice();
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            ground[i][j] = EMPTY;
        }
    }
    
    setlinestyle(PS_DASH); // 设置线条样式为虚线
    setlinewidth(1);
    rectangle(BOXX*EDGEX-3,BOXY*EDGEY-3,BOXX*(ROW+EDGEX-1)+10,BOXY*(COL+EDGEY-1)+10);

}

//初始化蛇内存
LPSnakeHead InitSnake( int x, int y )
{
    if( x==-1 && y==-1 )//默认时，令蛇的初始化坐标为游戏区中心
    {
        x = COL / 2;
        y = ROW / 2;
    }
    SnakeHead *head; 
    head = (LPSnakeHead)malloc(sizeof(SnakeHead));
    head->snakelen = 1;
    head->x = x;
    head->y = y;
    
    SnakeBody *body, *tail;
    body = (LPSnakeBody)malloc(sizeof(SnakeBody));
    tail = (LPSnakeBody)malloc(sizeof(SnakeBody));
    body->x = head->x - 1;
    body->y = head->y;
    tail->x = head->x - 2;
    tail->y = head->y;
    body->next = tail;
    tail->next = NULL;
    head->body = body;

    ground[head->y][head->x] = HEAD;
    ground[body->y][body->x] = BODY;
    ground[tail->y][tail->x] = TAIL;

    return head;
}

//清除蛇
void ClearSnake(SnakeHead *head)
{
    setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));	//设置背景色为纯白
	setfillcolor(EGEARGB(0xFF, 0xFF, 0xFF, 0xFF));
    ege_fillrect((head->x+EDGEX)*BOXX, (head->y+EDGEY)*BOXY,BOXX,BOXY);
    SnakeBody *p = head->body;
    while (p != NULL)//清除蛇身
    {
        ege_fillrect((p->x+EDGEX)*BOXX, (p->y+EDGEY)*BOXY,BOXX,BOXY);
        p = p->next;
    } 
}

//打印蛇
void PrintSnake(LPSnakeHead head,int num, int direction)
{
    //创建图片对象
	PIMAGE headi = newimage();
	//获取旋转后蛇头
	if(num ==1){
		switch (direction)
		    {
			    case UP:
			        getimage(headi, "resource/head1UP.png");
			        break;
			    case RIGHT:
			        getimage(headi, "resource/head1RIGHT.png");
			        break;
			    case DOWN:
			        getimage(headi, "resource/head1DOWN.png");
			        break;
			    case LEFT:
			        getimage(headi, "resource/head1LEFT.png");
			        break;
			    default:
			    	break;
			}
	}
	if(num ==2){
		switch (direction)
		    {
			    case UP:
			        getimage(headi, "resource/head2UP.png");
			        break;
			    case RIGHT:
			        getimage(headi, "resource/head2RIGHT.png");
			        break;
			    case DOWN:
			        getimage(headi, "resource/head2DOWN.png");
			        break;
			    case LEFT:
			        getimage(headi, "resource/head2LEFT.png");
			        break;
			    default:
			    	break;
			}
	} 
	putimage((head->x+EDGEX)*BOXX, (head->y+EDGEY)*BOXY, headi);
	delimage(headi);

	// 绘制蛇身
    SnakeBody *p = head->body;
    p = head->body;
    if(num ==1){
	    while (p != NULL)
	    {
		    setfillcolor(EGERGBA(0x66, 0x33, 0x00, 0xFF));
		    ege_fillrect((p->x+EDGEX)*BOXX, (p->y+EDGEY)*BOXY, BOXX, BOXY);
	        p = p->next;
	    }
	}
	if(num ==2){
		while (p != NULL)
	    {
		setfillcolor(EGERGBA(0x0E, 0x86, 0x2A, 0xFF));
		ege_fillrect((p->x+EDGEX)*BOXX, (p->y+EDGEY)*BOXY, BOXX, BOXY);
	        p = p->next;
	    }	
	}

    delay_fps(10);
}

//随机生成食物
void RandFood()
{
    int i, j;
	do
	{ //随机生成食物的横纵坐标
		i = rand() % ROW;
		j = rand() % COL;
	} while (ground[i][j] != EMPTY); //确保生成食物的位置为空，若不为空则重新生成
	ground[i][j] = FOOD; //将食物位置进行标记
	color(12); //颜色设置为红色

	setfillcolor(EGEARGB(0x80, 0xFF, 0x00, 0xFF));
	ege_fillellipse((j+EDGEX)*BOXX, (i+EDGEY)*BOXY, BOXX, BOXY);
    delay_fps(10);
}

//检查食物周围墙体情况
int IsSurroundWall(int x, int y)
{
    int wallcount = 0;

    if (ground[y-1][x] == WALL)//上方是墙体
        wallcount++;
    if (ground[y+1][x] == WALL)//下方是墙体
        wallcount++;
    if (ground[y][x-1] == WALL)//左边是墙体
        wallcount++;
    if (ground[y][x+1] == WALL)//右边是墙体
        wallcount++;
    
    return (wallcount >= 3);//三周或四周围墙
}

//随机生成食物，且避免其三周围着墙壁
void RandNWFood()
{
    int i, j;
	do
	{ //确保生成食物的位置为空，若不为空则重新生成
		i = rand() % ROW;
		j = rand() % COL;//随机生成食物的横纵坐标
	} while (ground[i][j] != EMPTY || IsSurroundWall(j, i));
	ground[i][j] = FOOD; //将食物位置进行标记
	color(12); //颜色设置为红色
	setfillcolor(EGEARGB(0x80, 0xFF, 0x00, 0xFF));
	ege_fillellipse((j+EDGEX)*BOXX, (i+EDGEY)*BOXY, BOXX, BOXY);
}

//检查位置是否靠近蛇头、蛇身，范围为4格
int IsNearSnake(int x, int y,  LPSnakeHead head)
{
    SnakeBody *body = head->body;
    while (body != NULL)
    {
        int dx = abs(x - body->x);
        int dy = abs(y - body->y);
        if (dx <= 4 && dy <= 4)
        {
            return 1; //靠近蛇头、蛇身
        }
        body = body->next;
    }
    return 0; //非靠近
}

//随机生成墙体的地图
void InitRandGround(LPSnakeHead head)
{
    //生成初始地图
    InitGround();

    //随机生成墙体
    int numwall = (ROW*COL)/24; //将墙体数量定为场地格数的1/24
    while (numwall > 0)
    {
        int x = rand() % COL;
        int y = rand() % ROW;
        if (ground[y][x] == EMPTY && !IsNearSnake(x, y, head))
        { //避免在贪吃蛇初始化位置周围生成墙体
            ground[y][x] = WALL;
            //纯黑色墙体
            int startX = BOXX * EDGEX + BOXX * x;
            int startY = BOXY * EDGEY + BOXY * y;
            int endX = startX + BOXX;
            int endY = startY + BOXY;
            setfillcolor(BLACK);
            bar(startX, startY, endX, endY);
            numwall--;
        }
    }
}

//蛇的单次移动与目的地检测
int MoveSnake(SnakeHead *head, int direction)
{
    int x = head->x;
    int y = head->y;
    switch (direction)
    {
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        default:
            break;
    }

    if (ground[y][x] == WALL || ground[y][x] == BODY || ground[y][x] == HEAD || ground[y][x] == TAIL)
    {
        return 1;//撞墙或撞身体，返回1
    }
    else if (ground[y][x] == FOOD)//在原蛇头的位置新增蛇身结点，然后将蛇头移动到新的位置
    {
        ground[y][x] = HEAD;//坐标更新
        ground[head->y][head->x] = BODY;
        
        SnakeBody *newbody;//创造新的蛇身结点
        newbody = (LPSnakeBody)malloc(sizeof(SnakeBody));
        newbody->x = head->x;
        newbody->y = head->y;

        newbody->next = head->body;//将新的蛇身结点插入到蛇身链表的头部
        head->body = newbody;

        head->x = x;//更新蛇头坐标
        head->y = y;
        head->snakelen++;

        RandFood();
        return 2;//吃到食物，返回2
    }
    else
    {
        ground[y][x] = HEAD;
        ground[head->y][head->x] = BODY;

        SnakeBody *p = head->body;//更新第一节蛇身坐标
        int tempX = p->x;//储存当前第一节蛇身的坐标
        int tempY = p->y;
        p->x = head->x;
        p->y = head->y;
        
        head->x = x;//更新蛇头坐标
        head->y = y;

        int NewX, NewY;
        while (p->next != NULL)//更新后续蛇身坐标(蛇尾坐标在此步骤中未更新)
        {
            NewX = p->next->x;//储存下一个蛇身的坐标
            NewY = p->next->y;
            p->next->x = tempX;//下一个蛇身的坐标等于上一个蛇身的坐标
            p->next->y = tempY;
            tempX = NewX;//更新上一个蛇身的坐标
            tempY = NewY;
            p = p->next;//移动下一个蛇身结点
        }
        ground[p->y][p->x] = TAIL;//更新蛇尾坐标
        ground[NewY][NewX] = EMPTY;//清空原来蛇尾的坐标
        
        return 0;//正常移动，返回0
    }
}

//穿墙模式中蛇的单次移动与目的地检测
int MovePSnake(SnakeHead *head, int direction)
{
    int x = head->x;
    int y = head->y;
    switch (direction)
    {
        case UP:
            y--;
            if (y < 0) // 蛇头超出上边界
                y = ROW - 1; // 移动至下边界
            break;
        case DOWN:
            y++;
            if (y >= ROW) // 超出下边界
                y = 0; // 移动至上边界
            break;
        case LEFT:
            x--;
            if (x < 0) // 超出左边界
                x = COL - 1; // 移动至右边界
            break;
        case RIGHT:
            x++;
            if (x >= COL) // 超出右边界
                x = 0; // 移动至左边界
            break;
        default:
            break;
    }

    if (ground[y][x] == BODY || ground[y][x] == HEAD || ground[y][x] == TAIL)
    {
        return 1;//撞身体，返回1
    }
    else if (ground[y][x] == FOOD)//在原蛇头的位置新增蛇身结点，然后将蛇头移动到新的位置
    {
        ground[y][x] = HEAD;//坐标更新
        ground[head->y][head->x] = BODY;
        
        SnakeBody *newbody;//创造新的蛇身结点
        newbody = (LPSnakeBody)malloc(sizeof(SnakeBody));
        newbody->x = head->x;
        newbody->y = head->y;

        newbody->next = head->body;//将新的蛇身结点插入到蛇身链表的头部
        head->body = newbody;

        head->x = x;//更新蛇头坐标
        head->y = y;
        head->snakelen++;

        RandFood();
        return 2;//吃到食物，返回2
    }
    else
    {
        ground[y][x] = HEAD;
        ground[head->y][head->x] = BODY;

        SnakeBody *p = head->body;//更新第一节蛇身坐标
        int tempX = p->x;//储存当前第一节蛇身的坐标
        int tempY = p->y;
        p->x = head->x;
        p->y = head->y;
        
        head->x = x;//更新蛇头坐标
        head->y = y;

        int NewX, NewY;
        while (p->next != NULL)//更新后续蛇身坐标(蛇尾坐标在此步骤中未更新)
        {
            NewX = p->next->x;//储存下一个蛇身的坐标
            NewY = p->next->y;
            p->next->x = tempX;//下一个蛇身的坐标等于上一个蛇身的坐标
            p->next->y = tempY;
            tempX = NewX;//更新上一个蛇身的坐标
            tempY = NewY;
            p = p->next;//移动下一个蛇身结点
        }
        ground[p->y][p->x] = TAIL;//更新蛇尾坐标
        ground[NewY][NewX] = EMPTY;//清空原来蛇尾的坐标
        
        return 0;//正常移动，返回0
    }
}