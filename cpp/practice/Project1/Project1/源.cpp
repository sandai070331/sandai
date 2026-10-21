#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

void pupu(int arr[], int m)
{
	int i, j;
	for (j = 0; j < m; j++)
	{
		for (i = 0; i < m - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
			}
		}
	}
	for (i = 0; i < m; i++)
	{
		printf("%d \n", arr[i]);
	}
	for (i = 0; i < m / 2; i++)
	{
		int temp = arr[i];
		arr[i] = arr[m - 1 - i];
		arr[m - 1 - i] = temp;
	}
	for (i = 0; i < m; i++)
	{
		printf("%d ", arr[i]);
	}
}

int main()
{
	int arr[1000];
	int m;
	scanf("%d", &m);
	int i;
	for (i = 0; i < m; i++)
	{
		scanf("%d", &arr[i]);
	}
	pupu(arr, m);
	return 0;
}