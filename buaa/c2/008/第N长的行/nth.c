/*������������
Ѱ�Ҹ��������ַ����е�N�����ַ����С�
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�nth.in
��һ�и�������N (1 < N <100000)��
�ڶ��п�ʼ����M (N < M <100000)���ַ������ַ�������󳤶Ȳ�����2000���ַ������ո񣬵��������з�������EOF������
�������ʽ��
����ļ�Ϊ��ǰĿ¼�µ�nth.out

������������е�N���������ȴӴ���С���򣩵��ַ�������ͬ���ȵ��о�����ͬ�ĳ�����ţ����к�����������N�����ַ�����ֻһ��ʱ��
��������������������ֵĵ�N�����С�
���Ȱ����ַ��������м��㣬��\t���ȷ�������һ���ַ�
������������
3
k
abc defg
12345
abc
12 34567
abcde
123
ac
�����������
123
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {MAX = 100001, LEN = 2001};
typedef struct{
	char *str;
	int length;
}LINE;
void getResult(LINE line[], int lineNum, int n, FILE *out);
void insertSort(LINE line[], int lineNum);
main()
{
	FILE *in, *out;
	char buf[LEN];
	LINE line[MAX];
	int i = 0, n, lineNum, temp;
	in = fopen("nth.in", "r");
	out = fopen("nth.out", "w");
	//in = fopen("nth1.txt", "r");
	//out = fopen("nth2.txt", "w");
	//in = stdin;
	//out = stdout;
	
	fscanf(in, "%d", &n);
	while(fgets(buf, LEN + 1, in) != NULL){
		if(i == 0){
			//n = atoi(buf);
			i++;
			continue;
		}
		temp = strlen(buf);
		if(buf[temp - 1] == '\n')
			buf[temp - 1] = '\0';
		line[i - 1].length = strlen(buf);
		line[i - 1].str = (char *)malloc(line[i - 1].length);
		line[i - 1].str = strcpy(line[i - 1].str, buf);
		i++;
	}
	lineNum = i - 1;
	getResult(line, lineNum, n, out);
	fclose(in);
	fclose(out);
}

void getResult(LINE line[], int lineNum, int n, FILE *out){
	int i = 0, k = 0;
	insertSort(line, lineNum);
	while(i < lineNum){
		if(i == 0 || line[i].length < line[i - 1].length){
			k++;
			if(k == n)
				break;
		}
		i++;
	}
	while(i < lineNum - 1 && line[i + 1].length == line[i].length)
		i++;
	if(i == lineNum)
		fprintf(out, "");
	else
		fprintf(out, "%s", line[i].str);
}

void insertSort(LINE line[], int lineNum){
	int i, j;
	LINE temp;

	for(i = 0;i < lineNum - 1;i++){
		temp = line[i + 1];
		for(j = i + 1;j > 0 && temp.length > line[j - 1].length;j--)
			line[j] = line[j - 1];
		line[j] = temp;
	}
}