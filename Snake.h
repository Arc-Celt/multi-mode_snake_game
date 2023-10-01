
#include  "includes.h"
#include  "SnakeGUI.h"

//���ع��
void HideCursor();

//�����ת
void CursorJump(int x, int y);

//��ɫ����
void color(int c);

//��ʼ������
void InitGround();

//��ʼ���ճ���
void InitEmptyGround();

//��ʼ�����ڴ�
LPSnakeHead InitSnake( int x, int y );

//�����
void ClearSnake(SnakeHead *head);

//��ӡ��
void PrintSnake(LPSnakeHead head,int num, int direction);

//�������ʳ��
void RandFood();

//���ʳ����Χǽ�����
int IsSurroundWall(int x, int y);

//�������ʳ��ұ���������Χ��ǽ��
void RandNWFood();

//���λ���Ƿ񿿽���ͷ��������ΧΪ4��
int IsNearSnake(int x, int y,  LPSnakeHead head);

//�������ǽ��ĵ�ͼ
void InitRandGround(LPSnakeHead head);

//�ߵĵ����ƶ���Ŀ�ĵؼ��
int MoveSnake(SnakeHead *head, int direction);

//��ǽģʽ���ߵĵ����ƶ���Ŀ�ĵؼ��
int MovePSnake(SnakeHead *head, int direction);

//����ģʽ��Ϸ����
void GameControl_single();

//˫��ģʽ��Ϸ����
void GameControl_double();

//��ǽģʽ��Ϸ����
void GameControl_passwall();

//���ǽ��ģʽ��Ϸ����
void GameControl_randwall();
