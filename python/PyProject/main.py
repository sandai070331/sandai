"""我觉得要稍微记住以下的东西
list列表相关的函数   [  ,  ,  ]
编号	使用方式	            作用
1	列表.append (元素)	向列表中追加一个元素
2	列表.extend (容器)	将数据容器的内容依次取出，追加到列表尾部
3	列表.insert (下标，元素)	在指定下标处，插入指定的元素
4	del 列表 [下标]	删除列表指定下标元素
5	列表.pop (下标)	删除列表指定下标元素 列表.pop=取出的元素
6	列表.remove (元素)	从前向后，删除此元素第一个匹配项
7	列表.clear ()	清空列表
8	列表.count (元素)	统计此元素在列表中出现的次数
9	列表.index (元素)	查找指定元素在列表的下标，找不到报错 ValueError
10	len (列表)	统计容器内有多少元素
tuple 元组    (  ,  ,  )单个元素不是元组类型  函数和上面一样，只是不能修改
但是，元组里的列表，其内容是可以修改，删除，添加的
字符串
字符串
1  字符串[下标]                 根据下标索引取出特定位置字符
2  字符串.index(字符串)         查找给定字符的第一个匹配项的下标
3  字符串.replace(字符串1, 字符串2)   将字符串内的全部字符串1，替换为字符串2；不会修改原字符串，而是得到一个新的
4  字符串.split(字符串)         按照给定字符串，对字符串进行分隔；不会修改原字符串，而是得到一个新的列表
5  字符串.strip() / 字符串.strip(字符串)   移除首尾的空格和换行符或指定字符串
6  字符串.count(字符串)         统计字符串内某字符串的出现次数
7  len(字符串)                  统计字符串的字符个数
8  字符串.strip("123")删去旁边所以123，删除到其他字符就停下
9  字符串.find(子串)      查找子串第一个位置，找不到返回-1
10 字符串.rfind(子串)     查找子串最后一个位置，找不到返回-1（find和rfind是字符串特有的）
序列
序列
字符串 str、列表 list、元组 tuple
序列可以做切片
res = s[9:4:-1] 从第九个开始（第一个是0）取到第四个（不包含）【包含起点，不包含终点】
左起右终 +—决定方向
集合
集合的特点{1，2，3，4，5}
无序存储，不支持下标索引
自动去重，不允许存在重复数据
集合.add(元素)：添加元素
集合.remove(元素)：删除指定元素，不存在报错
集合.pop()：随机取出删除一个元素
集合.clear()：清空集合
集合1.difference(集合2)：求差集，返回新集合，原集合不变
集合1.difference_update(集合2)：求差集，直接修改集合 1
集合1.union(集合2)：求并集，返回新集合
集合1.intersection(集合2)：求交集，返回新集合
字典
字典就是key对应value{“name”：小明,“age”：20}
字典[Key]：获取 key 对应的值
字典[Key] = Value：新增 / 更新键值对
字典.pop(Key)：取出 value，同时删除该键值对
字典.clear()：清空字典
字典.keys()：获取所有键 key
len(字典)：统计键值对总数
字典可以嵌套写成
{"小明":{"age":20,"money":10,"level":low}}
使用时
a=[小明][age]   a=20


容器转化，能装数据的都是容器
max(容器)   获取容器内最大元素
min(容器)   获取容器内最小元素
len(容器)   统计容器内元素数量
list(容器)   转换为列表
tuple(容器)  转换为元组
str(容器)    转换为字符串
set(容器)    转换为集合（自动去重）
sorted(序列, reverse=True)
排序；reverse=True降序，reverse=False升序（默认）
返回新列表，不会修改原数据
sorted(my_list)          # 升序
sorted(my_list, reverse=True) # 降序
按照asc值排序 返回值是list

lambda匿名函数
lambda 参数列表：表达式（只能一次性使用）
lambda x, y: x + y
def test_func(compute):
    result = compute(1, 2)
    print(result)

# 传入lambda匿名函数
test_func(lambda x, y: x + y)
lambda x: "大" if x>10 else "小"（也可以写成这样，主要是方便）

文件操作
open(file,mode,encoding)：打开文件，获取文件对象
  说到mode就是
  r：只读；文件不存在会报错
  w：只写；文件不存在创建，存在会清空原有内容
  a：追加；文件不存在创建，在末尾新增内容
  说到encoding就是“utf-8”
.read(num)：读取全部 / 指定长度内容
.readline()：读取一行
.readlines()：读取所有行，返回列表
for line in 文件对象：循环逐行读取
.close()：手动关闭文件
with open() as f：自动关闭文件，优先使用

可变参数（先写普通参数，再写可变参数）
*args：可变位置参数 （多个参数打包成一个元组）
**kwargs：可变关键字参数（字典类型的使用，多个打包成字典，用法和上面相同）
（重点是**不是变量名）
def all_param(name, age, *args, **kwargs):
    print("普通参数：", name, age)
    print("位置可变参数args：", args)
    print("关键字可变参数kwargs：", kwargs)

all_param("张三", 19, "篮球", "游戏", addr="武汉", height=172)

异常捕捉
异常捕捉
try:
    # 可能发生异常的代码
except [异常类型 as 别名]: 也可以写except： 直接捕获所有异常
    # 出现异常执行这里
else:
    # 没有发生异常才执行
finally:
    # 无论是否异常，一定会执行

try:
    num = int(input("输入数字："))
except Exception as err:
    print(f"出错了：{err}")
else:
    print("输入正确")
finally:
    print("程序执行结束")

模块
模块
import 模块名
使用：模块名.功能()
from 模块名 import 函数1, 函数2
直接：函数1()
from 模块名 import *
一次性导入模块中公开功能（要是有）
import 模块名 as 别名
简化书写：别名.功能()
from 模块名 import 函数 as 别名
避免名字冲突，直接用别名调用

检测模块是否可行使用
if __name__ == "__main__"
（在模块页面运行可以得到ture，在主程序里得不到）
控制*的范围使用
__all__ = ["函数名"]（则只能用*导入all里的函数）

包的定义
包是存放多个模块（.py文件）的文件夹，用来对模块分类管理，逻辑上把功能相近代码归为一组。
__init__.py
文件夹内存在该文件，这个文件夹才会被 Python 识别为包（不是普通文件夹）；导入包时，这个文件内代码会自动执行。
__all__
写在__init__.py中，是字符串列表；专门控制 from 包名 import * 语句，只有列表内填写的模块才会被一次性导入。

my_package/             在这个文件夹里面调用包的模块
    __init__.py         要先写文件夹名再写文件名
    mod1.py             import my_package.mod1
    mod2.py             my_package.mod1.函数()


魔术方法
魔术方法
1 __init__：创建对象初始化
2 __str__：print / 转字符串
3 __lt__：小于 <
4 __le__：小于等于 <=
5 __eq__：等于 ==
6 __gt__：大于 >
7 __ge__：大于等于 >=



//稍微有点不太沾边的
JSON
JSON
JSON 是轻量级文本数据格式，本质就是字符串
不同语言之间交换数据


json.dumps()
Python 对象（字典 / 列表） → JSON 字符串
中文不乱码写法：json.dumps(data, ensure_ascii=False)
json.loads()
JSON 字符串 → Python 对象（字典 / 列表）


"""

