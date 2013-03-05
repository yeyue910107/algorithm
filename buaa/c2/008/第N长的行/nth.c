/*【问题描述】
寻找给定多行字符串中第N长的字符串行。
【输入形式】
输入文件为当前目录下的nth.in
第一行给定整数N (1 < N <100000)。
第二行开始包含M (N < M <100000)行字符串，字符串的最大长度不超过2000个字符（含空格，但不含换行符），以EOF结束。
【输出形式】
输出文件为当前目录下的nth.out

输出各输入行中第N长（按长度从大向小排序）的字符串。相同长度的行具有相同的长度序号，序列号连续。当第N长的字符串不只一个时，
输出在输入序列中最后出现的第N长的行。
长度按照字符个数进行计算，‘\t’等符号算作一个字符
【输入样例】
3
k
abc defg
12345
abc
12 34567
abcde
123
ac
【输出样例】
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