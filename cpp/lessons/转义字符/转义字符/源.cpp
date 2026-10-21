#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
int main()
{
	printf("abc\n");//这里的\n是换行
	printf("abcde\n");
	//转义字符合集
	//   \? 书写多个问号时使用(现在的编译器不用了，老的会出其他东西)/但还是存在一些特殊情况，看情况用吧
	//   \' 表示字符常量'  （同上
	//   \" 字符串内部的双引号（同上
	//   \\ 表示反斜    (这个就是要用的
	//   \a 警告字符，蜂鸣
	//   \b 退格号 （次要
	//   \f 进纸符 （次要
	//   \n 换行
	//   \r 回车
	//   \t 水平制表符 识别成tab键,防止识别成t
	//   \v 垂直制表符 （次要
	//   \ddd 一个八进制的数字
	//   \xdd dd表示2个十六进制的数字
	printf("%s\n","(are you ok ??\\)");
	printf("%s\n", "（yes ?'\")");
		//1   printf（） 打印出，输出。。。头文件   <stdio.h>
		//2   scanf（）输入。。。（加法里有例子）
		//3 % d，打印数字
		//4 % s，打印字符串
		//5   enum（）（枚举）
		//enum color
		//{red，green，blue}
		//6 % c  打印字符
		//7   strlen（）  本意string length 求字符串常数    头文件 < string.h>
		//8 % f   打印float类的数据
		//9 % lf    打印double类型的数据
		//10 %zu    打印sizeof的返回值
	 printf("\a"); 
	 printf("%c\n", '\130');//  \ddd 表示八进制数 这里是八进制的130换成十进制是88 在ASCII表里，计算机将88读为X
	 printf("%c\n", '\x60');// \xdd 表示16进制数 同上
	 //这里的值如果超过ASCII表的值是不行的，读不了
	 printf("%d\n", strlen("djiwjs"));// \0不算长度 空格算



	return 0;
}