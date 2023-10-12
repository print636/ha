#include"stack.h"
#include<readline/readline.h>
#include"history.h"
#include <getopt.h> 

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
        int opt;
        
         while ((opt = getopt(argc, argv, "t:")) != -1) 
         {
            switch (opt) 
            {  
             case 't':  
                 filename = optarg;  // 获取文件名
                 break;  
             default:  
                 printf("Usage: %s -t <file>\n", argv[0]);  //给出正确输入格式
                 return 1;  
            }  
         }  
  
        FILE *fp = NULL;  // 文件指针  
        if (filename)   // 如果有文件名，打开文件  
    { 
         fp = fopen(filename, "w");  
         if (!fp) 
           { 
               printf("Error: Failed to open file %s\n", filename);  
               return 1;  
           }  
    }  
        
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
          
	verse(input, output);
	printf("后缀表达式为：%s\n", output);
	double result = calculate(output);
	printf("计算结果为：%lf\n", result);
	
	 if (fp)   // 如果打开了文件，将结果写入文件  
        {
            fprintf(fp, "%lf\n", result);  
        }  
        
	free(line);
	printf("-------END-------\n");
	
      }
      if (fp)       // 关闭文件  
      {
        fclose(fp);
      }
       printf("\033[0m");
       return 0;
}

 
