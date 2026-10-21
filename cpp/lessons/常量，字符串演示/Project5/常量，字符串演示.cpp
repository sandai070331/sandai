#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include<stdio.h>
//下面是常量演示
#define w "wanzihan"//#define定义的标识符常量
 const int a = 100;//变量是一个空间 常量是一个值 const锁死了空间，只剩下一个值 但本质 还是空间
 //因此本质是变量
 //不太需要管常量变量
 
 //字面常量

 int main()
 {

	 printf("%s\n", w);
	 printf("%d\n", a);
	 enum color { red, green, blue };//枚举常量
	 enum color c = red;//red代表零
	 printf("%d\n", c);


	 //下面是字符串演示
	 //'w'字符
	 //"abced"字符串
	 char ah = 'u';
	 char shuzhu[] = "ajhsa";//这里末尾隐藏有一个\0,则不是要5个空间，是要6个
	 //数组和单个数组结果不同的原因是这个\0，\0就是终止密码子//本质上是转义字符
	 char dangeshuzu[] = { 'a','b','c','d','\0' };//加上之后世界和平，不加的话停不下来会乱码
	 printf("%s\n", shuzhu);
	 printf("%s\n", dangeshuzu);
	 printf("%c\n", ah);//给d能出来，给s出不来，要给c，c是什么？？？？

	 //新函数 strlen演示 需要头文件string.h
	 int g = strlen("hjkhuihi");
	 printf("%d\n", g);
	 //转义字符演示
	 printf("abc\nnjH\n");//此时\n代表的和\0一样，终止密码子
	 printf("abch\0hsh");//当两个打印一起时，不用转义字符   \n   换行的话，会打在一起\n和\0不同
	 //多种转义字符
	 //   \?  有时候有三字母词如  ??(   变成[  则，\？很有作用
	 //   \‘   要打'时，要用'\'才行



	 return 0;}