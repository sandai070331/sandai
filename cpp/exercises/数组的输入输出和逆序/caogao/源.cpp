#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
int main()
{
	int m;
	int i = 0;
	scanf("%d", &m);
	int w=0;
	int arr[100000] = { 0 };
	while (m != 0)
	{
		arr[i] = m % 2;
		m = m / 2;
		i++;
		w++;
	}
	for (i = 0; i < w/2; i++)//加等号之后一定要算算特殊情况
	{
		int h = arr[i];
		arr[i] = arr[w-1 - i];
		arr[w-1 - i] = h;

	}
	for (i = 0; i <= w-1; i++)
	{
		printf("%d", arr[i]);
	}

	return 0;
}