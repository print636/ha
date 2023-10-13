#include"stack.h"
#include<readline/readline.h>
#include"history.h"
#include <getopt.h> 

void compare_an() 
{
    // 使用diff工具对答案  
    int diff_result = system("diff result.txt answer.txt");
    if (diff_result != 0) 
    {  
        printf("程序输出与预期结果不符\n");  
        return;
    }  
    else
    {
        printf("程序输出与预期结果相同\n");
        return;
    }
}

void convert(double d, FILE *fp)   //将小数部分为0的数转换为整数  
{  
    if(( d - (int)d ) == 0 )  
    {   
        int i = (int)d;
        if(i == -404)
        {
          printf("该表达式有误\n");             
          if (fp)   // 如果打开了文件，将结果写入文件    
          {  
              fprintf(fp, "该表达式有误\n");    
          }    
        }
        else
        {
          printf("result>%d\n", i);             
          if (fp)   // 如果打开了文件，将结果写入文件    
          {  
              fprintf(fp, "%d\n", i);    
          }    
        }
    }     
    else
    {  
        printf("result>%lf\n", d);  
        if (fp)     
        {  
            fprintf(fp, "%lf\n", d);    
        }    
    }  
}
    

void handle_ctrl_u()
        { 
          rl_begin_undo_group();
          rl_delete_text(0, rl_point); 
          rl_end_undo_group();
        }

int main(int argc, char *argv[])
{
        
        printf("\033[31m");
        
        rl_initialize();
        rl_bind_key('\025', (rl_command_func_t *)&handle_ctrl_u);  //'\025'指的是ctrl_u
        
        using_history();
        
        
        Stack stack;
        init_stack(&stack);


	char input[100];
        char output[100];
        
        char *filename = NULL;  // 文件名指针
        char *filename2 = NULL;
        int opt;
        
        
                
            while ((opt = getopt(argc, argv, "t:s:")) != -1) 
       {       
               switch (opt)
           {   
            case 't':    
             filename = optarg; // 获取第一个文件名  
                break;    
            case 's':    
             filename2 = optarg; // 获取第二个文件名  
                break;    
            default:    
            printf("Usage: %s -t <file1> -s <file2>\n", argv[0]); // 给出正确输入格式  
                return 1;    
           }    
      } 
  
        FILE *fp = NULL;  // 文件指针
        FILE *fp2 = NULL;  
        
            if (filename2)   // 如果有文件名，打开文件 
    { 
         fp2 = fopen(filename2, "r");  
         if (!fp2) 
           { 
               printf("Error: Failed to open file %s\n", filename2);  
               return 1;  
           }  
    }  
        
          
        if (filename)   // 如果有文件名，打开文件  
    { 
         fp = fopen(filename, "w");  
         if (!fp) 
           { 
               printf("Error: Failed to open file %s\n", filename);  
               return 1;  
           }  
    }  
        
      
      if(fp && fp2)
       {
           char lines[100][1000];
           char outputf[1000];
           int lineNum = 0;
           
            while (fgets(lines[lineNum], 1000, fp2) != NULL) 
            { 
                     removet(lines[lineNum]);
                     verse(lines[lineNum], outputf); 
                     double result = calculate(outputf);
                     
                     convert(result, fp);
                     lineNum++; 
                                         
                     int size = sizeof(output) / sizeof(output[0]);               
                     memset(input, 0, size * sizeof(char));   //用完一次outputf需要清空
            }   
            compare_an();   
            printf("Yes!\n");     
      }
      else    
     {
            while(1)
        {
            printf("请输入中缀表达式：");
            char* line = readline("interaction> ");
            if(line == NULL)
            { break; }
            
         add_history(line);  
            
         strncpy(input, line, sizeof(input) - 1);         
         input[sizeof(input)-1] = '\0';
         
         removet(input);
         printf("去空格后：%s\n", input);
        
         if(strcmp(input, "help") == 0 )
       {    
           printf("帮助：1.你的计算器一直运行着，除非输入quit（程序崩溃或ctrl+c终止进程例外），每条表达式以键入enter结束。                  2.当输入表达式时，觉得表达式错了，可以键入ctrl+u清除当前行。                             3.通过↑,↓,可以查看历史命令(表达式)。                       4.你的计算器可以接受命令行参数-t <file>,-t表示你的计算器为后续测试作准备，计算器把每条表达式的结果输入到以-t参数为名字的文件中。                                     \n");
           
           free(line);       
           continue;
       }
       
        if(strcmp(input, "quit") == 0 )  
      {      
        free(line);         
        break;  
      }
        
	verse(input, output);  //转换
	printf("后缀表达式为：%s\n", output);
	double result = calculate(output);  //计算
    
	convert(result, fp);
	
	free(line);
	printf("-------END-------\n");
	
      }
      
     }
      
      if (fp)       // 关闭文件  
      {
        fclose(fp);
      }
      if (fp2)       // 关闭文件  
      {
        fclose(fp2);
      }
       printf("\033[0m");
       
       return 0;
}

 
