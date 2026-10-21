#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int main()
{
	int m;
	int i = 0;
	scanf("%d", &m);
	int arr[1000000] = {0};
	while(m != 0)
	{
		arr[i] = m % 2;
		m = m / 2;
		i++;
	}
	for (i = 0; i <= 9; i++)
	{
		printf("%d ", arr[i]);
	}
	
	return 0;
}