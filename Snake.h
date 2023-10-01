
#include  "includes.h"
#include  "SnakeGUI.h"

//隐藏光标
void HideCursor();

//光标跳转
void CursorJump(int x, int y);

//颜色设置
void color(int c);

//初始化场地
void InitGround();

//初始化空场地
void InitEmptyGround();

//初始化蛇内存
LPSnakeHead InitSnake( int x, int y );

//清除蛇
void ClearSnake(SnakeHead *head);

//打印蛇
void PrintSnake(LPSnakeHead head,int num, int direction);

//随机生成食物
void RandFood();

//检查食物周围墙体情况
int IsSurroundWall(int x, int y);

//随机生成食物，且避免其三周围着墙壁
void RandNWFood();

//检查位置是否靠近蛇头、蛇身，范围为4格
int IsNearSnake(int x, int y,  LPSnakeHead head);

//随机生成墙体的地图
void InitRandGround(LPSnakeHead head);

//蛇的单次移动与目的地检测
int MoveSnake(SnakeHead *head, int direction);

//穿墙模式中蛇的单次移动与目的地检测
int MovePSnake(SnakeHead *head, int direction);

//单人模式游戏控制
void GameControl_single();

//双人模式游戏控制
void GameControl_double();

//穿墙模式游戏控制
void GameControl_passwall();

//随机墙体模式游戏控制
void GameControl_randwall();
