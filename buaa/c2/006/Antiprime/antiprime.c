/*【问题描述】
设n是一个自然数，如果对所有的自然数x（x<n），x的约数个数都少于n的约数个数，则称n是一个Antiprime数。如：1, 2, 4, 6, 12, 24。
试计算不大于n的最大Antiprime数。
【输入形式】
输入文件为当前目录下的antiprime.in。
该文件只有一个整数n，（1≤n≤20 000 000 00）。
【输出形式】
输出文件为当前目录下的antiprime.out。
该文件只包含一个整数，即不大于n的最大Antiprime数。
【输入样例】 
100
【输出样例】
60
*/
#include<stdio.h>
enum {PrimeNum = 11};
int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
int getAntiprime(int n);
int divisors(int n);
main()
{
	int n;
	FILE *in, *out;

	in = fopen("antiprime.in", "r");
	out = fopen("antiprime.out", "w");
	//in = stdin;
	//out = stdout;
	fscanf(in, "%d", &n);
	fprintf(out, "%d", getAntiprime(n));
	fclose(in);
	fclose(out);
}

int getAntiprime(int n){
	int m, i, k, max = 0, num = 0, count;

	for(i = 0, k = 1;(double)k * (double)k <= n;i++)
		k *= prime[i];
	m = k;
	while(k <= n){
		count = divisors(k);
		if(count > max){
			max = count;
			num = k;
		}
		k += m;
	}
	return num;
}

int divisors(int n){
	int i, k = 1, m;

	for(i = 0;i < PrimeNum;i++){
		for(m = 0;n % prime[i] == 0;m++)
			n /= prime[i];
		if(m > 0)
			k *= (m + 1);
	}
	if(k == 1)
		return 0;
	return k;
}
