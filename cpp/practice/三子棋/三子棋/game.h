#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//调用time函数

#define ROW 3//为了方便实现以后的修改
#define COL 3
void Initboard(char board[ROW][COL], int row, int col);
//棋子初始化

void Displayboard(char board[ROW][COL], int row, int col);
//棋盘打印

void playermove(char board[ROW][COL],int row,int col);
//玩家下棋

void computermove(char board[ROW][COL], int row, int col);
//电脑下棋
//随机数生成

//void playermove1(char board[ROW][COL], int row, int col);双人版
//void  checkwin(char board[ROW][COL]);//胜利检测

//随机数生成的一个方式
/*
* 使用rand()函数，可生成一套混乱的数字，但是这是根据()里的数字决定的
* 因此，为了模拟随机的情况，我们使用一个一直变化的数值   时间戳 输入()里面
* 实现伪随机的效果
*/

