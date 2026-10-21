#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
struct
{
	char name[20];
	int id;
} xuesheng;
int main()
{
	xuesheng a[3];
	int i;
	for (i = 0; i < 3; i++)
	{
		scanf("%c %d", &a[i].name, &a[i].id);
	}
	for (i = 0; i < 3; i++)
	{
		printf("%c %d", a[i].name, a[i].id);
	}
	
	return 0;
}