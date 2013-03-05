/*【问题描述】
后缀表达式是一种将运算符放在运算对象后面的计算表达方式。例如，正常的中缀表达式a+b在后缀表达式中写为ab+。
后缀表达式可以表达任意的计算顺序而不使用括号。例如，(a+b) * (c+d)在后缀表达式中写为ab+cd+*。
后缀表达式的求值过程是，从左至右扫描表达式，当遇到运算对象时，将其压入栈中；
当遇到运算符时，从栈中弹出所需数量的运算对象进行运算，并将计算结果压入栈中，再继续对表达式的其余部分求值。
给出包含变量的后缀表达式以及变量的赋值表，求表达式的值。
【输入形式】
输入文件为当前目录下的express.in。
该文件的第一行是一个后缀表达式。表达式中的运算对象可以是数值或变量。变量名由一个或多个字母组成（最多5个字母）。
表达式中允许的操作符包括四则运算符+、－、*、/和三角函数sin和cos（运算对象视为角度数，如90 sin,即为sin90°=1）。
各运算对象以及变量之间以一个或多个空格分隔。
该文件的后N行为N个不同的变量赋值表，每个赋值表包含表达式中所有变量的名-值对，每个名-值对的形式为<>:<>，中间无空格。
名-值对间由一个或多个空格符分隔。
【输出形式】
输出结果写在标准输出上。
按输入文件中赋值表的顺序，每个赋值表对应一个值，占一行。当输出的值没有小数部分时，按整数格式输出，
当输出的值有小数部分时，保留有效小数部分。当计算无法进行时，输出”error”。
【输入样例】
abda sin  bfd cos  *  cccc  /
abda:90  bfd:60  cccc:1
abda:30  bfd:60  cccc:1.5
abda:180  bfd:0  cccc:-2.55
【输出样例】
1.5
1.75
-2.55
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#define PI 3.141592653
enum {LEN = 10, LINE = 100, MAX = 100};
typedef struct{
	char name[LEN];
	double value;
}VAR;
void setVar(VAR var[], char *buf, int n);
void getResult(char *express, VAR var[], FILE *out);
int isNum(char *str);
int varNum = 0;
int main()
{
	FILE *in, *out;
	char buf[LINE], express[LINE], temp[LINE];
	int i = 0;
	VAR var[MAX];
	//in = fopen("express.in", "r");
	//out = fopen("express.out", "w");
	in = fopen("express1.txt", "r");
	out = fopen("express2.txt", "w");

	while(fgets(buf, LINE + 1, in) != NULL){
		if(i == 0)
			strcpy(express, buf);
		else{
			strcpy(temp, express);
			setVar(var, buf, i);
			getResult(temp, var, out);
		}
		i++;
	}
	fclose(in);
	fclose(out);
}

void setVar(VAR var[], char *buf, int n){
	int i = 0;
	char *token;
	
	token = strtok(buf, " :\n");
	while(token){
		//if(token == NULL)
			//break;
		//set variables' names for just once
		if(i % 2 == 0 && n == 1){
			strcpy(var[i / 2].name, token);
			varNum++;
		}
		//set variables' values
		else
			var[i / 2].value = atof(token);
		i++;
		token = strtok(NULL, " :\n");
	}	
}

void getResult(char *express, VAR var[], FILE *out){
	double stack[MAX];
	int top = -1, i;
	char *token;

	token = strtok(express, " \n");
	while(token){
		if(token == NULL)
			break;
		if(strcmp(token, "sin") == 0){
			stack[top] = sin(stack[top] / 180 * PI);
		}
		else if(strcmp(token, "cos") == 0){
			stack[top] = cos(stack[top] / 180 * PI);
		}
		else if(strcmp(token, "+") == 0){
			if(top <= 0){
				fprintf(out, "error\n");
				return;
			}
			stack[top - 1] += stack[top--];
		}
		else if(strcmp(token, "-") == 0){
			if(top <= 0){
				fprintf(out, "error\n");
				return;
			}
			stack[top - 1] -= stack[top--];
		}
		else if(strcmp(token, "*") == 0){
			if(top <= 0){
				fprintf(out, "error\n");
				return;
			}
			stack[top - 1] *= stack[top--];
		}
		else if(strcmp(token, "/") == 0){
			if(top <= 0){
				fprintf(out, "error\n");
				return;
			}
			if(stack[top] == 0){
				fprintf(out, "error\n");
				return;
			}
			stack[top - 1] /= stack[top--];
		}
		else if(isNum(token))
			stack[++top] = atof(token);
		else{
			for(i = 0;i < varNum;i++)
				if(strcmp(token, var[i].name) == 0){
					stack[++top] = var[i].value;
					break;
				}
		}
		token = strtok(NULL, " \n");
	}
	if(top == 0)
		fprintf(out, "%g\n", stack[top]);
	else
		fprintf(out, "error\n");
}

int isNum(char *str){
	int i;
	for(i = 0;str[i] != '\0' && (str[0] == '-' || str[i] == '.' || isdigit(str[i]));i++)
		;
	return (str[i] == '\0')?1:0;
}
