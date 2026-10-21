#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
void puni(int arr[],int n)//pupuËã·¨ ºÍÄæĞò
{
	int j;
	int i;
	for (i = 1; i < n; i++)
	{
		for (j = 2; j <= n; j++)
		{
			if (arr[j - 1] > arr[j])
			{
				int temp = arr[j- 1];
				arr[j - 1] = arr[j];
				arr[j] = temp;
				
			}
		}

	}
	for (j = 1; j <= n / 2; j++)
	{
		int temp = arr[j ];
		arr[j ] = arr[n+1-j];
		arr[n+1-j] = temp;
	}

	for (i = 1; i <= n; i++)
	{
		printf("%4d", arr[i]);
	}
}
int main()
{
	int n;
	scanf("%d", &n);
	int arr[1000];
	int i;
	for (i = 1; i <= n; i++)
	{
		scanf("%d", &arr[i]);
	}
	puni(arr, n);
	return 0;

}