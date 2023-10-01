#include "includes.h"
#include "SnakeGUI.h"
#include "Snake.h"

//SnakeMode.cpp用于存放四种模式的实现

//单人模式游戏控制
void GameControl_single()
{
    int key;
    int flag = 0;
    int Numcheck;
    SnakeHead *head;
    head = InitSnake(-1, -1);//初始化蛇
    InitGround();//初始化地图
    PrintSnake(head,1,RIGHT);//打印蛇
    RandFood();//随机生成食物


    int direction = RIGHT;
	for (; is_run() && flag !=1; delay_fps(10)) 
    {   // 从队列中取出所有按键消息
        while (kbmsg()) 
    {
            key_msg keyMsg = getkey();
            if(keyMsg.key == 0x57){if (direction != DOWN){direction = UP;}break;}
            if(keyMsg.key == 0x53){if (direction != UP){direction = DOWN;}break;}
            if(keyMsg.key == 0x41){if (direction != RIGHT){direction = LEFT;}break;}
            if(keyMsg.key == 0x44){if (direction != LEFT){direction = RIGHT;}break;}
    }

        ClearSnake(head); //清除蛇
        flag = (int)MoveSnake(head, direction);//进行下一步移动
        printf("%d",flag);
        if (flag == 1)//撞墙或撞身体，游戏结束
        {
            cleardevice();
            delay_fps(10);             
            break;
        }
        else if (flag == 2)//吃到食物，长度+1
        {
            color(10); //颜色设置为绿色
            PrintSnake(head,1,direction);
            color(7); //颜色设置为白色
            xyprintf(BOXX*NUMX*0.7,BOXY*NUMY-50 , "current goal:%d",head->snakelen - 1);
            // music[1].Play(0);
        }
        else//正常移动
        {
            color(10); //颜色设置为绿色
            PrintSnake(head,1,direction);
            color(7); //颜色设置为白色
            xyprintf(BOXX*NUMX*0.7,BOXY*NUMY-50 , "current goal:%d",head->snakelen - 1);
        }
    }
    // music[3].Play(0);
    xyprintf(BOXX*NUMX*0.4,BOXY*NUMY/2 ,"Your score is:%d", head->snakelen - 1);
    delay_fps(10);
    system("pause");
}


