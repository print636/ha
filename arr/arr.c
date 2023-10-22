
#include<stdio.h>

 void print(int (*p)[5], int r, int c)
{
	int i = 0;
	for(i=0 ; i <r; i++)
	{
		int j = 0;
		for
		(j = 0; j < c ; j++)
		{
			printf("%d ", *(*(p + i) + j));
		}
		printf("\n");
	}
}
int main()
{
	int arr[3][5] = {1,2,3,4,5,2,3,4,5,6,3,4,5,6,7};
	print(arr, 3, 5);

	return 0;
}
