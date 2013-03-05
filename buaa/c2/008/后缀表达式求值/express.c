/*������������
��׺���ʽ��һ�ֽ��������������������ļ����﷽ʽ�����磬��������׺���ʽa+b�ں�׺���ʽ��дΪab+��
��׺���ʽ���Ա������ļ���˳�����ʹ�����š����磬(a+b) * (c+d)�ں�׺���ʽ��дΪab+cd+*��
��׺���ʽ����ֵ�����ǣ���������ɨ����ʽ���������������ʱ������ѹ��ջ�У�
�����������ʱ����ջ�е��������������������������㣬����������ѹ��ջ�У��ټ����Ա��ʽ�����ಿ����ֵ��
�������������ĺ�׺���ʽ�Լ������ĸ�ֵ������ʽ��ֵ��
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�express.in��
���ļ��ĵ�һ����һ����׺���ʽ�����ʽ�е���������������ֵ���������������һ��������ĸ��ɣ����5����ĸ����
���ʽ������Ĳ������������������+������*��/�����Ǻ���sin��cos�����������Ϊ�Ƕ�������90 sin,��Ϊsin90��=1����
����������Լ�����֮����һ�������ո�ָ���
���ļ��ĺ�N��ΪN����ͬ�ı�����ֵ��ÿ����ֵ��������ʽ�����б�������-ֵ�ԣ�ÿ����-ֵ�Ե���ʽΪ<>:<>���м��޿ո�
��-ֵ�Լ���һ�������ո���ָ���
�������ʽ��
������д�ڱ�׼����ϡ�
�������ļ��и�ֵ���˳��ÿ����ֵ���Ӧһ��ֵ��ռһ�С��������ֵû��С������ʱ����������ʽ�����
�������ֵ��С������ʱ��������ЧС�����֡��������޷�����ʱ�������error����
������������
abda sin  bfd cos  *  cccc  /
abda:90  bfd:60  cccc:1
abda:30  bfd:60  cccc:1.5
abda:180  bfd:0  cccc:-2.55
�����������
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
