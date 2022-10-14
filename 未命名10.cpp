#include<stdio.h>
#include<windows.h>//������̬���塣֧Ԯ��̬���庯����ʹ���߽��溯�� ͼ��װ�ý��溯����
#include<conio.h> //�û�ͨ�������̲����Ķ�Ӧ���� (����̨��
#include<stdlib.h>
#include<time.h> //���ں�ʱ��ͷ�ļ�
#define LEN 30
#define WID 25
int Snake[LEN][WID] = {0}; //�����Ԫ�ش����ߵĸ�����λ
char Sna_Hea_Dir = 'a';//��¼��ͷ���ƶ�����
int Sna_Hea_X, Sna_Hea_Y;//��¼��ͷ��λ��
int Snake_Len = 3;//��¼�ߵĳ���
clock_t Now_Time;//��¼��ǰʱ�䣬�Ա��Զ��ƶ�
int Wait_Time ;//��¼�Զ��ƶ���ʱ����
int Eat_Apple = 1;//�Ե�ƻ����ʾΪ1
int Level ;
int All_Score = -1;
int Apple_Num = -1;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ��׼����ľ�� <windows.h>
//��� ����־Ӧ�ó����еĲ�ͬ�����ͬ������еĲ�ͬ��ʵ�� ����ٿأ�
void gotoxy(int x, int y)//���ù��λ��
{
COORD pos = {x,y}; //����һ���ַ��ڿ���̨��Ļ�ϵ�����POS
SetConsoleCursorPosition(hConsole, pos); //��λ���λ�õĺ���<windows.h>
}
void Hide_Cursor()//���ع�� �̶�����
{
CONSOLE_CURSOR_INFO cursor_info = {1, 0};
SetConsoleCursorInfo(hConsole, &cursor_info);
}
void SetColor(int color)//������ɫ
{
SetConsoleTextAttribute(hConsole, color);
//��API����������ɫ�ͱ���ɫ�ĺ��� ��ʽ��SetConsoleTextAttribute(���,��ɫ);
}
void Print_Snake()//��ӡ��ͷ���ߵĲ��Ӻ���β
{
int iy, ix, color;
for(iy = 0; iy < WID; ++iy)
for(ix = 0; ix < LEN; ++ix)
{
if(Snake[ix][iy] == 1)//��ͷ
{
SetColor(0xf); //oxf���������ڴ��ַ setcolor:34���Զ���������ɫ�ĺ���
gotoxy(ix*2, iy);
printf("��");
}
if(Snake[ix][iy] == 2)//�ߵĲ���
{
color = rand()%15 + 1; //rand()�����ǲ����������һ�����������C�����ﻹ�� srand()�����ȡ�
//ͷ�ļ�:stdlib.h
if(color == 14)
color -= rand() % 13 + 1; //��ɫ
SetColor(color);
gotoxy(ix*2, iy);
printf("��");
}
if(Snake[ix][iy] == Snake_Len)
{
gotoxy(ix*2, iy);
SetColor(0xe);
printf("��");
}
}
}
void Clear_Snake()//����̰����
{
int iy, ix;
for(iy = 0; iy < WID; ++iy)
for(ix = 0; ix < LEN; ++ix)
{
gotoxy(ix*2, iy);
if(Snake[ix][iy] == Snake_Len)
printf(" ");
}
}
void Rand_Apple()//�������ƻ��
{
int ix, iy;
do
{
ix = rand() % LEN;
iy = rand() % WID;
}while(Snake[ix][iy]);
Snake[ix][iy] = -1;
gotoxy(ix*2, iy);
printf("��");
Eat_Apple = 0;
}
void Game_Over()//��������
{
gotoxy(30, 10);
printf("Game Over");
Sleep(3000);
system("pause > nul");
exit(0);
}
void Move_Snake()//���߶�����
{
int ix, iy;
for(ix = 0; ix < LEN; ++ix)//�ȱ����ͷ
for(iy = 0; iy < WID; ++iy)
if(Snake[ix][iy] == 1)
{
switch(Sna_Hea_Dir)//�����µ���ͷ�����־��ͷ
{
case 'w':
if(iy == 0)
Game_Over();
else
Sna_Hea_Y = iy - 1;
Sna_Hea_X = ix;
break;
case 's':
if(iy == (WID -1))
Game_Over();
else
Sna_Hea_Y = iy + 1;
Sna_Hea_X = ix;
break;
case 'a':
if(ix == 0)
Game_Over();
else
Sna_Hea_X = ix - 1;
Sna_Hea_Y = iy;
break;
case 'd':
if(ix == (LEN - 1))
Game_Over();
else
Sna_Hea_X = ix + 1;
Sna_Hea_Y = iy;
break;
default:
break;
}
}
if(Snake[Sna_Hea_X][Sna_Hea_Y]!=1&&Snake[Sna_Hea_X][Sna_Hea_Y]!=0&&Snake[Sna_Hea_X][Sna_Hea_Y]!=-1)
Game_Over();
if(Snake[Sna_Hea_X][Sna_Hea_Y] < 0)//�Ե�ƻ��
{
++Snake_Len;
Eat_Apple = 1;
}
for(ix = 0; ix < LEN; ++ix)//������β
for(iy = 0; iy < WID; ++iy)
{
if(Snake[ix][iy] > 0)
{
if(Snake[ix][iy] != Snake_Len)
Snake[ix][iy] += 1;
else
Snake[ix][iy] = 0;
}
}
Snake[Sna_Hea_X][Sna_Hea_Y] = 1;//������ͷ
}
void Get_Input()//�����ߵ��ƶ�����
{
if(kbhit())
{
switch(getch())
{
case 87:
Sna_Hea_Dir = 'w';
break;
case 83:
Sna_Hea_Dir = 's';
break;
case 65:
Sna_Hea_Dir = 'a';
break;
case 68:
Sna_Hea_Dir = 'd';
break;
default:
break;
}
}
if(clock() - Now_Time >= Wait_Time)//�ߵ�ʱ���Զ�����
{
Clear_Snake();
Move_Snake();
Print_Snake();
Now_Time = clock();
}
}
void Init()//��ʼ��
{
system("title ̰��ëë��");
system("mode con: cols=80 lines=25");
Hide_Cursor();
gotoxy(61, 4);
printf("You Score:");
gotoxy(61, 6);
printf("You Level:");
gotoxy(61, 8);
printf("The Lenght:");
gotoxy(61, 10);
printf("The Speed:");
gotoxy(61, 12);
printf("Apple Num:");
int i;
for(i = 0; i < Snake_Len; ++i)//������
Snake[10+i][15] = i+1;
int iy, ix;//��ӡ��
for(iy = 0; iy < WID; ++iy)
for(ix = 0; ix < LEN; ++ix)
{
if(Snake[ix][iy])
{
SetColor(Snake[ix][iy]);
gotoxy(ix*2, iy);
printf("��");
}
}
}
void Pri_News()//��ӡ��Ϣ
{
SetColor(0xe);
gotoxy(73,4);
All_Score += Level;
printf("%3d", All_Score);
gotoxy(73, 6);
printf("%3d", Level);
gotoxy(73, 8);
printf("%3d",Snake_Len);
gotoxy(73, 10);
printf("0.%3ds", Wait_Time/10);
gotoxy(73, 12);
printf("%d", Apple_Num);
}
void Lev_Sys()//�ȼ�ϵͳ
{
if(((Apple_Num-1) / 10) == Level)
{
++Level;
if(Wait_Time > 50)
Wait_Time -= 50;
else
if(Wait_Time > 10)
Wait_Time -= 10;
else
Wait_Time -= 1;
}
}
int main(void)
{
Init();
srand((unsigned)time(NULL));//���������������
Now_Time = clock();
int speed1=1000,speed2,a;
printf("\n");
printf("����������Ҫ���ٶ�\n");
scanf("%d",&speed2);
Level=1;
Wait_Time=speed1-speed2;
printf("����������Ҫ��ƻ����\n");
scanf("%d",&a);
while(a--)
Rand_Apple();
while(1)
{
if(Eat_Apple)
{
++Apple_Num;
Rand_Apple();
Lev_Sys();
Pri_News();
}
Get_Input();
Sleep(10);
}
return 0;
}
