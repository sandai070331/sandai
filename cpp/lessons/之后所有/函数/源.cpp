#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdio.h>


#define num 100//定义标识符常量
#define add(x,y)((x)+(y));//定义宏，就是一个过程
struct xuesheng
{
	char name[100];
	int age;
	char xingbie[100];
	char dianhua[100];
};



//注意，一般我们在不同部分之间要打空格，前端特殊符号
//后端要打逗号，但是一个部分之间绝对不能有空格，
//比如这里的定义宏
extern int Add(int x, int y);
extern int quanju;
void test()
{
	static  int ju = 1;
	//static是让它一直活着 static修饰局部变量时，
	//局部变量出了作用域不销毁，本质上static修饰局部变量时，改变了
	//变量的存储 从栈区到静态区
	ju++;
	printf("%d\n", ju);
}
int main()
{//typedef unsigned int uint;//类型重命名

	//unsigned int au = 0;


	int hanshu = 10;
	int hanshu2 = 20;

	int z = Add(hanshu, hanshu2);
	int w = add(hanshu, hanshu2);
	printf("%d\n", w);
	printf("%d\n", z);
	printf("%d\n", quanju);
	int i = 0;
	while (i < 10)
	{
		test();
		i++;
	}
	//int a = 1;
	//int* p = &a;
	//*p = 2;//解引用操作符，通过p存的的地址，找到p所指引的对象

	//uint wa = 1;
	struct xuesheng wzh= { "wzh",17,"nan","12345" };//结构体创建变量
	printf("%s %d %s %s\n",wzh.name,wzh. age,wzh. xingbie,wzh. dianhua);
	//（为什么放到其他项里面读不到这个结构体？
	//结构体对象   .成员名







	return 0;

}
//static
//修饰局部变量 修饰全局变量 修饰函数
//内存的相关知识 指针相关知识
//1.内存被分为小的内存单元,也就是字节（byte）,
// 每个都有一个地址 一字节=8bit
//2.32位电脑 在二进制中，有2的32次方个地址，也就是字节，
// 也就是二的三十二次方✖8bit
//3.%p  打印地址，一般打出看来时是十六进制，而当我们要
// 储存地址时，我们使用int* 如int*p
//这里的p就是指针变量，指针也其实就是地址，而前面也不
// 一定是int，p指向的量是什么类型，
// 就用什么，如float*也行
//多个指针这么写（int *p1，*p2；




//结构体相关知识
//（一种把单一类型组合在一起的做法   见最上方