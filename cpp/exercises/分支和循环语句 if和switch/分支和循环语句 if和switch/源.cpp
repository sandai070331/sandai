#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
int main()
{
	
	//写一个有关于缓存区的这样一个代码  EOF就是getchar()读到末尾的特殊标记
	//一个只读取数字的代码
	//while ((w = getchar()) != '\n')
	//{
	//	;}
	//这样也行
	int ch;
	while ((ch = getchar()) != EOF)//这里getchar只能用char储存啊。。。
	{
		if (ch < '0' || ch > '9')
		{
			continue;
		}
		putchar(ch);
	}



	int n;
	scanf("%d",&n);
	if (n >= 1 && n <= 7)
	{
		switch (n)
		{
		case 1:
			printf("星期一");
			break;
		case 2:
			printf("星期二");
			break;
		case 3:
			printf("星期三");
			break;
		case 4:
			printf("xingqisi");
			break;
		case 5:
			printf("xingqiwu");
			break;
		case 6:
			printf("xingqiliu");
			break;
		case 7:
			printf("xingqitian");
			break;
		}
	}
	else
		printf("error");
	











	return 0;
	//break是永久终止循环 ，continue是跳过接下来的，回到while
}
