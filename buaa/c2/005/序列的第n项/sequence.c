/*【问题描述】
序列a(1)，a(2)，…，a(n)以及正整数k。对于i>1，a(i)是满足下面2个性质的最小正整数：
(1) a(i) > a(i-1)；
(2) a(i) 的各位数字的和与k×a(i-1)的各位数字的和相等。
例如，a(1)=1,k=2,n=6时，该序列的前6个元素是1，2，4，8，16，23。
现给定a(1),k,n的值，计算该序列的第n项a(n)的值。
【输入形式】
输入文件为当前目录下的sequence.in。
文件只有一行，包含3个整数a(1),k,n (0<a(1)<1000;0<k,n<300000)。
【输出形式】
输出文件为当前目录下的sequence.out。
该输出文件只有一个整数，为序列的第n项a(n)，以换行符结束。
【输入样例】
1 2 6
【输出样例】
23
【运行时限】
1秒
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {LEN = 300000, MAX = 20};
void getNext(char *array, char *temp, int k);
int getSum(char *array);
int getNextSum(char *array, int n);
void multiply(char *s, int n);
void reverseStr(char* s);
main()
{
	int i, k, n;
	char *array, *temp;
	FILE *in, *out;
	//in = fopen("sequence.in", "r");
	//out = fopen("sequence.out", "w");
	in = fopen("in.txt", "r");
	out = fopen("out.txt", "w");
	//in = stdin;
	//out = stdout;
	
	array = (char *)malloc(LEN);
	temp = (char *)malloc(LEN);
	fscanf(in, "%s%d%d", array, &k, &n);
	for(i = 1;i < n;i++)
		getNext(array, temp, k);
	fprintf(out, "%s\n", array);
	fclose(in);
	fclose(out);
}
//获得下一个数
void getNext(char *array, char *temp, int k){
	int i, sum, nextSum, num;

	temp = strcpy(temp, array);
	sum = getSum(array);
	nextSum = getNextSum(temp, k);
	reverseStr(array);
	if(nextSum > sum){
		num = nextSum - sum;
		i = 0;
		while(array[i] != '\0'){
			 if(array[i] != '9')
				 break;
			 i++;
		}
		if(array[i] == '\0'){
			array[i] = '0';
			array[i + 1] = '\0';
		}
		while(num > 0){
			if(array[i] == '\0'){
				array[i] = '0';
				array[i + 1] = '\0';
			}
			else if(array[i] + num > '9'){
				num -= '9' - array[i];
				array[i++] = '9';
				//array[++i] = '0';
				//array[i + 1] = '\0';
			}
			else{
				array[i] += num;
				break;
			}
		}
	}
	else{
		num = sum - nextSum;
		i = 0;
		while(array[i] != '\0'){
			if(i == 0){
				sum -= (int)array[i] - 48;
				array[i++] = '0';
				continue;
			}
			if(array[i] == '9'){
				sum -= (int)array[i] - 48;
				array[i++] = '0';
			}
			else{
				if(sum + 1 > nextSum){
					sum -= (int)array[i] - 48;
					array[i++] = '0';
				}
				else{
					array[i]++;
					sum++;
					break;
				}
			}
		}
		if(array[i] == '\0'){
			array[i] = '1';
			array[i + 1] = '\0';
			sum++;
		}
		i = 0;
		while(array[i] != '\0' && sum < nextSum){
			if(sum + 9 <= nextSum){
				array[i++] = '9';
				sum += 9;
			}
			else{
				array[i] = (char)nextSum - sum + 48;
				break;
			}
		}
	}
	reverseStr(array);
}
//计算各位数字和
int getSum(char *array){
	int i = 0, sum = 0;

	while(array[i] != '\0'){
		sum += (int)array[i] - 48;
		i++;
	}
	return sum;
}

//计算乘积结果各位数字和
int getNextSum(char *array, int n){
	int sum = 0, nLen = 0, i = 0, k = -1, arrayLen = strlen(array), temp = 0, flag, mod = 0;
	char *num[MAX];
	while(1){
		flag = 0;
		if(n > 0){
			num[++k] = (char *)malloc(arrayLen + 1);
			num[k] = strcpy(num[k], array);
			multiply(num[k], n % 10);
		}
		for(i = 0, temp = 0;i <= k;i++){
			if(*(num[i]) != '\0'){
				temp += (int)*(num[i]) - 48 + mod;
				num[i]++;
				flag = 1;mod = 0;
			}
		}
		if(flag == 0){
			sum += mod;
			break;
		}
		if(temp >= 10){
			sum += temp % 10;
			mod = temp /= 10;
		}
		else
			sum += temp;
		n /= 10;
		//k++;
	}
	//	mul(array, n, tempStr, str);
	//	sum = getSum(tempStr);
	return sum;
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
	
}
//字符串逆序
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

/*
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {LEN = 10000, MAX = 20};
void getNext(char *array, char *temp, int k, char *tempStr, char *str);
int getSum(char *array);
int getNextSum(char *array, int n, char *tempStr, char *str);
void multiply(char *s, int n);
void reverseStr(char* s);
void mul(char *s, int n, char *tempStr, char *str);
void add(char *s, char *t);
main()
{
	int i, k, n;
	char *array, *temp, *tempStr, *str;
	FILE *in, *out;
	//in = fopen("sequence.in", "r");
	//out = fopen("sequence.out", "w");
	in = stdin;
	out = stdout;
	
	array = (char *)malloc(LEN);
	temp = (char *)malloc(LEN);
	tempStr = (char *)malloc(LEN);
	str = (char *)malloc(LEN);
	fscanf(in, "%s%d%d", array, &k, &n);
	for(i = 1;i < n;i++)
		getNext(array, temp, k, tempStr, str);
	fprintf(out, "%s\n", array);
	fclose(in);
	fclose(out);
}
//获得下一个数
void getNext(char *array, char *temp, int k, char *tempStr, char *str){
	int i, sum, nextSum, num;

	temp = strcpy(temp, array);
	sum = getSum(array);
	nextSum = getNextSum(temp, k, tempStr, str);
	reverseStr(array);
	if(nextSum > sum){
		num = nextSum - sum;
		i = 0;
		while(array[i] != '\0'){
			 if(array[i] != '9')
				 break;
			 i++;
		}
		if(array[i] == '\0'){
			array[i] = '0';
			array[i + 1] = '\0';
		}
		while(num > 0){
			if(array[i] == '\0'){
				array[i] = '0';
				array[i + 1] = '\0';
			}
			else if(array[i] + num > '9'){
				num -= '9' - array[i];
				array[i++] = '9';
				//array[++i] = '0';
				//array[i + 1] = '\0';
			}
			else{
				array[i] += num;
				break;
			}
		}
	}
	else{
		num = sum - nextSum;
		i = 0;
		while(array[i] != '\0'){
			if(i == 0){
				sum -= (int)array[i] - 48;
				array[i++] = '0';
				continue;
			}
			if(array[i] == '9'){
				sum -= (int)array[i] - 48;
				array[i++] = '0';
			}
			else{
				if(sum + 1 > nextSum){
					sum -= (int)array[i] - 48;
					array[i++] = '0';
				}
				else{
					array[i]++;
					sum++;
					break;
				}
			}
		}
		if(array[i] == '\0'){
			array[i] = '1';
			array[i + 1] = '\0';
			sum++;
		}
		i = 0;
		while(array[i] != '\0' && sum < nextSum){
			if(sum + 9 <= nextSum){
				array[i++] = '9';
				sum += 9;
			}
			else{
				array[i] = (char)nextSum - sum + 48;
				break;
			}
		}
	}
	reverseStr(array);
}
//计算各位数字和
int getSum(char *array){
	int i = 0, sum = 0;

	while(array[i] != '\0'){
		sum += (int)array[i] - 48;
		i++;
	}
	return sum;
}

//计算乘积结果各位数字和
int getNextSum(char *array, int n, char *tempStr, char *str){
	int sum;

	mul(array, n, tempStr, str);
	sum = getSum(tempStr);
	return sum;
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
	
}
//字符串逆序
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
}*/