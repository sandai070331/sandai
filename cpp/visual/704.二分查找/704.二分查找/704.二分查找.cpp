// 704.二分查找.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS


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
    int search(vector<int>& nums, int target)
    {
        int right = (int)nums.size();
        int left = 0;
        while (left < right)
        {
            int mid = (left + right) / 2;
            if (nums[mid] < target)    
                left = mid + 1;  
            else
                right = mid;
        }
            //这一步就是要检测我所得到的值是不是target，为了节省，我们不在循环里次次比较结果而是拿到外面
            //在外面是没有mid的，在nums[mid]=target的时候，right成为了mid
            return(left < right && nums[left] == target) ? nums[left] : -1;
            //本来nums[left] == target作为比较就够了，可是当数字比所有数值都大的时候，最后left会等于right，right代表个数，left代表位置
        //这一块会越界，所以要确保不发生越位
    }
};  
int main()
{
    Solution a;
    int target;
    int n;
    cin >> n;
    vector<int>nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    cin >> target;
     cout << a.search(nums, target);
    return 0;
}