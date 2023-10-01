#include "includes.h"
#include "SnakeGUI.h"
#include "Snake.h"

//SnakeBasic.cpp���ڴ��ʵ���ߡ�ʳ����ص���ػ�������

//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO curInfo; //��������Ϣ�Ľṹ�����
	curInfo.dwSize = 1; //���û��ֵ�Ļ������������Ч
	curInfo.bVisible = FALSE; //���������Ϊ���ɼ�
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorInfo(handle, &curInfo); //���ù����Ϣ
}

//�����ת
void CursorJump(int x, int y)
{
	COORD pos; //������λ�õĽṹ�����
	pos.X = x; //������
	pos.Y = y; //������
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ����̨���
	SetConsoleCursorPosition(handle, pos); //���ù��λ��
}

//��ɫ����
void color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c); //��ɫ����
	//ע��SetConsoleTextAttribute��һ��API��Ӧ�ó����̽ӿڣ�
}

//��ʼ������
void InitGround()
{
    int i, j;
    //color(6); //��ɫ����Ϊ����ɫ

    //initgraph(800, 600, INIT_RENDERMANUAL);		//��ʼ��ͼ�λ������������Ϊ640x480�Ĵ���
	//setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));	//���ñ���ɫΪ����
    ege_enable_aa(true);					//���������
    //system("cls");
	cleardevice();
     for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            if (i == 0 || i == ROW-1 || j == 0 || j == COL-1)//ǽ
            {
                ground[i][j] = WALL;
            }
            else//��
            {
                ground[i][j] = EMPTY;
            }
        }
    } 

    setlinewidth(6);
    rectangle(BOXX*EDGEX-3,BOXY*EDGEY-3,BOXX*(ROW+EDGEX-1)+3,BOXY*(COL+EDGEY-1)+3);
    delay_fps(10);
}

//��ʼ���ճ���
void InitEmptyGround()
{
    int i, j;
    //initgraph(800, 600, INIT_RENDERMANUAL);		//��ʼ��ͼ�λ������������Ϊ640x480�Ĵ���
	//setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));	//���ñ���ɫΪ����
    ege_enable_aa(true);					//���������
    system("cls");
	cleardevice();
    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            ground[i][j] = EMPTY;
        }
    }
    
    setlinestyle(PS_DASH); // ����������ʽΪ����
    setlinewidth(1);
    rectangle(BOXX*EDGEX-3,BOXY*EDGEY-3,BOXX*(ROW+EDGEX-1)+10,BOXY*(COL+EDGEY-1)+10);

}

