#include "includes.h"
#include "SnakeGUI.h"
#include "Snake.h"

//SnakeMode.cpp���ڴ������ģʽ��ʵ��

//����ģʽ��Ϸ����
void GameControl_single()
{
    int key;
    int flag = 0;
    int Numcheck;
    SnakeHead *head;
    head = InitSnake(-1, -1);//��ʼ����
    InitGround();//��ʼ����ͼ
    PrintSnake(head,1,RIGHT);//��ӡ��
    RandFood();//�������ʳ��


    int direction = RIGHT;
	for (; is_run() && flag !=1; delay_fps(10)) 
    {   // �Ӷ�����ȡ�����а�����Ϣ
        while (kbmsg()) 
    {
            key_msg keyMsg = getkey();
            if(keyMsg.key == 0x57){if (direction != DOWN){direction = UP;}break;}
            if(keyMsg.key == 0x53){if (direction != UP){direction = DOWN;}break;}
            if(keyMsg.key == 0x41){if (direction != RIGHT){direction = LEFT;}break;}
            if(keyMsg.key == 0x44){if (direction != LEFT){direction = RIGHT;}break;}
    }

        ClearSnake(head); //�����
        flag = (int)MoveSnake(head, direction);//������һ���ƶ�
        printf("%d",flag);
        if (flag == 1)//ײǽ��ײ���壬��Ϸ����
        {
            cleardevice();
            delay_fps(10);             
            break;
        }
        else if (flag == 2)//�Ե�ʳ�����+1
        {
            color(10); //��ɫ����Ϊ��ɫ
            PrintSnake(head,1,direction);
            color(7); //��ɫ����Ϊ��ɫ
            xyprintf(BOXX*NUMX*0.7,BOXY*NUMY-50 , "current goal:%d",head->snakelen - 1);
            // music[1].Play(0);
        }
        else//�����ƶ�
        {
            color(10); //��ɫ����Ϊ��ɫ
            PrintSnake(head,1,direction);
            color(7); //��ɫ����Ϊ��ɫ
            xyprintf(BOXX*NUMX*0.7,BOXY*NUMY-50 , "current goal:%d",head->snakelen - 1);
        }
    }
    // music[3].Play(0);
    xyprintf(BOXX*NUMX*0.4,BOXY*NUMY/2 ,"Your score is:%d", head->snakelen - 1);
    delay_fps(10);
    system("pause");
}


