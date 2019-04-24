#include "stdafx.h"
#include <time.h>
#include <conio.h>


#define FRAMERWHIDTH 20  //一个小的格子的宽度
#define FRAMERHIGHT 20   //一个小的格子的高度

int Bound[4][4]; //抽象为地图
int RandNum_nFalge;   //是否添加一个新的随机数标志   1--->产生新的随机数   0--->不必产生新的随机数
int Gameover_nFlage;   //是否游戏结束   1--->游戏失败结束   2---->游戏胜利结束  0--->继续正常（游戏未结束）
int Score;  //游戏分数


//数组的移动          下标 k，j；    其中j为k后面的第一个不为0的数字
//左移动     
void MoveLeft()
{
	for (int i = 0; i < 4; i++)  //一共有4行
	{
		for (int k = 0, j = 1; j < 4; j++)   //每一行都是有4列（个数字）
		{
			if (Bound[i][j] > 0)   //在一行中，只判k只有遇到的第一个非0的个数字  （j>0）
			{
				if(Bound[i][k] == Bound[i][j]) //情况一:k == j  &&  j >0
				{
					Score +=  Bound[i][k++] *= 2;
					Bound[i][j] = 0;

					RandNum_nFalge = 1;
				}
				else if (Bound[i][k] == 0)     //情况二:k == 0  && j>0
				{
					Bound[i][k] = Bound[i][j];
					Bound[i][j] = 0;
					RandNum_nFalge = 1;
				}
				else                           //情况三:k != j &&j >0
				{
					Bound[i][++k] = Bound[i][j];
					if (k != j)
					{
						Bound[i][j] = 0;
						RandNum_nFalge = 1;
					}

				}

			}
		}
	}
}

//右移动
void MoveRight()
{
	for (int i = 0; i < 4; i++)  //一共有4行
	{
		for (int k = 3, j = 2; j >= 0; j--)   //每一行都是有4列（个数字）
		{
			if (Bound[i][j] > 0)   //在一行中，只判k只有遇到的第一个非0的个数字  （j>0）
			{
				if (Bound[i][k] == Bound[i][j]) //情况一:k == j  &&  j >0
				{
					Score += Bound[i][k--] *= 2;
					Bound[i][j] = 0;

					RandNum_nFalge = 1;
				}
				else if (Bound[i][k] == 0)     //情况二:k == 0  && j>0
				{
					Bound[i][k] = Bound[i][j];
					Bound[i][j] = 0;
					RandNum_nFalge = 1;
				}
				else                           //情况三:k != j &&j >0
				{
					Bound[i][--k] = Bound[i][j];
					if (k != j)
					{
						Bound[i][j] = 0;
						RandNum_nFalge = 1;
					}

				}

			}
		}
	}
}


//上移动
void MoveUp()
{
	for (int i = 0; i < 4; i++)  //一共有4列
	{
		for (int k = 0, j = 1; j < 4; j++)   //每一列都是有4个数
		{
			if (Bound[j][i] > 0)   //这个里面j为时刻变化的 数组行， i为每一轮变化一次的数组的列（这里面注意体会s数组的i和j的循环和数组里面的区别）
			{
				if (Bound[j][i] == Bound[k][i]) //情况一:k == j  &&  j >0
				{
					Score += Bound[k++][i] *= 2;
					Bound[j][i] = 0;
					RandNum_nFalge = 1;
				}
				else if (Bound[k][i] == 0)     //情况二:k == 0  && j>0
				{
					Bound[k][i] = Bound[j][i];
					Bound[j][i] = 0;
					RandNum_nFalge = 1;
				}
				else                           //情况三:k != j &&j >0
				{
					Bound[++k][i] = Bound[j][i];
					if (k != j)
					{
						Bound[j][i] = 0;
						RandNum_nFalge = 1;
					}

				}

			}
		}
	}
}


//下移动
void MoveDown()
{
	for (int i = 0; i < 4; i++)  //一共有4列
	{
		for (int k = 3, j = 2; j >= 0; j--)   //每一列都是有4个数
		{
			if (Bound[j][i] > 0)   //这个里面j为时刻变化的 数组行， i为每一轮变化一次的数组的列（这里面注意体会s数组的i和j的循环和数组里面的区别）
			{
				if (Bound[j][i] == Bound[k][i]) //情况一:k == j  &&  j >0
				{
					Score += Bound[k--][i] *= 2;
					Bound[j][i] = 0;
					RandNum_nFalge = 1;
				}
				else if (Bound[k][i] == 0)     //情况二:k == 0  && j>0
				{
					Bound[k][i] = Bound[j][i];
					Bound[j][i] = 0;
					RandNum_nFalge = 1;
				}
				else                           //情况三:k != j &&j >0
				{
					Bound[--k][i] = Bound[j][i];
					if (k != j)
					{
						Bound[j][i] = 0;
						RandNum_nFalge = 1;
					}

				}

			}
		}
	}
}

