#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
	int i=0;
	char arr[100];
	while(1)
	{
		scanf("%c", &arr[i]);
		if (arr[i] == '\n')
			break;
		i++;
	}
	 i = 0;
	while (1)
	{
		if (arr[i] == '\n')
			break;
		if (arr[i] >= 'a' && arr[i] <= 'z' - 3 || arr[i] >= 'A' && arr[i] <= 'Z' - 3)
			arr[i] = arr[i] + 3;
		else if (arr[i] == 'x' || arr[i] == 'y' || arr[i] == 'z' || arr[i] == 'X' || arr[i] == 'Y' || arr[i] == 'Z')
			arr[i] = arr[i] - 26 + 3;
		printf("%c", arr[i]);
		i++;
		
		
	}
		
	
	
	
	return 0;
}