//˫��ģʽ��Ϸ����
void GameControl_double()
{
    int key;
    int flag;
    int checkflag;//�ڷǲ�������¼�����Ƿ�����
    int Numcheck;
    int check = 0;//���ڼ�ⰴ�°��������Ϊ1�Ż���2�ţ���û�а���ʱΪ0
    int snakelive1 = 1;//���ڼ��1������Ƿ�����������Ϊ0��δ����Ϊ1
    int snakelive2 = 1;//���ڼ��2������Ƿ�����������Ϊ0��δ����Ϊ1

    SnakeHead *head1;
    SnakeHead *head2;
    head1 = InitSnake(3*COL/4, ROW/2);//��ʼ����
    head2 = InitSnake(COL/4, ROW/2);//��ʼ����
    InitGround();//��ʼ����ͼ
    PrintSnake(head1,1,RIGHT);//��ӡ��1
    PrintSnake(head2,2,RIGHT);//��ӡ��2
    RandFood();//�������ʳ��

    int direction1 = RIGHT;
    int direction2 = RIGHT;

    for (; is_run(); delay_fps(10)) 
    {
        while (kbmsg()) 
        {
            key_msg keyMsg = getkey();//��ȡ��������
            check = 0;
            switch (keyMsg.key)
            {
                case key_up://��
                    if (direction1 != DOWN && snakelive1 == 1)
                    {
                        direction1 = UP;
                        check = 1;
                    }
                    break;
                case key_down://��
                    if (direction1 != UP && snakelive1 == 1)
                    {
                        direction1 = DOWN;
                        check = 1;
                    }
                    break;
                case key_left://��
                    if (direction1 != RIGHT && snakelive1 == 1)
                    {
                        direction1 = LEFT;
                        check = 1;
                    }
                    break;
                case key_right://��
                    if (direction1 != LEFT && snakelive1 == 1)
                    {
                        direction1 = RIGHT;
                        check = 1;
                    }
                    break;
                case 0x57://��
                    if (direction2 != DOWN && snakelive2 == 1)
                    {
                        direction2 = UP;
                        check = 2;
                    }
                    break;
                case 0x53://��
                    if (direction2 != UP && snakelive2 == 1)
                    {
                        direction2 = DOWN;
                        check = 2;
                    }
                    break;
                case 0x41://��
                    if (direction2 != RIGHT && snakelive2 == 1)
                    {
                        direction2 = LEFT;
                        check = 2;
                    }
                    break;
                case 0x44://��
                    if (direction2 != LEFT && snakelive2 == 1)
                    {
                        direction2 = RIGHT;
                        check = 2;
                    }
                    break;
                default:
                    break;
            }
        }

        ClearSnake(head1); //�����1
        ClearSnake(head2); //�����2

        setfillcolor(EGEARGB(0xFF, 0xFF, 0xFF, 0xFF));//����ɫ����Ϊ��ɫ
        if( check == 1 )
        {
            flag = MoveSnake(head1, direction1);//��1���հ���������һ���ƶ�
            checkflag = MoveSnake(head2, direction2);//��2����ԭ���ķ��������һ���ƶ�
            if ( checkflag == 1 )//��2����
            {
                snakelive2 = 0;
            }
            if (flag == 1)//��1ײǽ��ײ���壬��Ϸ����
            {
                snakelive1 = 0;
                if( snakelive2 == 0 )//������߶���������Ϸ����
                {
                    // music[3].Play(0);
                    break;
                }
            }
            else if (flag == 2)//�Ե�ʳ�����+1
            {
                PrintSnake(head1,1,direction1);
                PrintSnake(head2,2,direction2);
                // music[1].Play(0);

                xyprintf(BOXX*NUMX*0.6,BOXY*NUMY*0.8 ,"��ǰ���1�÷�:%d", head1->snakelen - 1);
            }
            else//�����ƶ�
            {
                color(12); //��ɫ����Ϊ��ɫ
                PrintSnake(head1,1,direction1);
                color(9); //��ɫ����Ϊ��ɫ
                PrintSnake(head2,2,direction2);
                color(7); //��ɫ����Ϊ��ɫ

                xyprintf(BOXX*NUMX*0.6,BOXY*NUMY*0.8 ,"��ǰ���1�÷�:%d", head1->snakelen - 1);
            }
        }
        else if( check == 2 )
        {
            checkflag = MoveSnake(head1, direction1);//��1����ԭ���ķ��������һ���ƶ�
            flag = MoveSnake(head2, direction2);//��2���հ���������һ���ƶ�
            if ( checkflag == 1 )//��1����
            {
                snakelive1 = 0;
            }
            if (flag == 1)//ײǽ��ײ���壬��Ϸ����
            {
                snakelive2 = 0;
                if( snakelive1 == 0 )//������߶���������Ϸ����
                {
                    break;
                }
            }
            else if (flag == 2)//�Ե�ʳ�����+1
            {
                color(12); //��ɫ����Ϊ��ɫ
                PrintSnake(head1,1,direction1);
                color(9); //��ɫ����Ϊ��ɫ
                PrintSnake(head2,2,direction2);
                color(7); //��ɫ����Ϊ��ɫ

                xyprintf(BOXX*NUMX*0.6,BOXY*(NUMY*0.8+2) ,"��ǰ���2�÷�:%d", head2->snakelen - 1);
            }
            else//�����ƶ�
            {
                color(12); //��ɫ����Ϊ��ɫ
                PrintSnake(head1,1,direction1);
                color(9); //��ɫ����Ϊ��ɫ
                PrintSnake(head2,2,direction2);
                color(7); //��ɫ����Ϊ��ɫ

                xyprintf(BOXX*NUMX*0.6,BOXY*(NUMY*0.8+2) ,"��ǰ���2�÷�:%d", head2->snakelen - 1);
            }
        }
        else//˫����û�а�������
        {
            MoveSnake(head1, direction1);//��1����ԭ���ķ��������һ���ƶ�
            MoveSnake(head2, direction2);//��2����ԭ���ķ��������һ���ƶ�
            color(12); //��ɫ����Ϊ��ɫ
            PrintSnake(head1,1,direction1);
            color(9); //��ɫ����Ϊ��ɫ
            PrintSnake(head2,2,direction2);
            color(7); //��ɫ����Ϊ��ɫ

            xyprintf(BOXX*NUMX*0.6,BOXY*NUMY*0.8 ,"��ǰ���1�÷�:%d", head1->snakelen - 1);
            xyprintf(BOXX*NUMX*0.6,BOXY*(NUMY*0.8+2) ,"��ǰ���2�÷�:%d", head2->snakelen - 1);
        }
    }
    cleardevice();

        xyprintf(BOXX*NUMX*0.4,BOXY*NUMY/2 ,"Player1 score is:%d", head1->snakelen - 1);
        xyprintf(BOXX*NUMX*0.4,BOXY*(NUMY/2+5) ,"Player2 score is:%d", head2->snakelen - 1);
    delay_fps(10);
    system("pause");

}

