#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
int main()
{
	printf("加入西理工\n");
	printf("会好好学习吗？（1/0 ）");
	int input = 0;
	scanf("%d", &input);
		if (input == 1)
		{
			printf("good\n");
		}
		else
		{
			printf("bad");
		}
		int daima = 0;
		printf("study\n");
		while (daima < 20)

		{
			printf("more and more;%d\n",daima);
			daima++;
		}
		return 0;
}
//c语言实现选择
// if else
// switch

//循环的三种形式while for do...while 语句
