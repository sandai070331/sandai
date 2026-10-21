#define _CRT_SECURE_NO_WARNINGS

#include "game.h"
void menu()
{
	printf("********************\n");
	printf("********1.play******\n");
	printf("********0.exit******\n");
	printf("********************\n");
}
void game()
{
	char board[ROW][COL];
	Initboard(board, ROW, COL);//把几个棋子全部初始化，一开始全是空格
	Displayboard(board,ROW,COL);//把棋盘打印出来
	while (1)
	{
		playermove(board, ROW, COL);//开始下棋 玩家先下
		//检查玩家胜利没有

		Displayboard(board, ROW, COL);
		//playermove1(board, ROW, COL);双人版
		computermove(board,ROW,COL);//电脑下棋
		//检查电脑胜利没有

		Displayboard(board, ROW, COL);
		
	}
	//computermove(board, ROW, COL);
	//Displayboard(board, ROW, COL);

}
int main()
{
	//time(NULL)返回时间戳
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("请选择;>");
		scanf("%d", &input);
		switch(input)
		{
		case 1:
				printf("三子棋\n");
				game();
				break;
		case 0:
				printf("退出游戏\n");
				break;
		default:
			    printf("选择错误!\n");
				break;

		}

	} while (input);
	
	return 0;
}