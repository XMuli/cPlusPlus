#pragma once

#include "stdafx.h"

//数组的移动
//左移动
void MoveLeft();
//右移动
void MoveRight();
//上移动
void MoveUp();
//下移动
void MoveDown();



//控制游戏的键盘输入
void KeyboardInput();
//绘画出一行数字
void ShowNum_a_Line(int i);
//检测空余的各自的个数
int nCountNullNum();
//生成随机数
void RandNum();
//界面显示和刷新
void ShowWindows();

//游戏是否结束
void CheckGameOver();

//开始游戏循环
void StartGame();

//游戏开始之前随机初始化两个格子
void StartDate();

