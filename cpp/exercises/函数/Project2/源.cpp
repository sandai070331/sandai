#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
//比较字符串要用strcmp（"",""）=0
//目录
/*
* 
* 1.函数定义  其实就是子程序
* 2.库函数
* 3.自定义函数
* 4.函数参数
* 5.函数调用
* 6.函数的声明和定义
* 7.函数的嵌套调用和链式访问
* 8.函数递归
*/
//简单的函数实例
int getmax(int x, int y)//返回值类型要啥前面写啥   这个是所谓的传值调用
{
	return(x > y ? x : y);//三木操作符，条件成立返回冒号前，不成立冒号后
}//这种是返回值的、
void jiaohuan(int* x, int* y)//（这里的x y 中存的是地址）一定要带星号 这个是传址调用
{
	int z =  *x;
	*x = *y;
	*y = z;
	
}//这种事不返回值的，而且，这里的吗，n，m只是有了c d的值，不影响cd，所以无法完成交换
//专业一点，这里的是形参，是对实参的一份临时拷贝，不影响实参
//这里要想实现，可以通过指针找地址的方式，这里最后呈现的是该过之后的方案
//一般，当我们想改变cd的值时，才会用到这个地址
int main()
{
	int a = 0, b = 0;
	scanf("%d %d", &a, &b);
	int m = getmax(a, b);
	printf("%d", m);
	int c = 0,d = 0;
	scanf("%d %d", &c, &d);
	jiaohuan(&c, &d);
	printf("%d %d", c, d);

	
	return 0;
}
//记一下二分查找的防止数值溢出的问题
//我们直接使用 《left+right》 /2。可能导致数值过大出现错误
//所以我们一般使用   （right+left）/2+left