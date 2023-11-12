#include <stdio.h>  
  
int compressString(char* chars) {  
    int length = 0;  // �ַ�����ǰ����  
    int count = 1;   // ��ǰ�ַ����ظ�����  
  
    // ������1��ʼ��������Ϊ����0�϶����ַ����ĵ�һ���ַ�  
    int i = 1;
    for (i = 1; chars[i] != '\0'; i++) {  
        if (chars[i] == chars[i - 1]) {  
            count++;  // ����ַ���ͬ�������ظ�����
            
        } else {  
            chars[length++] = chars[i - 1];  // ���µ�ǰ�ַ�  
  
            // ����ظ���������1���򽫼���ת��Ϊ�ַ���ӵ��ַ�����  
            if (count > 1) {  
                char countStr[10];  // �洢�������ַ���  
                int countLength = sprintf(countStr, "%d", count);  // ������ת��Ϊ�ַ���  
                for (int j = 0; j < countLength; j++) {  
                    chars[length++] = countStr[j];  // ��ÿ�������ַ���ӵ��ַ�����  
                }
                
            }
            count = 1;  // �����ظ�����  
            
        }  
    }   
                chars[length++] = chars[i-1];
                if (count > 1) {  
                char countStr[10];  // �洢�������ַ���  
                int countLength = sprintf(countStr, "%d", count);  // ������ת��Ϊ�ַ���  
                for (int j = 0; j < countLength; j++) {  
                    chars[length++] = countStr[j];  // ��ÿ�������ַ���ӵ��ַ�����  
                } 

                }

  
    chars[length] = '\0';  // ����ַ���������  
    return length;         // �����µ��ַ�������  
}  
  
int main() {  
    char chars[1000];  
    scanf("%s", chars);  
    int length = compressString(chars);  
    printf("Compressed string: %s\n", chars);  
    printf("New length: %d\n", length);  
    return 0;  
}