//��ʼ�����ڴ�
LPSnakeHead InitSnake( int x, int y )
{
    if( x==-1 && y==-1 )//Ĭ��ʱ�����ߵĳ�ʼ������Ϊ��Ϸ������
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

//�����
void ClearSnake(SnakeHead *head)
{
    setbkcolor(EGERGB(0xFF, 0xFF, 0xFF));	//���ñ���ɫΪ����
	setfillcolor(EGEARGB(0xFF, 0xFF, 0xFF, 0xFF));
    ege_fillrect((head->x+EDGEX)*BOXX, (head->y+EDGEY)*BOXY,BOXX,BOXY);
    SnakeBody *p = head->body;
    while (p != NULL)//�������
    {
        ege_fillrect((p->x+EDGEX)*BOXX, (p->y+EDGEY)*BOXY,BOXX,BOXY);
        p = p->next;
    } 
}

//��ӡ��
void PrintSnake(LPSnakeHead head,int num, int direction)
{
    //����ͼƬ����
	PIMAGE headi = newimage();
	//��ȡ��ת����ͷ
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

	// ��������
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

//�������ʳ��
void RandFood()
{
    int i, j;
	do
	{ //�������ʳ��ĺ�������
		i = rand() % ROW;
		j = rand() % COL;
	} while (ground[i][j] != EMPTY); //ȷ������ʳ���λ��Ϊ�գ�����Ϊ������������
	ground[i][j] = FOOD; //��ʳ��λ�ý��б��
	color(12); //��ɫ����Ϊ��ɫ

	setfillcolor(EGEARGB(0x80, 0xFF, 0x00, 0xFF));
	ege_fillellipse((j+EDGEX)*BOXX, (i+EDGEY)*BOXY, BOXX, BOXY);
    delay_fps(10);
}

//���ʳ����Χǽ�����
int IsSurroundWall(int x, int y)
{
    int wallcount = 0;

    if (ground[y-1][x] == WALL)//�Ϸ���ǽ��
        wallcount++;
    if (ground[y+1][x] == WALL)//�·���ǽ��
        wallcount++;
    if (ground[y][x-1] == WALL)//�����ǽ��
        wallcount++;
    if (ground[y][x+1] == WALL)//�ұ���ǽ��
        wallcount++;
    
    return (wallcount >= 3);//���ܻ�����Χǽ
}

//�������ʳ��ұ���������Χ��ǽ��
void RandNWFood()
{
    int i, j;
	do
	{ //ȷ������ʳ���λ��Ϊ�գ�����Ϊ������������
		i = rand() % ROW;
		j = rand() % COL;//�������ʳ��ĺ�������
	} while (ground[i][j] != EMPTY || IsSurroundWall(j, i));
	ground[i][j] = FOOD; //��ʳ��λ�ý��б��
	color(12); //��ɫ����Ϊ��ɫ
	setfillcolor(EGEARGB(0x80, 0xFF, 0x00, 0xFF));
	ege_fillellipse((j+EDGEX)*BOXX, (i+EDGEY)*BOXY, BOXX, BOXY);
}

//���λ���Ƿ񿿽���ͷ��������ΧΪ4��
int IsNearSnake(int x, int y,  LPSnakeHead head)
{
    SnakeBody *body = head->body;
    while (body != NULL)
    {
        int dx = abs(x - body->x);
        int dy = abs(y - body->y);
        if (dx <= 4 && dy <= 4)
        {
            return 1; //������ͷ������
        }
        body = body->next;
    }
    return 0; //�ǿ���
}

//�������ǽ��ĵ�ͼ
void InitRandGround(LPSnakeHead head)
{
    //���ɳ�ʼ��ͼ
    InitGround();

    //�������ǽ��
    int numwall = (ROW*COL)/24; //��ǽ��������Ϊ���ظ�����1/24
    while (numwall > 0)
    {
        int x = rand() % COL;
        int y = rand() % ROW;
        if (ground[y][x] == EMPTY && !IsNearSnake(x, y, head))
        { //������̰���߳�ʼ��λ����Χ����ǽ��
            ground[y][x] = WALL;
            //����ɫǽ��
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

//�ߵĵ����ƶ���Ŀ�ĵؼ��
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
        return 1;//ײǽ��ײ���壬����1
    }
    else if (ground[y][x] == FOOD)//��ԭ��ͷ��λ�����������㣬Ȼ����ͷ�ƶ����µ�λ��
    {
        ground[y][x] = HEAD;//�������
        ground[head->y][head->x] = BODY;
        
        SnakeBody *newbody;//�����µ�������
        newbody = (LPSnakeBody)malloc(sizeof(SnakeBody));
        newbody->x = head->x;
        newbody->y = head->y;

        newbody->next = head->body;//���µ���������뵽���������ͷ��
        head->body = newbody;

        head->x = x;//������ͷ����
        head->y = y;
        head->snakelen++;

        RandFood();
        return 2;//�Ե�ʳ�����2
    }
    else
    {
        ground[y][x] = HEAD;
        ground[head->y][head->x] = BODY;

        SnakeBody *p = head->body;//���µ�һ����������
        int tempX = p->x;//���浱ǰ��һ�����������
        int tempY = p->y;
        p->x = head->x;
        p->y = head->y;
        
        head->x = x;//������ͷ����
        head->y = y;

        int NewX, NewY;
        while (p->next != NULL)//���º�����������(��β�����ڴ˲�����δ����)
        {
            NewX = p->next->x;//������һ�����������
            NewY = p->next->y;
            p->next->x = tempX;//��һ����������������һ�����������
            p->next->y = tempY;
            tempX = NewX;//������һ�����������
            tempY = NewY;
            p = p->next;//�ƶ���һ��������
        }
        ground[p->y][p->x] = TAIL;//������β����
        ground[NewY][NewX] = EMPTY;//���ԭ����β������
        
        return 0;//�����ƶ�������0
    }
}

//��ǽģʽ���ߵĵ����ƶ���Ŀ�ĵؼ��
int MovePSnake(SnakeHead *head, int direction)
{
    int x = head->x;
    int y = head->y;
    switch (direction)
    {
        case UP:
            y--;
            if (y < 0) // ��ͷ�����ϱ߽�
                y = ROW - 1; // �ƶ����±߽�
            break;
        case DOWN:
            y++;
            if (y >= ROW) // �����±߽�
                y = 0; // �ƶ����ϱ߽�
            break;
        case LEFT:
            x--;
            if (x < 0) // ������߽�
                x = COL - 1; // �ƶ����ұ߽�
            break;
        case RIGHT:
            x++;
            if (x >= COL) // �����ұ߽�
                x = 0; // �ƶ�����߽�
            break;
        default:
            break;
    }

    if (ground[y][x] == BODY || ground[y][x] == HEAD || ground[y][x] == TAIL)
    {
        return 1;//ײ���壬����1
    }
    else if (ground[y][x] == FOOD)//��ԭ��ͷ��λ�����������㣬Ȼ����ͷ�ƶ����µ�λ��
    {
        ground[y][x] = HEAD;//�������
        ground[head->y][head->x] = BODY;
        
        SnakeBody *newbody;//�����µ�������
        newbody = (LPSnakeBody)malloc(sizeof(SnakeBody));
        newbody->x = head->x;
        newbody->y = head->y;

        newbody->next = head->body;//���µ���������뵽���������ͷ��
        head->body = newbody;

        head->x = x;//������ͷ����
        head->y = y;
        head->snakelen++;

        RandFood();
        return 2;//�Ե�ʳ�����2
    }
    else
    {
        ground[y][x] = HEAD;
        ground[head->y][head->x] = BODY;

        SnakeBody *p = head->body;//���µ�һ����������
        int tempX = p->x;//���浱ǰ��һ�����������
        int tempY = p->y;
        p->x = head->x;
        p->y = head->y;
        
        head->x = x;//������ͷ����
        head->y = y;

        int NewX, NewY;
        while (p->next != NULL)//���º�����������(��β�����ڴ˲�����δ����)
        {
            NewX = p->next->x;//������һ�����������
            NewY = p->next->y;
            p->next->x = tempX;//��һ����������������һ�����������
            p->next->y = tempY;
            tempX = NewX;//������һ�����������
            tempY = NewY;
            p = p->next;//�ƶ���һ��������
        }
        ground[p->y][p->x] = TAIL;//������β����
        ground[NewY][NewX] = EMPTY;//���ԭ����β������
        
        return 0;//�����ƶ�������0
    }
}