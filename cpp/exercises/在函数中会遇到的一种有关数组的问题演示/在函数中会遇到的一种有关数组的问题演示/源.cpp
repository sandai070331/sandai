#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
//这里用二分查找作为演示
//数组传参，传递的是首元素的地址，而不是整个数组
int chazhao(int arr[], int k, int sz)//在这里arr只有第一个数的地址
{
	//int sz = sizeof(arr) / sizeof(arr[0]);如果用了这一步，会导致结果一直是1
	int left = 0;
	int right = sz - 1;
	while (left <= right)
	{
		int mid = left + (right - left) / 2;
		if (arr[mid] > k)
		{
			left = mid + 1;
		}
		else if (arr[mid] < k)
		{
			right = mid - 1;
		}
		else
			return mid;

	}
	return -1;
}
int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9, };
	int k = 5;
	int sz = sizeof(arr) / sizeof(arr[0]);//问题就是这一步，我们不能把这一步移到函数里求值
	int flag = chazhao(arr, k,sz);
	if (flag == -1)
	{
		printf("没找到");
	}
	else
	{
		printf("找到了，下标是%d", flag);
	}
	return 0;
}