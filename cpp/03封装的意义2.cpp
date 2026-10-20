#include<iostream>
using namespace std;
/*
    public 公共权限。     类的内外都可以访问
    protected 保护权限。  类内可以访问，类外不能访问   ()
    private 私有权限。    类内可以访问，类外不能访问   ()
 */
class ren//class默认是私有，struct默认是公共
{
    public:
    string m_name;
    protected:
    string m_car;
    private:
    int m_password;
    public:
    void chaxun()
    {
        m_name="zhangsan";
        m_car="brnchi";
        m_password=12345;
    }
};
int main()
{

    ren r1;
    cout <<r1.m_name;//只能访问这个，其他不行
}