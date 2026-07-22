/*
决定开始根据功能记录遇到的各种函数


一、增加元素（新增、追加、插入）
vector.push_back ()：容器尾部追加元素
vector.emplace_back ()：原地构造对象，尾部新增元素
string::operator+=：字符串追加拼接
ofstream：向文件写入 / 追加内容
二、删除元素（移除、清空、销毁）
vector.erase (迭代器)：删除迭代器指向元素
ifstream/ofstream.close ()：关闭文件流，释放资源
三、查找、遍历、条件检索
find (begin, end, val)：区间查找指定值，返回迭代器
find_if (begin, end, lambda)：自定义条件查找元素
vector.begin ()：获取首元素迭代器
vector.end ()：获取末尾边界迭代器
四、获取长度、统计数量（计算类）
vector.size ()：统计容器内元素总个数
string.empty ()：判断字符串是否为空（长度是否为 0）
五、类型转换（文本↔数字）
stoi (string)：字符串 → int 整数
to_string (数值)：数字 → string 字符串
stringstream：实现字符串与其他类型互相转换、文本分割
六、字符串 / 文本分割工具
getline (流，str, 分隔符)：按分隔符截取字符串，支持文件流、stringstream、cin
七、控制台输入输出
cin：控制台标准输入
cout：控制台标准输出
cin.ignore ()：清理输入缓冲区残留换行
八、文件读写
ifstream：读取本地文件
ofstream：写入本地文件
九、时间相关
time ()：获取系统时间戳
localtime ()：时间戳转为本地时间结构体
strftime ()：格式化时间，生成可读时间字符串

*/