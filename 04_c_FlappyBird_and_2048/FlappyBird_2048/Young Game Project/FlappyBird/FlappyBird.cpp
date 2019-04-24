// FlappyBird.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h> 
#include <conio.h>
#include <time.h>

#define MAX 100
                                    //Map[][] 地图数值说明:0-- - ' '  1-- - '$'  2-- - '*'  3-- - '~'   4-- - '|'
int g_MapHight, g_MapWidth;         //实际地图的场景大小（注意：这两个数值都是比Map[][]的数组大小要小）
int g_BridX, g_BridY;               //鸟的横、纵坐标
int g_ThroughX, g_ThroughY;         //障碍物的 基准中心坐标
int Map[MAX][MAX] = {0};                  //题图场景（用来存储地图每一个区域的数值，数值不同对应不同的符号， 而地图就是由许许多多的符号构成）   
bool Book[MAX][MAX] = { false };    //true---触碰死亡   false---触碰未死亡
bool g_Result = false;              //true---游戏结束     false---游戏未结束
int g_Score;                        //分数成绩


//.初始化最基础的数据 
void StartUp();

//.初始化地图等
void StartMap();

//.清除控制台的光标
void HideCursor();

//.显示游戏页面
void Show();

//.刷新游戏的界面
void UpDateOutPut();

//.监测键盘的输入
void UpDateInPut();




int main()
{
	system("title Flappy Bird");
	system("color 0e");

	char ch = 'y';
	//char ch1 = 'y';
	int i = 1;
	printf_s("你先开始Flappy Bird小游戏吗？(Y/N)");
	scanf_s("%c", &ch);

	if ('y' == ch || 'Y' == ch)
	{
	
			//while ('y' == ch1 || 'Y' == ch1)
		    while (1 == i)
			{
				StartUp();                //.初始化最基础的数据 

				while (true)
				{
					HideCursor();         //.清除控制台的光标 
					StartMap();           //.初始化地图等
					Show();               //.显示游戏页面
					UpDateInPut();        //.监测键盘的输入
					UpDateOutPut();       //.刷新游戏的界面
					if (true == g_Result)
					{
						break;
					}
					system("cls");
				}

				//system("cls");
				printf_s("你输了~~~~\n\n你还要继续游戏吗？(1-->继续   2-->不继续)\n");
				scanf_s("%d", &i);
				if (1 == i)
				{
					g_Result = false;
				}
				system("cls");
			}

			

		}

	printf("欢迎下次运行Flappy Bird小游戏~~~\n");
    return 0;
}




//.初始化最基础的数据
void StartUp()
{
	g_Score = 0;
	g_MapHight = 30;                         //地图实际的高度（推荐20）    --->数值越大，闪烁越厉害
	g_MapWidth = 100;                        //地图实际的宽度（推荐50）   --->数值越大，闪烁越厉害
	g_BridX = g_MapWidth / 4;
	g_BridY = g_MapHight / 2;
	g_ThroughX = g_MapWidth / 4 * 3;
	g_ThroughY = g_MapHight / 2;
}

//.初始化地图等    //0---' '  1---'$'  2---'*'  3---'~'   4---'|'   //true---触碰死亡   false---触碰未死亡
void StartMap()
{
	int i, j;//i表示行，往下移动； j表示列，往右移动

	for (i = 0; i <= g_MapHight - 1; i++)
	{
		for (j = 0; j <= g_MapWidth - 1; j++)
		{
			Map[i][j] = 0;
		}

	}

	//Map[MAX][MAX] = {1};  //MMP  原来一直都是这里出了错误，  这是Map[100][100]元素复制唯一
	                        //浪费一个晚上和一个上午，就找到这个原因  真的是他妈的坑爹啊，不能这一行来代替上面两个for循环给Map[][]每一个都赋值

	//初始化上下围墙
	for ( j = 0; j < g_MapWidth; j++)
	{
		Map[0][j] = Map[g_MapHight-1][j] =3;
	}

	//初始化左右围墙
	for (i = 0; i < g_MapHight; i++)
	{
		Map[i][0] = Map[i][g_MapWidth-1] =4;
	}

	//初始化小鸟位置
	Map[g_BridY][g_BridX] = 1;

	//初始化障碍墙
	for (i = 1; i < g_MapHight-1; i++)
	{
		Map[i][g_ThroughX] = 2;
		Book[i][g_ThroughX] = true;
	}
	
	//初始化一个通道出来
	for ( i = g_ThroughY-2; i < g_ThroughY+2; i++)
	{
		Map[i][g_ThroughX] = 0;
		Book[i][g_ThroughX] = false;
	}
}


//.清除控制台的光标
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

//.显示游戏页面
void Show()
{
	//Gotoxy(0, 0);
	int i, j;
	for ( i = 0; i < g_MapHight; i++)
	{
		for ( j = 0; j <g_MapWidth; j++)
		{
			switch (Map[i][j])
			{
			case 0:printf(" ");
				break;
			case 1:printf("$");
				break;
			case 2:printf("*");
				break;
			case 3:printf("~");
				break;
			case 4:printf("|");
				break;
			default:
				break;
			}
		}

		printf("\n");
	}

	printf("你的分数是:%d 分\n", g_Score);
	printf("提示： 按键W或空格是往上面运动\n");

}


//.刷新游戏的界面
void UpDateOutPut()
{
	g_BridY++;
	g_ThroughX--;

	//鸟触碰死亡
 	if (true == Book[g_BridY][g_BridX] || g_BridY <= 0 || g_BridY >= g_MapHight-1)
	{
		g_Result = true;
	}

	//鸟跨过障碍物，得分
	if (g_BridX == g_ThroughX+1 )
	{
		g_Score++;
	}

	if (g_ThroughX < 1)
	{
		srand(time(NULL));  //获取随机数的种子
		g_ThroughY = rand() % g_MapHight;

		while (g_ThroughY <= 3 || g_ThroughY >= g_MapHight-4)   
		{
			g_ThroughY = rand() % g_MapHight;
		}

		g_ThroughX = g_MapWidth / 4 * 3;
	}

	memset(Book, 0, sizeof(Book));   //??????
	Sleep(100);
}


//.监测键盘的输入
void UpDateInPut()
{
	char ch;
	if (_kbhit())
	{
		ch = _getch();
		if (' ' == ch || 'w' == ch)
		{
			g_BridY -= 2;
		}
	}
}