//控制游戏的键盘输入
void KeyboardInput()
{
	//char ch;

	switch (_getch())
	{
	case 'w':
	case 'W':
		MoveUp();
		break;
	case 'a':
	case 'A':
		MoveLeft();
		break;
	case 's':
	case 'S':
		MoveDown();
		break;
	case 'd':
	case 'D':
		
		MoveRight();
		break;

	default:
		break;

	}
	

}

//绘画出一行数字
void ShowNum_a_Line(int i)
{
	printf_s("                ┃          ┃          ┃          ┃          ┃\n");
	printf_s("                ┃");
	for (int j = 0; j < 4; j++)
	{
		if (0 != Bound[i][j])
		{
			printf_s("   %5d  ┃", Bound[i][j]);
		}
		else
		{
			printf_s("          ┃", Bound[i][j]);
		}
	}
		
	printf_s("\n");
	printf_s("                ┃          ┃          ┃          ┃          ┃\n");
}


//检测空余的各自的个数
int nCountNullNum()
{
	int n = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (0 == Bound[i][j])
				n++;
		}
	}

	return n;
}

//生成随机数(该函数只赋值一个空格)
void RandNum()
{
	srand((unsigned int)time(NULL));
	int n = rand() % nCountNullNum();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (0 == n)  //第n个为0的个子
			{
				Bound[i][j] = rand() % 3 ? 2 : 4;  //数组随机生成的第n个为0的空格子，随机赋值的2的该路是4的2倍
				goto a;
			}

			if (0 == Bound[i][j])   //数到第那n个位0的空格子
			{
				n--;
			}
		
		}
	}

a:;
	RandNum_nFalge = 0;
}


void ShowWindows()
{
	printf_s("\n\n\n		                  游戏名字:2048        分数:%-6d        开发者:诗情画意\n", Score);
	printf_s("		------------------------------------------------------------------------------------------\n");

    printf_s("		┏━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┳━━━━━━━━━━┓\n");
		for (int i = 0; i < 4; i++)
		{		
				if (i < 3)
				{
					ShowNum_a_Line(i);
					printf_s("		┣━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━╋━━━━━━━━━━┫\n"); 
					
				}
				if ( 3 == i)
				{
					ShowNum_a_Line(i);
					printf_s("		┗━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┻━━━━━━━━━━┛\n");
				}
		}

	printf_s("\n\n		  W:↑  A:←  S:↓  D:→\n");
}


//游戏开始之前随机初始化两个格子
void StartDate()
{
	RandNum();
	RandNum();
}


//游戏是否结束
void CheckGameOver()
{
	int n1 = 0, n2 = 0;//横着、竖着两个两个不相等的 次数 的计数器

	for (int i = 0; i < 4; i++)  //横着横着2个进行比较
	{
		for (int j = 0; j < 3; j++)
		{
			if (Bound[i][j] != Bound[i][j + 1])
			{
				n1++;   //n1最多只会比较12次
			}

			if (Bound[i][j] >= 2048)   //单独的一个判断单个的Bound[][]是否大于2048，大于就说明游戏结束（胜利）
			{
				Gameover_nFlage = 2;
			}
		}
	}

	for (int i = 0; i < 4; i++)  //竖着竖着2个进行比较
	{
		for (int j = 0; j < 3; j++)
		{
			if (Bound[j][i] != Bound[j + 1][i])
			{
				n2++;   //n2最多只会比较12次
			}

		}
	}

	if (n1 == 12 && n2 == 12)
	{
		Gameover_nFlage = 1;//游戏结束（游戏失败）
	}


}




//开始游戏循环
void StartGame()
{
	system("title 2048");  //改控制台标题名称
	system("color 0e");  //改控制台标题背景和内容的颜色


		//游戏开始位置代码---------------------￥￥（一局游戏完整）
	StartDate();
	while (true)
	{
		ShowWindows();
		KeyboardInput();
		CheckGameOver();

		if (1 == Gameover_nFlage)  //判断游戏结束的两种方法（Gameover_nFlage ==1 或 ==2）
		{
			printf_s("游戏失败，GAME OVER！！！\n");
		}
		if (2 == Gameover_nFlage)
		{
			printf_s("游戏胜利，GAME SUCCESS！！！\n");
		}


		if (1 == RandNum_nFalge)
		{
			RandNum();
		}
		system("cls");

	}
	//游戏结束位置代码---------------------￥￥（一局游戏完整）

}



