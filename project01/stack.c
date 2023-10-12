
#include"stack.h"

//初始化
Status init_stack(Stack* pStack)
{

    //使用基于动态数组实现的栈，要实现动态分配内存，我们先给栈分配初始容量
    pStack->capacity = 20;    
    pStack->pBase = (StackElem*)malloc(sizeof(StackElem) * pStack->capacity); 
    
    if(pStack->pBase == NULL)
    {
        return ERROR;
    }
        
    pStack->pTop = pStack->pBase;
    pStack->size = 0; 
    return OK;
}

//释放栈元素内存
void stack_free(Stack* pStack)
{
	free(pStack->pBase);
	pStack->pBase = NULL;
	pStack->pTop = NULL;
	pStack->size = 0;
	pStack->capacity = 0;  
}

//清空栈
void stack_clear(Stack* pStack)
{
        pStack->size = 0;
	pStack->pTop = pStack->pBase;
}

//判断是否为空
Bool is_empty(Stack* pStack)
{
	return pStack->pTop == pStack->pBase;
}

//求栈的长度
int stack_length(Stack* pStack)
{
	return pStack->size;
}

//取栈顶元素
Status stack_get_top(Stack *pStack, StackElem *pElem)
{
       if(is_empty(pStack))
       {
            return ERROR;
       }
*pElem = *(pStack->pTop - 1);
    return OK;
}

//入栈
Status stack_push(Stack *pStack, StackElem *pElem)
{

    while (pStack->size >= pStack->capacity)  // 栈已满，需要扩展容量  
    {
        pStack->capacity = pStack->capacity * 2; // 每次将数组的大小乘2， 相比与每次加1,这样效率更高。
        StackElem* pNewBase = (StackElem*)malloc(sizeof(StackElem) * pStack->capacity); // 新分配内存空间  
        if (pNewBase == NULL) 
        {
            return ERROR; // 内存分配失败，返回错误
        }  
        // 将原有数据复制到新的内存空间中  
        for (int i = 0; i < pStack->size; i++) 
        { 
            pNewBase[i] = pStack->pBase[i];
        }  
        free(pStack->pBase); // 释放原有内存空间  
        pStack->pBase = pNewBase; // 更新栈底指针指向新的内存空间起始位
        pStack->pTop = pNewBase + pStack->size;
     }
        *(pStack->pTop) = *pElem;  
        pStack->pTop++;  
        pStack->size++; 
        return OK;  
}

//出栈
Status stack_pop(Stack *pStack, StackElem *pElem)
{
	if(is_empty(pStack))
	{
		return ERROR;
	}
	*pElem = *--pStack->pTop;
	pStack->size--;
	return OK;
}

//遍历栈
Status stack_traverse(Stack *pStack, Status (*visit)())
{
	StackElem* p = pStack->pBase;
	while ( p != pStack->pTop)
	{
		if(visit(p) != OK)
		{
			return ERROR;
		}
		++p;
	}
	return OK;
}


    

//比较符号优先级
int compare(char op)
{
    if(op == '+' || op == '-')
    {
    return 1;
    }
    else if(op == '*' || op == '/')
    {
    return 2;
    }
    else
    {
    return 0;
    }
}

//判断是符号还是数字
int is_num(char k)
{
    if( k >= '0' &&  k <= '9' || k == '.')
    {
        return 1;
    }
    else{ return 0;}
}

//判断是否为计算符
int is_operator(char c) 
{
    return (c == '+' || c == '-' || c == '*' || c == '/');  
}  