//双人模式游戏控制
void GameControl_double()
{
    int key;
    int flag;
    int checkflag;//在非操作情况下检测蛇是否死亡
    int Numcheck;
    int check = 0;//用于检测按下按键的玩家为1号还是2号，都没有按下时为0
    int snakelive1 = 1;//用于检测1号玩家是否死亡，死亡为0，未死亡为1
    int snakelive2 = 1;//用于检测2号玩家是否死亡，死亡为0，未死亡为1

    SnakeHead *head1;
    SnakeHead *head2;
    head1 = InitSnake(3*COL/4, ROW/2);//初始化蛇
    head2 = InitSnake(COL/4, ROW/2);//初始化蛇
    InitGround();//初始化地图
    PrintSnake(head1,1,RIGHT);//打印蛇1
    PrintSnake(head2,2,RIGHT);//打印蛇2
    RandFood();//随机生成食物

    int direction1 = RIGHT;
    int direction2 = RIGHT;

    for (; is_run(); delay_fps(10)) 
    {
        while (kbmsg()) 
        {
            key_msg keyMsg = getkey();//获取键盘输入
            check = 0;
            switch (keyMsg.key)
            {
                case key_up://上
                    if (direction1 != DOWN && snakelive1 == 1)
                    {
                        direction1 = UP;
                        check = 1;
                    }
                    break;
                case key_down://下
                    if (direction1 != UP && snakelive1 == 1)
                    {
                        direction1 = DOWN;
                        check = 1;
                    }
                    break;
                case key_left://左
                    if (direction1 != RIGHT && snakelive1 == 1)
                    {
                        direction1 = LEFT;
                        check = 1;
                    }
                    break;
                case key_right://右
                    if (direction1 != LEFT && snakelive1 == 1)
                    {
                        direction1 = RIGHT;
                        check = 1;
                    }
                    break;
                case 0x57://上
                    if (direction2 != DOWN && snakelive2 == 1)
                    {
                        direction2 = UP;
                        check = 2;
                    }
                    break;
                case 0x53://下
                    if (direction2 != UP && snakelive2 == 1)
                    {
                        direction2 = DOWN;
                        check = 2;
                    }
                    break;
                case 0x41://左
                    if (direction2 != RIGHT && snakelive2 == 1)
                    {
                        direction2 = LEFT;
                        check = 2;
                    }
                    break;
                case 0x44://右
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

        ClearSnake(head1); //清除蛇1
        ClearSnake(head2); //清除蛇2

        setfillcolor(EGEARGB(0xFF, 0xFF, 0xFF, 0xFF));//背景色设置为白色
        if( check == 1 )
        {
            flag = MoveSnake(head1, direction1);//蛇1按照按键进行下一步移动
            checkflag = MoveSnake(head2, direction2);//蛇2按照原来的方向进行下一步移动
            if ( checkflag == 1 )//蛇2死亡
            {
                snakelive2 = 0;
            }
            if (flag == 1)//蛇1撞墙或撞身体，游戏结束
            {
                snakelive1 = 0;
                if( snakelive2 == 0 )//如果两蛇都死亡，游戏结束
                {
                    // music[3].Play(0);
                    break;
                }
            }
            else if (flag == 2)//吃到食物，长度+1
            {
                PrintSnake(head1,1,direction1);
                PrintSnake(head2,2,direction2);
                // music[1].Play(0);

                xyprintf(BOXX*NUMX*0.6,BOXY*NUMY*0.8 ,"当前玩家1得分:%d", head1->snakelen - 1);
            }
            else//正常移动
            {
                color(12); //颜色设置为红色
                PrintSnake(head1,1,direction1);
                color(9); //颜色设置为蓝色
                PrintSnake(head2,2,direction2);
                color(7); //颜色设置为白色

                xyprintf(BOXX*NUMX*0.6,BOXY*NUMY*0.8 ,"当前玩家1得分:%d", head1->snakelen - 1);
            }
        }
        else if( check == 2 )
        {
            checkflag = MoveSnake(head1, direction1);//蛇1按照原来的方向进行下一步移动
            flag = MoveSnake(head2, direction2);//蛇2按照按键进行下一步移动
            if ( checkflag == 1 )//蛇1死亡
            {
                snakelive1 = 0;
            }
            if (flag == 1)//撞墙或撞身体，游戏结束
            {
                snakelive2 = 0;
                if( snakelive1 == 0 )//如果两蛇都死亡，游戏结束
                {
                    break;
                }
            }
            else if (flag == 2)//吃到食物，长度+1
            {
                color(12); //颜色设置为红色
                PrintSnake(head1,1,direction1);
                color(9); //颜色设置为蓝色
                PrintSnake(head2,2,direction2);
                color(7); //颜色设置为白色

                xyprintf(BOXX*NUMX*0.6,BOXY*(NUMY*0.8+2) ,"当前玩家2得分:%d", head2->snakelen - 1);
            }
            else//正常移动
            {
                color(12); //颜色设置为红色
                PrintSnake(head1,1,direction1);
                color(9); //颜色设置为蓝色
                PrintSnake(head2,2,direction2);
                color(7); //颜色设置为白色

                xyprintf(BOXX*NUMX*0.6,BOXY*(NUMY*0.8+2) ,"当前玩家2得分:%d", head2->snakelen - 1);
            }
        }
        else//双方都没有按键输入
        {
            MoveSnake(head1, direction1);//蛇1按照原来的方向进行下一步移动
            MoveSnake(head2, direction2);//蛇2按照原来的方向进行下一步移动
            color(12); //颜色设置为红色
            PrintSnake(head1,1,direction1);
            color(9); //颜色设置为蓝色
            PrintSnake(head2,2,direction2);
            color(7); //颜色设置为白色

            xyprintf(BOXX*NUMX*0.6,BOXY*NUMY*0.8 ,"当前玩家1得分:%d", head1->snakelen - 1);
            xyprintf(BOXX*NUMX*0.6,BOXY*(NUMY*0.8+2) ,"当前玩家2得分:%d", head2->snakelen - 1);
        }
    }
    cleardevice();

        xyprintf(BOXX*NUMX*0.4,BOXY*NUMY/2 ,"Player1 score is:%d", head1->snakelen - 1);
        xyprintf(BOXX*NUMX*0.4,BOXY*(NUMY/2+5) ,"Player2 score is:%d", head2->snakelen - 1);
    delay_fps(10);
    system("pause");

}

//穿墙模式游戏控制
void GameControl_passwall()
{
    int key;
    int flag = 0;
    int Numcheck;
    SnakeHead *head;
    head = InitSnake(-1, -1);//初始化蛇
    PrintSnake(head,1,RIGHT);//打印蛇
    InitEmptyGround();//初始化空地图
    RandFood();//随机生成食物

    int direction = RIGHT;
    for (; is_run(); delay_fps(10)) 
    {// 从队列中取出所有按键消息
    while (kbmsg()) 
    {
            key_msg keyMsg = getkey();
            if(keyMsg.key == 0x57){if (direction != DOWN){direction = UP;}break;}
            if(keyMsg.key == 0x53){if (direction != UP){direction = DOWN;}break;}
            if(keyMsg.key == 0x41){if (direction != RIGHT){direction = LEFT;}break;}
            if(keyMsg.key == 0x44){if (direction != LEFT){direction = RIGHT;}break;}
    }

        ClearSnake(head); //清除蛇

        //重新绘制墙体
	    setlinestyle(PS_DASH); //设置线条样式为虚线
	    setlinewidth(1);
	    rectangle(BOXX*EDGEX-3,BOXY*EDGEY-3,BOXX*(ROW+EDGEX-1)+10,BOXY*(COL+EDGEY-1)+10);
        
        flag = MovePSnake(head, direction);//进行下一步移动

        if (flag == 1)//撞身体，游戏结束
        {
            cleardevice();
            // music[3].Play(0);
            xyprintf(BOXX*NUMX*0.5,BOXY*NUMY*0.5,"FAILURE.");
            break;
        }
        else if (flag == 2)//吃到食物，长度+1
        {
            color(10); //颜色设置为绿色
            PrintSnake(head,1,direction);
            color(7); //颜色设置为白色

            xyprintf(BOXX*NUMX*0.7,BOXY*NUMY-50 , "current goal:%d",head->snakelen - 1);
        }
        else//正常移动
        {
            color(10); //颜色设置为绿色
            PrintSnake(head,1,direction);
            color(7); //颜色设置为白色

            xyprintf(BOXX*NUMX*0.7,BOXY*NUMY-50 , "current goal:%d",head->snakelen - 1);
        }
    }
	xyprintf(BOXX*NUMX*0.4,BOXY*NUMY/2 ,"Your score is:%d", head->snakelen - 1);
    delay_fps(10);
    system("pause");
}

//随机墙体模式游戏控制
void GameControl_randwall(){

    int key;
    int flag;
    int Numcheck;
    LPSnakeHead head = InitSnake(-1, -1);
    InitRandGround(head);//初始化随机墙体地图
    PrintSnake(head,1,RIGHT);//打印蛇
    RandNWFood();//随机生成食物

    int direction = RIGHT;
    for (; is_run(); delay_fps(10)) 
    {// 从队列中取出所有按键消息
    while (kbmsg()) 
    {
            key_msg keyMsg = getkey();
            if(keyMsg.key == 0x57){if (direction != DOWN){direction = UP;}break;}
            if(keyMsg.key == 0x53){if (direction != UP){direction = DOWN;}break;}
            if(keyMsg.key == 0x41){if (direction != RIGHT){direction = LEFT;}break;}
            if(keyMsg.key == 0x44){if (direction != LEFT){direction = RIGHT;}break;}
    }

        ClearSnake(head); //清除蛇
        flag = MoveSnake(head, direction);//进行下一步移动

        if (flag == 1)//撞墙或撞身体，游戏结束
        {
            printf("%d",flag);   
            cleardevice();
            // music[3].Play(0);
            xyprintf(BOXX*NUMX*0.5,BOXY*NUMY*0.5,"FAILURE.");
            break;
        }
        else if (flag == 2)//吃到食物，长度+1
        {
            color(10); //颜色设置为绿色
            PrintSnake(head,1,direction);
            color(7); //颜色设置为白色
            // music[1].Play(0);

            xyprintf(BOXX*NUMX*0.7,BOXY*NUMY-50 , "current goal:%d",head->snakelen - 1);
        }
        else//正常移动
        {
            color(10); //颜色设置为绿色
            PrintSnake(head,1,direction);
            color(7); //颜色设置为白色

            xyprintf(BOXX*NUMX*0.7,BOXY*NUMY-50 , "current goal:%d",head->snakelen - 1);
        }
    }

	xyprintf(BOXX*NUMX*0.4,BOXY*NUMY/2 ,"Your score is:%d", head->snakelen - 1);
    delay_fps(10);
    system("pause");
}
