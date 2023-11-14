#include<stdio.h>
#define MAXN 100001
int fa[MAXN], rank[MAXN];
int day = 1;

void init(int n){
    for (int i = 1; i <= n; ++i)
    {
        fa[i] = i;
        rank[i] = 1;
    }
}

int find(int x)
{
    if(x == fa[x])
        return x;
    else{
        fa[x] = find(fa[x]);  //���ڵ���Ϊ���ڵ�,�´�ʹ��ʱ�����ظ�����
        return fa[x];         
    }
}

//ͨ���ж�ָ��ĸ��ڵ��Ƿ����Լ����ж��Ƿ���ȫ�����������е���ȫ������ֻ�и��ڵ�ָ������
int panduan(int n){
    int k = 0;
    for(int j = 1; j <= n; j++){
        if(fa[j] == j){
            k++;
        }
    }
    if(k > 1){
        return 0;
    }
    else{
        return 1;
    }
}

void merge(int i, int j, int n)
{
    
    int x = find(i), y = find(j);    //���ҵ��������ڵ�
    if (rank[x] <= rank[y])
        fa[x] = y;
    else
        fa[y] = x;
    if (rank[x] == rank[y] && x != y)
        rank[y]++;                   //��������ͬ�Ҹ��ڵ㲻ͬ�����µĸ��ڵ�����+1
    if(!panduan(n))
    {
        day++;
    }
}

int main()
{
    int n, m, x, y;
    scanf("%d %d", &n, &m);
    init(n);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d %d", &x, &y);
        merge(x, y, n);
    }
    if(!panduan(n)){
        printf("-1");
    }
    else{
        printf("%d", day);
    }
    return 0;
    
}