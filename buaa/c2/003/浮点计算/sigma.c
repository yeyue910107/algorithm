/*【问题描述】
计算 k *∑(x^i), －m ≤ i ≤ n，精确到小数点后14位（最后要求四舍五入）。
【输入形式】
从文件sigma.in中顺序读入4个由空格分隔的正整数k、x、m、n。(1≤  k、x、m、n ≤ 100)。
【输出形式】
将结果写到标准输出，其中小数占14位，不足部分补零，最后输出一个回车。(输入数据保证输出结果小于2^53。)
【输入样例】
1 10 5 5
【输出样例】
111111.11111000000000
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {MAX = 500};
void multiply(char *s, int n);
void mul(char *s, int n, char *tempStr, char* str);
void add(char *s, char *t);
void reverseStr(char* s);
main()
{
	FILE *in, *out;
	int k, x, m, n, i, j = 0, x0, x1;
	double rs = 0.0, temp = 1.0;
	char *s, *kStr, *xStr, *tempStr, *str, *str0;
	//in = fopen("sigma.in", "r");
	in = stdin;
	out = stdout;

	s = (char *)malloc(MAX + 1);
	tempStr = (char *)malloc(MAX + 1);
	str = (char *)malloc(MAX + 1);
	str0 = (char *)malloc(MAX + 1);
	kStr = (char *)malloc(10);
	xStr = (char *)malloc(10);
	s[0] = '0';
	s[1] = '\0';
	
	fscanf(in, "%s%s%d%d", kStr, xStr, &m, &n);
	k = atoi(kStr);
	x = atoi(xStr);
	for(i = -m; i <= n;i++){
		if(i <= 0){
			temp = 1.0;
			for(j = 0;j > i;j--)
				temp /= x;
			rs += temp;
		}
		else{
			x0 = x;
 			for(;j < i;j++){
				if(j == 0){
					str0[0] = '1';
					str0[1] = '\0';
				}
				else{
					str0 = strcpy(str0, tempStr);
				}
				mul(str0, x0, tempStr, str);
				add(s, tempStr);
			}
		}
	}

	rs = rs * k;
	mul(s, k, tempStr, str);
	s = strcpy(s, tempStr);
	x1 = (int)rs;
	i = 0;
	while(x1 > 0){
		tempStr[i] = (char)(x1 % 10 + 48);
		x1 /= 10;
		i++;
	}
	tempStr[i] = '\0';
	reverseStr(tempStr);
	add(tempStr, s);
	s = strcpy(s, tempStr);
	rs = rs - (int)rs + (int)(s[strlen(s) - 1]) - 48;
	for(i = 0;i < strlen(s) - 1;i++)
		fputc(s[i], out);
	fprintf(out, "%.14f\n", rs);
	fclose(in);
	fclose(out);
}

void multiply(char *s, int n){
	int i , mod = 0, m;
	
	reverseStr(s);
    for(i = 0;s[i] != '\0';i++){
        m = (int)((s[i] - 48) * n + mod);
        s[i] = (char)(m % 10 + 48);
        mod = m / 10;
    }
    if(mod != 0){
        s[i] = (char)(mod + 48);
        s[i + 1] = '\0';
    }
	else
		s[i] = '\0';
	reverseStr(s);
}

void mul(char *s, int n, char *tempStr, char *str){
	int count, strLen, k, n0;
	count = 0;
	while(n > 0){
		str = strcpy(str, s);
		n0 = n % 10;
		multiply(str, n0);
		n /= 10;
		strLen = strlen(str);
		if(count > 0){
			for(k = 0;k < count;k++){
				str[strLen] = '0';
				str[++strLen] = '\0';
			}
		}
		if(count == 0){
			tempStr = strcpy(tempStr, str);
		}
		else
			add(tempStr, str);
		count++;
	}
}

void add(char *s, char *t){
	int i, sLen = strlen(s), tLen = strlen(t), m, mod = 0;
	
	reverseStr(s);
	reverseStr(t);
	for(i = sLen;i < tLen;i++)
		s[i] = '0';
	s[i] = '\0';
	sLen = tLen;
	for(i = 0;s[i] != '\0';i++){
		m = (int)((s[i] - 48) + (t[i] - 48) + mod);
        s[i] = (char)(m % 10 + 48);
        mod = m / 10;		
	}
	if(mod != 0){
        s[i] = (char)(mod + 48);
        s[i + 1]='\0';
    }
	reverseStr(s);
	reverseStr(t);
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