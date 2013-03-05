/*【问题描述】
将由数字和四则运算符组成的后缀表达式变换为中缀表达式。输入的后缀表达式包含的运算符不超过15个。
要求转换后的中缀表达式中不应出现不必要的括号。例如，整个表达式两端的括号要省略，不影响原计算顺序的括号要省略。
【输入形式】
程序从标准输入上读入一行字符串，是一个合法的后缀表达式，数字和运算符之间由空格分隔。其中的数字可以是整数，
也可以是带有小数部分的浮点数。
【输出形式】
向标准输出打印结果。
输出只有一行，是转换后的中缀表达式，并且
1. 各分量（包括括号）紧密输出，不使用空格进行分隔；
2. 在转换前后各运算数的出现顺序不变；
3. 浮点数保留输入时的小数位数。
【输入样例】
4  7  -  2.1  5  +  *  7.1  9  -  /
【输出样例】
(4-7)*(2.1+5)/(7.1-9)
【样例说明】
输入的后缀表达式中含有整数、浮点数，以及四则运算符。要求将其转换成相应的中缀表达式，并且不包含多余的括号，
各运算数的出现顺序不变。
【运行时限】
1秒
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
enum {MAX = 100};
int compare1Op2(char op1, char op2);
int compare2Op2(char op1, char op2);
int compareOp3(char op1, char op2, char op3);
void addBrackets(char *s);
int isHasOp(char *s);
main()
{
	char *stack[MAX], c = -1, buf[MAX], stackOp[MAX];
	int j, top, topOp = -1;
	
	c = getchar();
	for(top = 0;c != '\n';top++){
		if(c == ' '){
			c = getchar();
			top--;
			continue;
		}
		j = 0;
		while(c != ' '){
			buf[j++] = c;
			c = getchar();
			if(c == '\n')
				break;
		}
		buf[j] = '\0';
		stack[top] = (char *)malloc(strlen(buf)+1);
		strcpy(stack[top], buf);
		if(!isdigit(stack[top][0])){
			stackOp[++topOp] = stack[top][0];
			if(top >= 2){
					if(isHasOp(stack[top - 2]) && !isHasOp(stack[top - 1])){
						if(compare1Op2(stackOp[0], stackOp[1]) == 1){
							addBrackets(stack[top - 2]);
							}
							stackOp[topOp - 1] = stackOp[topOp];
							topOp--;
							stack[top - 2] = strcat(stack[top - 2], stack[top]);
							stack[top - 2] = strcat(stack[top - 2], stack[top - 1]);
							top -= 2;
						}
						else if(isHasOp(stack[top - 1]) && !isHasOp(stack[top - 2])){
							if(compare2Op2(stackOp[0], stackOp[1]) == 1){
								addBrackets(stack[top - 1]);
							}
							stackOp[topOp - 1] = stackOp[topOp];
							topOp--;
							stack[top - 2] = strcat(stack[top - 2], stack[top]);
							stack[top - 2] = strcat(stack[top - 2], stack[top - 1]);
							top -= 2;
						}
					
						else if(!isHasOp(stack[top - 2]) && !isHasOp(stack[top - 1])){
							stack[top - 2] = strcat(stack[top - 2], stack[top]);
							stack[top - 2] = strcat(stack[top - 2], stack[top - 1]);
							top -= 2;
						}
				else if(isHasOp(stack[top - 2]) && isHasOp(stack[top - 1])){
					switch(compareOp3(stackOp[0], stackOp[1], stackOp[2])){
					case -1:
						addBrackets(stack[top - 2]);
						break;
					case 0:
						break;
					case 1:
						addBrackets(stack[top - 1]);
						break;
					case 2:
						addBrackets(stack[top - 2]);
						addBrackets(stack[top - 1]);
						break;
					default:
						break;
					}
					stackOp[topOp - 2] = stackOp[topOp];
					topOp -= 2;
				stack[top - 2] = strcat(stack[top - 2], stack[top]);
				stack[top - 2] = strcat(stack[top - 2], stack[top - 1]);
				top -= 2;
			}
		}
		}
		if(c == '\n')
			break;
		c = getchar();
	}
	puts(stack[0]);

}

int compare1Op2(char op1, char op2){
	if(op2 == '+')
		return 0;
	else if(op2 == '-')
		return 0;
	else if(op1 == '*' || op1 == '/')
		return 0;
	else
		return 1;
}

int compare2Op2(char op1, char op2){
	if(op2 == '+')
		return 0;
	else if(op2 == '-')
		return 1;
	else if(op2 == '*'){
		if(op1 == '+' || op1 == '-' || op1 == '/')
			return 1;
		else
			return 0;
	}
		
	else if(op2 == '/')
		return 1;
	else
		return 0;
}

int compareOp3(char op1, char op2, char op3){
	if(op3 == '+')
		return 0;
	else if(op3 == '-')
		return 1;
	else if(op3 == '*'){
		if(op1 == '+' || op1 == '-'){
			if(op2 == '+' || op2 == '-')
				return 2;
			else
				return -1;
		}
		else if(op1 == '*' || op1 == '/'){
			if(op2 == '+' || op2 == '-')
				return 1;
			else
				return 0;
		}
	}
	else if(op3 == '/'){
		if(op1 == '+' || op1 == '-'){
			if(op2 == '+' || op2 == '-' || op2 == '*')
				return 2;
			else
				return -1;
		}
		else if(op1 == '*' || op1 == '/'){
			if(op2 == '+' || op2 == '-' || op2 == '*')
				return 1;
			else
				return 0;
		}
	}
	return 0;
}

void addBrackets(char *s){
	int i, length = strlen(s);
	
	s[length + 1] = ')';
	s[length + 2] = '\0';
	for(i = length;i > 0;i--)
		s[i] = s[i - 1];
	s[0] = '(';
}

int isHasOp(char *s){
	int i, length = strlen(s);

	for(i = 0;i < length;i++)
		if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')
			return 1;
	return 0;
}