//中缀表达式转后缀表达式
void verse(char* input, char* output)  
{
    Stack stack;
    init_stack(&stack);
    int i = 0;
    int j = 0;
    int len = strlen(input);
    while(i < len)
    {       //为了限制用户乱输出，要定义范围，利用ASCLL码来限定元素范围
	    if(input[i] >= 'A' && input[i] <='Z' || input[i] >= 'a' && input[i] <='z' || input[i] >= '0' && input[i] <='9' || input[i] == '.')
	    {
		   output[j++] = input[i++];
		   
		   //保证多位数的独立
		   if(is_num(output[j-1]) != is_num(input[i]))
		   {    output[j++] = ' ' ;}
		       
	    }
	    else if(input[i] == '(')
	    {
		   stack_push(&stack, &input[i++]);//左括号表示要有额外优先级了，但它本身不代表要操作，只需入栈等待右括号到来即可
	    }
	    else if(input[i] == ')')
	    {
		    while(stack.pTop != stack.pBase && *(stack.pTop-1) != '(') //这里是第二个错误，要减1才是真正的首元素
		    {
		        StackElem element;
			    stack_pop(&stack, &element);
                            output[j++] = element; 
                            output[j++] = ' ';
		    }
		        StackElem ha ;
		        stack_pop(&stack, &ha);	     //将用完的左括号出栈   ，这里也可以指向空
		        i++;    //  第一个错误，导致段错误的祸首，因为无限循环了 卡了我这么久：2023.10.8. 17:00 到2023.10.9. 2:12  好好好🦸
           }
           else //剩下的就是符号了，利用compare函数实现优先级
           {  
              while(!is_empty(&stack) && compare(input[i]) - compare(*(stack.pTop-1))<= 0 )
	      {    
		        if(*stack.pTop == '(')   //这个情况是为了防止使用括号时出错，因为括号无法与计算符比较
			{
				break;
			}
			else
			{
		        StackElem element2;
		        stack_pop(&stack, &element2);
			output[j++] = element2;  //优先弹出等级更高的操作符
			output[j++] = ' ';
			}
	      }
                stack_push(&stack, &input[i++]);    //不管怎样最后都要入栈的
           }
    
         }
         
            //最后将栈中剩余的符号依次弹出 
while(!is_empty(&stack))
{
	StackElem element3;
	stack_pop(&stack, &element3);
        output[j++] = element3;
        output[j++] = ' ';
}
           //最后要给output的最后输入‘\0’来表示终止
output[j] = '\0';
stack_free(&stack);
}


//去除空格
void removet(char *str) 
{  
    char newstr[100]; // 创建一个新字符串来存储
    int i, j;  
  
    // 复制非空格字符到新字符串中  
    for (i = 0, j = 0; i < strlen(str); i++) 
    { 
        if (str[i] != ' ') 
        {
            newstr[j] = str[i];  
            j++;  
        }  
    }  
    newstr[j] = '\0';
  
    // 将新字符串复制回原始字符串  
    strcpy(str, newstr);  
}  



//判断是否为字母运算，如果是的话那将无法运算
int is_abc(char* output)
{
    int i = 0;
    while(output[i] != '\0')
    {
        if (output[i] >= 'A' && output[i] <='Z' || output[i] >= 'a' && output[i] <='z')
             {
                 return 1;
             }
             i++;
    }
    return 0;
}   

//计算
double calculate(char* output)
{
    if(is_abc(output))
        {
            printf("多项式无法计算\n");
            return 0;
        }
        
        char* token;
        double arr[100];
        int i = 0;
        token = strtok(output, " ");
    
    while (token != NULL) 
    {
        if (is_num(*token)) 
        {
            double num = atof(token);   // 将字符串转化为浮点数并存在数组里
            arr[i] = num;
            i++;
        }
        else if(is_operator(*token))
        {   
            switch (*token) 
            {
                case '+': arr[i-2] = arr[i-2] + arr[i-1] ; break;  
                case '-': arr[i-2] = arr[i-2] - arr[i-1] ; break;  
                case '*': arr[i-2] = arr[i-2] * arr[i-1] ; break;  
                case '/': if (arr[i-1] == 0) { printf("除数不能为0!\n"); exit(1); } // 检查0是否为分母
                          else arr[i-2] = arr[i-2] / arr[i-1] ; break;        
            }
            i--;
         }
         else
         {
             printf("ERROR\n");
         }
         token = strtok(NULL, " ");
     }   
     return arr[0];
}        
       
              	      
