#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void print(int x)
{
	if (x > 9)
	{
		print(x/10);
	}
	printf("%d ", x%10);
}
int main()
{
	//一个打印这个数每位数的函数
	int n;
	scanf("%d", &n);
	print(n);
	return 0;
}
//这里的递归是不返回值的
//一般情况下，我们要自己设置一个递归的返回条件，实现递归的返回
//也需要知道递归的各个值之间的关系
