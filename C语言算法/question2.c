#include <stdio.h>  
  
int compressString(char* chars) {  
    int length = 0;  // 字符串当前长度  
    int count = 1;   // 当前字符的重复计数  
  
    // 从索引1开始遍历，因为索引0肯定是字符串的第一个字符  
    int i = 1;
    for (i = 1; chars[i] != '\0'; i++) {  
        if (chars[i] == chars[i - 1]) {  
            count++;  // 如果字符相同，增加重复计数
            
        } else {  
            chars[length++] = chars[i - 1];  // 更新当前字符  
  
            // 如果重复计数大于1，则将计数转化为字符添加到字符串中  
            if (count > 1) {  
                char countStr[10];  // 存储计数的字符串  
                int countLength = sprintf(countStr, "%d", count);  // 将计数转化为字符串  
                for (int j = 0; j < countLength; j++) {  
                    chars[length++] = countStr[j];  // 将每个数字字符添加到字符串中  
                }
                
            }
            count = 1;  // 重置重复计数  
            
        }  
    }   
                chars[length++] = chars[i-1];
                if (count > 1) {  
                char countStr[10];  // 存储计数的字符串  
                int countLength = sprintf(countStr, "%d", count);  // 将计数转化为字符串  
                for (int j = 0; j < countLength; j++) {  
                    chars[length++] = countStr[j];  // 将每个数字字符添加到字符串中  
                } 

                }

  
    chars[length] = '\0';  // 添加字符串结束符  
    return length;         // 返回新的字符串长度  
}  
  
int main() {  
    char chars[1000];  
    scanf("%s", chars);  
    int length = compressString(chars);  
    printf("Compressed string: %s\n", chars);  
    printf("New length: %d\n", length);  
    return 0;  
}