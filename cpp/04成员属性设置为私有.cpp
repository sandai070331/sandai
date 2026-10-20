//可以自己控制读写权限
//对于写入的数据可以检测数据有效性
#include<iostream>
#include<string>
using namespace std;

class ren
{
    public:
    void setname(string name)
    {
        m_name=name;
    }
    string getname()
    {
        return m_name;
    }
    string gethero()
    {
        return m_hero;
    }
    void setage(int age)
    {
        m_age=age;
    }
    void settall(int tall)//（设置身高只能在0到300之间）
    {
        if(a<0||a>300)
        cout <<"输入异常"<<endl;
        else
        m_tall=tall
    }
    int gettall()
    {
        return m_tall;
    }
    private:
    string m_name;//设置为可读可写
    string m_hero="man";//设置为可读
    int m_age;//设置为可写
    int m_tall=180;//设置为可读可写
};

int main()
{
    ren r1;
    r1.setname("andy");
    cout <<"名字是"<<r1.getname()<<endl;//有读函数和写函数，因此可读可写
    r1.setage(18);//只有写函数，因此可写
    cout <<"英雄是"<<r1.gethero()<<endl;//只有读函数，因此可读
    r1.settall(310);
    cout <<"身高是"<<r1.gettall()<<endl;
}