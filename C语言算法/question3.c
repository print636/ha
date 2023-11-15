#include<stdio.h>

int f[20001];

int main(){

    f[1] = 2;
    f[2] = 4;
    int k;
    scanf("%d",&k);
    for (int i = 3; i <= 10001; i++)
    {
        f[i] = (f[i - 1] + f[i - 2]) % 1000000007;
    }
    while (k--)
    {
        int n;
        scanf("%d",&n);
        long long int a = 4;
        for (int j = 3; j <= n; j++)
        {
            a *= 2;
        }
        printf("%lld\n",(a % 1000000007 - f[n] + 1000000007) % 1000000007);
        
    }
    return 0;
}