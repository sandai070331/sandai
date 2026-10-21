#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int shuzi(int i,int arra[],int arrb[],int a);
void yiwei(int w, int arra[], int arrb[], int a, int b);

int main()
{
	int arra[2000];
	int arrb[1000];
	int i;
	int a, b;
	int w;
	scanf("%d %d", &a, &b);
	for (i = 0; i < a; i++)
	{
		scanf("%d",&arra[i]);
	}
	for (i = 0; i < b; i++)
	{
		scanf("%d",&arrb[i]);
	}
	for (i = 0; i < b; i++)
	{
		w = shuzi(i,arra,arrb,a);
		if (w == a)
			arra[a] = arrb[i];
		else
		yiwei(w,arra,arrb,a,i);
		a++;
	}
	for (i = 0; i < a; i++)
	{
		printf("%d ", arra[i]);
	}
	
	return 0;
}
int shuzi(int i, int arra[], int arrb[],int a)//首先是没有考虑到特殊情况 在最左边 在最右边
{
	int z = 0;
	if (arrb[i]<= arra[0])
		return 0;
	if (arrb[i] >= arra[a - 1])
		return a;
	for(z=0;z<=a-2;z++)
	{
		if(arrb[i]>=arra[z]&&arrb[i]<=arra[z+1])
		return z+1;
	}
}
void yiwei(int w, int arra[], int arrb[],int a,int b)
{
	int i;
	for (i = a - 1; i >= w; i--)
	{
		arra[i + 1] = arra[i];
	}
	arra[w] = arrb[b];
}