//��ǽģʽ��Ϸ����
void GameControl_passwall()
{
    int key;
    int flag = 0;
    int Numcheck;
    SnakeHead *head;
    head = InitSnake(-1, -1);//��ʼ����
    PrintSnake(head,1,RIGHT);//��ӡ��
    InitEmptyGround();//��ʼ���յ�ͼ
    RandFood();//�������ʳ��

    int direction = RIGHT;
    for (; is_run(); delay_fps(10)) 
    {// �Ӷ�����ȡ�����а�����Ϣ
    while (kbmsg()) 
    {
            key_msg keyMsg = getkey();
            if(keyMsg.key == 0x57){if (direction != DOWN){direction = UP;}break;}
            if(keyMsg.key == 0x53){if (direction != UP){direction = DOWN;}break;}
            if(keyMsg.key == 0x41){if (direction != RIGHT){direction = LEFT;}break;}
            if(keyMsg.key == 0x44){if (direction != LEFT){direction = RIGHT;}break;}
    }

        ClearSnake(head); //�����

        //���»���ǽ��
	    setlinestyle(PS_DASH); //����������ʽΪ����
	    setlinewidth(1);
	    rectangle(BOXX*EDGEX-3,BOXY*EDGEY-3,BOXX*(ROW+EDGEX-1)+10,BOXY*(COL+EDGEY-1)+10);
        
        flag = MovePSnake(head, direction);//������һ���ƶ�

        if (flag == 1)//ײ���壬��Ϸ����
        {
            cleardevice();
            // music[3].Play(0);
            xyprintf(BOXX*NUMX*0.5,BOXY*NUMY*0.5,"FAILURE.");
            break;
        }
        else if (flag == 2)//�Ե�ʳ�����+1
        {
            color(10); //��ɫ����Ϊ��ɫ
            PrintSnake(head,1,direction);
            color(7); //��ɫ����Ϊ��ɫ

            xyprintf(BOXX*NUMX*0.7,BOXY*NUMY-50 , "current goal:%d",head->snakelen - 1);
        }
        else//�����ƶ�
        {
            color(10); //��ɫ����Ϊ��ɫ
            PrintSnake(head,1,direction);
            color(7); //��ɫ����Ϊ��ɫ

            xyprintf(BOXX*NUMX*0.7,BOXY*NUMY-50 , "current goal:%d",head->snakelen - 1);
        }
    }
	xyprintf(BOXX*NUMX*0.4,BOXY*NUMY/2 ,"Your score is:%d", head->snakelen - 1);
    delay_fps(10);
    system("pause");
}

//���ǽ��ģʽ��Ϸ����
void GameControl_randwall(){

    int key;
    int flag;
    int Numcheck;
    LPSnakeHead head = InitSnake(-1, -1);
    InitRandGround(head);//��ʼ�����ǽ���ͼ
    PrintSnake(head,1,RIGHT);//��ӡ��
    RandNWFood();//�������ʳ��

    int direction = RIGHT;
    for (; is_run(); delay_fps(10)) 
    {// �Ӷ�����ȡ�����а�����Ϣ
    while (kbmsg()) 
    {
            key_msg keyMsg = getkey();
            if(keyMsg.key == 0x57){if (direction != DOWN){direction = UP;}break;}
            if(keyMsg.key == 0x53){if (direction != UP){direction = DOWN;}break;}
            if(keyMsg.key == 0x41){if (direction != RIGHT){direction = LEFT;}break;}
            if(keyMsg.key == 0x44){if (direction != LEFT){direction = RIGHT;}break;}
    }

        ClearSnake(head); //�����
        flag = MoveSnake(head, direction);//������һ���ƶ�

        if (flag == 1)//ײǽ��ײ���壬��Ϸ����
        {
            printf("%d",flag);   
            cleardevice();
            // music[3].Play(0);
            xyprintf(BOXX*NUMX*0.5,BOXY*NUMY*0.5,"FAILURE.");
            break;
        }
        else if (flag == 2)//�Ե�ʳ�����+1
        {
            color(10); //��ɫ����Ϊ��ɫ
            PrintSnake(head,1,direction);
            color(7); //��ɫ����Ϊ��ɫ
            // music[1].Play(0);

            xyprintf(BOXX*NUMX*0.7,BOXY*NUMY-50 , "current goal:%d",head->snakelen - 1);
        }
        else//�����ƶ�
        {
            color(10); //��ɫ����Ϊ��ɫ
            PrintSnake(head,1,direction);
            color(7); //��ɫ����Ϊ��ɫ

            xyprintf(BOXX*NUMX*0.7,BOXY*NUMY-50 , "current goal:%d",head->snakelen - 1);
        }
    }

	xyprintf(BOXX*NUMX*0.4,BOXY*NUMY/2 ,"Your score is:%d", head->snakelen - 1);
    delay_fps(10);
    system("pause");
}
