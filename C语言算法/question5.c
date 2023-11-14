#include <stdio.h>  
#include <string.h>
#define MAXN 200001
int a[MAXN], cf[MAXN];


  
int main() {  
    int t, n, i, j;  
    scanf("%d", &t);  
    while (t--) {  
        scanf("%d", &n);  
        for (i = 0; i < n; i++) {  
            scanf("%d", &a[i]);   
        }  
        memset(cf,0,sizeof(cf));
        int top = -1;

        for (i = 0; i < n; i++) {
            top++;
            if(a[i] > 0){
                j = top;
                while(j > top - a[i] + 1 && j > 0){
                    j--;         
                }
                cf[j] += 1;
                cf[top+1] -= 1;
            }
        }
        a[0] = cf[0];
        
        for(int k = 1; k < n; k++){
            a[k] = a[k-1] + cf[k];
        }
        for(int h = 0; h < n; h++){
            if(a[h] > 0){
                printf("1");
            }
            else{
                printf("0");
            }
        }
        printf("\n");
        memset(a,0,sizeof(a));
    }  
    return 0;  
}