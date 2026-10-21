#include<iostream>
#include<string>
using namespace std;

class ren
{
    public:
    ren()
    {
        cout <<"构造函数发力"<<endl;//函数一开始就会发力
    }
    ~ren()
    {
        cout <<"析构函数发力"<<endl;//函数一结束就会发力
    }
};

    void test()
    {
        ren r1;
    }
    int main()
    {
        test();
        ren r1;
        system("pause");
        return 0;
    }