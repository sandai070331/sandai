#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int add(int x, int y);//写一个声明，就能读到下面的函数了
int main()
{
	//首先是链式访问
	//看看下面的式子会是什么结果？
	printf("%d\n", printf("%d", printf("%d", 43)));
	//如果一个函数是有返回值的，那么这个函数可以进行链式访问，代替常数进入其他函数
	//这里的结果是4321
	int a = 5, b = 4;
	int sum = add(a, b);
	printf("%d\n", sum);



	return 0;
}
//这里是函数的定义
//我们一般会把函数放在最下面，目的是防止上面一个个调用顺序太麻烦
int add(int x, int y)
{
	return x + y;
}
//对函数的递归来说，其实是很需要刷题的，多写写自然会了
//你可以理解为递归是n次的函数功能的实现
//c语言中，函数可以嵌套调用，但是不能嵌套定义