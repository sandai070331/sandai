#include <iostream>
using namespace std;
class Test
{
private:
    int a, b;
public:
    Test();
    void Print();
};
Test::Test()
{
    cin >> a >> b;
}
void Test::Print()
{
    cout << a - b << endl;
}

int main()
{
    Test t;
    t.Print();
    return 0;
}







