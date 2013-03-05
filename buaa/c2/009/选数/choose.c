/*【问题描述】
已知n（1≤n≤20）个整数x1,x2,……,xn,以及一个整数k（1≤k≤n）。从n个整数中任选k个整数相加，可分别得到一系列的和，
计算其中和为素数的情况共有多少种。例如n=4，k=3时， 4个整数分别为3，7，12，19时，
可得全部的组合与它们的和为：3+7+12=22，3+7+19=29，7+12+19=38，3+12+19=34。此时只有一种情况和为素数：（3+7+19=29）。 
【输入形式】
输入文件为当前目录下的choose.in。
该文件第一行为一个正整数k（1≤k≤n），下面的n行（1≤n≤20）分别为x1,x2,……，xn(1 ≤xi≤5000000)表示这n个数。输入以EOF结束
【输出形式】
输出文件为当前目录下的choose.out。
该文件只有一个整数，代表计算出和为素数的种数。
【输入样例】
3
3
7
12
19
【输出样例】
1
*/
#include<stdio.h>
enum {MAX = 20};
int res[MAX];
int used[MAX] = {0};
int end[MAX] = {0};
int count = 0, primeNum = 0;
void arrange(int k, int m, int n, int num[]);
int sum(int array[], int num[], int m);
int isPrime(int n);
main()
{
	int m, n, i = 0, num[MAX];
	FILE *in, *out;
	in = fopen("choose.in", "r");
	out = fopen("choose.out", "w");
	//in = fopen("choose1.txt", "r");
	//out = fopen("choose2.txt", "w"); 

	fscanf(in, "%d", &m);
	while(fscanf(in, "%d", &num[i]) > 0)
		i++;
	n = i;
	arrange(0, m, n, num);
	fprintf(out, "%d", primeNum);

	fclose(in);
	fclose(out);
}

void arrange(int k, int m, int n, int num[]){
	int i, j;

	if(k == m){
		if(isPrime(sum(res, num, m)))
			primeNum++;
		return;
	}
	for(i = 0;i < n;i++){
		if(!used[i] && !end[i]){
			used[i] = 1;
			res[k] = i + 1;
			arrange(k + 1, m, n, num);
		}
		else
			continue;
		used[i] = 0;
	}
	end[res[k - 1] - 1] = 1;
	for(j = res[k - 1];j < n;j++)
		end[j] = 0;
}

int sum(int array[], int num[], int m){
	int i, sum = 0;

	for(i = 0;i < m;i++)
		sum += num[array[i] - 1];
		//printf("%d%c", array[i], (i == m - 1)?'\n':' ');
	return sum;
}

int isPrime(int n){
	int i;

	for(i = 2;i * i <= n;i++)
		if(n % i == 0)
			return 0;
	return 1;
}