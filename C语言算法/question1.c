#include<stdio.h>
#include<string.h>
int x[100]={0},y[100]={0},z[110]={0};   //初始化为0，那么位数少的大数计算时将会自动补全0
int main()
{
	char a[100],b[100];
	int len,len1,len2;
	scanf("%s%s",a,b);
	len1=strlen(a);
	len2=strlen(b);

	int i,j=0,k=0;
	for(i=len1-1;i>=0;i--)
	{
		x[j]=a[i]-'0';
		j++;
	}
	for(i=len2-1;i>=0;i--)
	{
		y[k]=b[i]-'0';
		k++;
	}

	len=len1>len2?len1:len2;    //取位数多的大数作为基准长度

	i=0;
	int m=0;
	for(i=0;i<len;i++)
	{
		z[i]=(x[i]+y[i]+m)%10;
		if(x[i]+y[i]+m>=10)
			m=1;
		else
			m=0;
	}

	if(x[i-1]+y[i-1]+m>=10)   //如果最高位有进位，则需要补1
		z[i]=1;
	else
		i=i-1;
	for(;i>=0;i--)
		printf("%d",z[i]);
	printf("\n");
	return 0;

}