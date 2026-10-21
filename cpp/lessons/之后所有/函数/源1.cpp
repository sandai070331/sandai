#define _CRT_SECURE_NO_WARNINGS
int quanju = 1;//如果这里用static，就会报错，一位内全局变量是具有外部链接属性的
//编译+链接=可执行程序
//static修饰全局变量时，外部链接属性变成了内部链接属性。其他源文件就不能再使用了
int Add(int x, int y)
{
	return x + y;
}
//直接放会报错的，要用extern
//为什么会报错但是还是能出结果呢？因为函数是具有外部链接属性的，但是加上static，就会变成内部，
// 不再能用