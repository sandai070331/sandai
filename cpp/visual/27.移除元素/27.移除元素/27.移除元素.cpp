

#include <iostream>

#include <fstream>

#include <vector>

#include <string>

#include <sstream>

#include <algorithm>

#include <ctime>

using namespace std;
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        auto it = std::remove(nums.begin(), nums.end(), val);
        nums.erase(it, nums.end());
        return (int)nums.size();
    }
};
/*这种解法是利用了remove接触所有元素，对所有正常元素给与点位
* 目标元素跳过的方式
* 最后，在所有正常元素排好顺序之后，把最后超出顺序处截断
* 这里提供另一种双指针的做法
* 
* int a=0;
* for(int x:nums)
*   if(x!=val)nums[a++]=x;
* nums.resize(k);
* .resize就是把nums的size大小强行变成k的大小
* 原理和上面差不多，都是这样一遍排好位置，之后强行改变
*/
int main()
{
    Solution a;
    vector<int>nums;
    int val;
    int x;
    cin >> x;
    nums.push_back(x);
    cin >> val;
    int k = a.removeElement(nums, val);
    return 0;
}