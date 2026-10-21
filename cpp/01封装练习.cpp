#include<iostream>
#include<string>
using namespace std;
class student
{
    public:
    int number;
    string name;
    void show()
    {
        cout << "学号是" << number << endl <<"姓名是" << name <<endl;
    }
    //赋值的另一种操作
    void setname(string nm)
    {
        name=nm;
    }
    //同样的，学号也可以这样
};
int main()
{
    student s1,s2;
    s1.name="张三";
    s1.number=12345;
    s1.show();
    s2.setname("李四");
    s2.number=12344;
    s2.show();
}