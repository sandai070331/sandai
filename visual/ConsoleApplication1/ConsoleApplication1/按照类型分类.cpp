/*
*  决定开始按照作用类型记录自带函数
1. std::vector 容器对象 | #include <vector>
push_back ()：尾部追加元素
emplace_back ()：原地构造，尾部新增对象
erase (迭代器)：删除指定迭代器元素
size ()：获取容器元素数量
begin ()：获取首元素迭代器
end ()：获取末尾后边界迭代器
2. std::string 字符串对象 | #include <string>
operator+=：字符串拼接追加
empty ()：判断字符串是否为空
3. std::stringstream 字符串流对象 | #include <sstream>
作用：完成文本分割、数据类型转换
搭配全局函数 getline () 进行分段读取
4. 文件流对象 | #include <fstream>
ifstream：文件读取流，加载本地文件
ofstream：文件写入流，保存数据到文件
close ()：关闭文件流
5. 控制台 IO 对象 | #include <iostream>
cin：标准输入对象，读取控制台输入
cout：标准输出对象，打印信息
cin.ignore ()：清理输入缓冲区遗留换行
6. <algorithm> 全局独立函数（不属于任何对象）
find (起始迭代器，终止迭代器，目标值)：查找匹配元素
find_if (起始迭代器，终止迭代器，条件)：自定义条件查找
7. <string> 全局转换函数（独立函数）
stoi ()：字符串转为 int
to_string ()：数字转为字符串
8. <ctime> 时间相关 C 标准函数（独立函数）
time ()：获取当前时间戳
localtime ()：时间戳转为本地时间结构体
strftime ()：格式化时间，生成时间文本
9. 全局通用函数（无归属对象）
getline (流，字符串，分隔符)：对流按分隔符读取字符串
支持 cin、ifstream、stringstream 所有流类型
*/