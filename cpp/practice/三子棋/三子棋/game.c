#define _CRT_SECURE_NO_WARNINGS
#include "game.h"



void Initboard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}
//一号版本
/*void Displayboard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		printf(" %c | %c | %c  \n",board[i][0],board[i][1],board[i][2]);
		if(i!=row-1)
		printf("---|---|---\n");
	}
}
*/
void Displayboard(char board[ROW][COL], int row, int col)//棋盘的打印
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if(j != col - 1)
			printf(" %c |", board[i][j]);
			else
			printf(" %c \n", board[i][j]);
		}
		for (j = 0; j < col; j++)
		{
			if (j != col - 1)
				printf("---|");
			else
				printf("---\n");
		}
	}
}
void playermove(char board[ROW][COL],int row,int col)
{
	printf("玩家下棋\n");
	printf("请输入坐标(行 列):>");
	int x, y;
	
	while (1)
	{
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col&&board[x-1][y-1] == ' ')
			//board[x-1][y-1]!='*' & board[x - 1][y - 1] != '#')这样就优化了
		{
			board[x - 1][y - 1] = '*';
			break;
		}
		else
		{
			printf("错误输入！\n");
			printf("请重新输入:>");
			continue;
		}
	}
}
void computermove(char board[ROW][COL], int row, int col)
{
	printf("电脑下棋\n");
	int x, y;
	while (1)
	{
		x = rand() % row;//这里是实现任意一个数字（在row为3的情况下）实现数字在0 1 2之间的取值
		y = rand() % col;
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
		//else
		//{
		//	continue;
		//}
		//这一串代码甚至是不需要的

	}
}

/*void playermove1(char board[ROW][COL], int row, int col)
{
	printf("玩家下棋\n");
	printf("请输入坐标(行 列):>");
	int x, y;

	while (1)
	{
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col && board[x - 1][y - 1] != '*'&&board[x-1][y-1]!='#')
		{
			board[x - 1][y - 1] = '#';
			break;
		}
		else
		{
			printf("错误输入！\n");
			printf("请重新输入:>");
			continue;
		}
	}
	*/
    //留一个双人版本的
	//int checkwin(char board[ROW][COL])
	//{

	//}



