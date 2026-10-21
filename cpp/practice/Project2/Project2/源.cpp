#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
struct xuesheng
{
	char name[20];
	int id;
};
int main()
{
	xuesheng a[3];
	int i;
	for (i = 0; i < 3; i++)
	{
		scanf("%s %d", &a[i].name, &a[i].id);
	}
	for (i = 0; i < 3; i++)
	{
		printf("%s %d", a[i].name, a[i].id);
	}

	return 0;
}