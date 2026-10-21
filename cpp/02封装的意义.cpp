#include<iostream>
using namespace std;
const double PI=3.14;
class yuan
{
    //访问权限
    public://公共权限
    //属性
    int r;//半径
    //行为
    //获取圆的周长，用一个函数
    double jisuanZC()
    {
        return 2*PI*r;
    }
};
int main()
{
    //实际运用
    yuan c1;
    c1.r=10;
    cout <<"圆的周长为："<<c1.jisuanZC()<<endl;
}