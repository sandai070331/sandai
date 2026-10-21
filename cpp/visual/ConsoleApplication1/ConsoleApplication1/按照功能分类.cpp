/*
决定开始根据功能记录遇到的各种函数

一、增加元素（新增、追加、插入）
vector.push_back ()：容器尾部追加元素 【头文件】<vector>
vector.emplace_back ()：原地构造对象，尾部新增元素 【头文件】<vector>
string::operator+=：字符串追加拼接 【头文件】<string>
ofstream：向文件写入 / 追加内容 【头文件】<fstream>
二、删除元素（移除、清空、销毁）
vector.erase (迭代器)：删除迭代器指向元素 【头文件】<vector>
ifstream/ofstream.close ()：关闭文件流，释放资源 【头文件】<fstream>
三、查找、遍历、条件检索
find (begin, end, val)：从 begin 到 end 区间查找指定值，找到返回对应迭代器，找不到返回 end 【头文件】<algorithm>
find_if (begin, end, lambda)：从 begin 到 end 区间，按照自定义条件查找元素 【头文件】<algorithm>
auto it = find_if(v.begin(),v.end(),[](int x){return x > 100;});（大于100，返回ture，这个数字的迭代器得到）
用auto 接住类型 *解开
vector.begin ()：获取容器首元素迭代器 【头文件】<vector>
vector.end ()：获取容器末尾边界迭代器（不指向有效元素）【头文件】<vector>
四、获取长度、统计数量（计算类）
vector.size ()：统计容器内当前元素总个数 【头文件】<vector>
string.empty ()：判断字符串是否为空，空返回 true，有内容返回 false 【头文件】<string>
五、类型转换（文本↔数字）
stoi (string)：字符串格式数字转换成 int 整数 【头文件】<string>
to_string (数值)：int、double 等数字转换成 string 字符串 【头文件】<string>
stringstream：实现字符串与其他类型互相转换、把字符串变成可分割的流 【头文件】<sstream>（取出会自动分割空格，其他符号分割自己写）
六、字符串 / 文本分割工具
getline (流，str, 分隔符)：从流中读取内容存入 str，遇到分隔符停止；支持 cin、文件流、stringstream 【头文件】<iostream> <sstream>
七、控制台输入输出
cin：控制台标准输入，读取键盘数据 【头文件】<iostream>
cout：控制台标准输出，向屏幕打印数据 【头文件】<iostream>
cin.ignore ()：清理输入缓冲区残留换行、空格，解决 cin 与 getline 混用 bug 【头文件】<iostream>
八、文件读写
ifstream：读取本地文件内容到程序 【头文件】<fstream>
ofstream：将程序数据写入本地文件 【头文件】<fstream>
九、时间相关
time ()：获取当前系统时间戳（长整型数字）【头文件】<ctime>
localtime ()：把时间戳转换成包含年月日时分秒的时间结构体 【头文件】<ctime>
strftime ()：格式化时间结构体，生成自定义格式的时间字符串 【头文件】<ctime>
十、区间反转、对象交换
reverse (a_begin, a_end)：从起始迭代器到末尾迭代器区间，元素顺序反转 【头文件】<algorithm>
swap (a,b)：交换 a、b 两个对象内部全部内容 【头文件】<algorithm>

*/