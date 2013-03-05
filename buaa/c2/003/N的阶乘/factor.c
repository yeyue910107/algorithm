/*【问题描述】
精确计算Ｎ的阶乘。其中，N可能是小于200的任意正整数。
【输入形式】
输入文件为当前目录下的factor.in。
该文件只包含一个正整数，表示需要求该正整数的阶乘。
【输出形式】
输出文件为当前目录下的factor.out。
该文件中的输出为所求的阶乘。注意：每行最多打印50个数字。
【输入样例】
57
【输出样例】
40526919504877216755680601905432322134980384796226
602145184481280000000000000
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {MAX = 1000};
void factor(char *s, int n, char *temp, char *t);
void multiply(char *s, int n, char *temp);
void add(char *s, char *t);
void reverseStr(char* s);
main()
{
	FILE *in, *out;
	int n, i, length;
	char s[MAX];
	char *temp, *t;
	
	//in = fopen("factor.in", "r");
	//out = fopen("factor.out", "w");
	in = stdin;
	out = stdout;

	s[0] = '1';
	s[1] = '\0';
	fscanf(in, "%d", &n);
	temp = (char *)malloc(1000);
	t = (char *)malloc(1000);
	for(i = 2;i <= n;i++)
		factor(s, i, temp, t);
	//fprintf(out, "%s", s);
	//fputc('\n', out);
	length = strlen(s);
	for(i = 0;i < length;i++){
		fputc(s[i], out);
		if((i+1) % 50 == 0)
			fputc('\n', out);
	}
	fputc('\n', out);
	free(temp);
	free(t);
	fclose(in);
	fclose(out);
}

void factor(char *s, int n, char *temp, char *t){
	int i, k, mod, length = strlen(s), tempLen;
	

	
	i = 0;
	t = strcpy(t, s);
	reverseStr(t);
	while(n > 0){
		mod = n % 10;
		multiply(t, mod, temp);
		tempLen = strlen(temp);
		if(i > 0){
			reverseStr(temp);
		for(k = 0;k < i;k++){
			temp[tempLen] = '0';
			temp[++tempLen] = '\0';
		}
		reverseStr(temp);
		}
		if(i == 0)
			s = strcpy(s, temp);
		else
			add(s, temp);
		n /= 10;
		i++;
	}
	reverseStr(s);
}

void multiply(char *s, int n, char *temp){
	int i , mod = 0, m;

    for(i = 0;i < 500 && s[i] != '\0';i++){
        m = (int)((s[i] - 48) * n + mod);
        temp[i] = (char)(m % 10 + 48);
        mod = m / 10;
    }
    if(mod != 0){
        temp[i] = (char)(mod + 48);
        temp[i + 1] = '\0';
    }
	else
		temp[i] = '\0';
}

void add(char *s, char *t){
	int i, sLen = strlen(s), tLen = strlen(t), m, mod = 0;

	for(i = sLen;i < tLen;i++)
		s[i] = '0';
	s[i] = '\0';
	sLen = tLen;
	for(i = 0;i < 500 && s[i] != '\0';i++){
		m = (int)((s[i] - 48) + (t[i] - 48) + mod);
        s[i] = (char)(m % 10 + 48);
        mod = m / 10;		
	}
	if(mod != 0){
        s[i] = (char)(mod + 48);
        s[i + 1]='\0';
    }
	
}

void reverseStr(char* s)
{
	int i, length = strlen(s);
	char temp;

	for(i = 0;i < length / 2;i++){
		temp = s[i];
		s[i] = s[length - i - 1];
		s[length - i - 1] = temp;
	}
}