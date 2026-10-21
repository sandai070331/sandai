#define _CRT_SECURE_NO_WARNINGS//一个系统给的方案
#include<stdio.h>//系统的东西要调用
int main()//主函数
{
	//搞一个初始化的量，可以不是零
	int num1 = 2;
	int num2 = 0;
	//下面的是输入两个值
	//scanf("%d %d", &num1, &num2);//%什么意思？？？
	//转入加起来的函数
	int sum = num1 + num2;
	//输出/打印出这个东西
	printf("%d\n",sum);
	return 0;
}