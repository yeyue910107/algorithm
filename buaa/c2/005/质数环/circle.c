/*【问题描述】
设计一个程序，使其将由1到N（N为偶数，且N <= 20）的N个正整数分别放置在由N个节点组成的环的各个节点上，
其中1必须放在第一个节点上，并使任意两个相邻的节点上的数字之和为质数。
下图是当N为6时的一个例。当N为6时的输出样例如下：
1 4 3 2 5 6
1 6 5 2 3 4
【输入形式】
从标准输入上读入一个偶数。 
【输出形式】
在标准输出上打印所有符合要求的排列方法。
输出有若干行，每一行都是符合题意且不重复的一种排列方法，所有数字从1所在位置开始，按顺时针方向依次输出，
各个数字之间以一个空格分隔。
注意：输出按升序排列，具体格式见输出样例。
只要输出序列不同就认为是不同排列。如N=6时，1 4 3 2 5 6和1 6 5 2 3 4两种排列实际上是对称的，但此时认为是两种排列。
【输入样例】
6
【输出样例】
1 4 3 2 5 6
1 6 5 2 3 4
【样例说明】
输入整数6，要求将1、2、……、6排成环且相邻两数之和为素数。
合法的排列方法共有2种，由运行结果可见，第2位上可能的数字只有4和6。且先输出4开头的所有合法排列，
再输出6开头的所有合法排列，余下部分同样遵循此原则。
【运行时限】
20秒。
*/
#include<stdio.h>
enum {MAX = 20};
void primeCircle(int num[], int k, int n);
void printCircle(int num[], int n);
int isPrime(int n);
int used[MAX] = {0};
main()
{
	int n, num[MAX] = {0};

	num[0] = 1;
	used[1] = 1;
	scanf("%d", &n);
	primeCircle(num, 1, n);
}

void primeCircle(int num[], int k, int n){
	int i;

	if(k == n){
		if(isPrime(num[k - 1] + 1))
			printCircle(num, n);
		return;
	}
	for(i = 2;i <= n;i++){
		if(!used[i] && isPrime(num[k - 1] + i)){
			num[k] = i;
			used[i] = 1;
			primeCircle(num, k + 1, n);
			used[i] = 0;
		}
	}
}

void printCircle(int num[], int n){
	int i;
	
	for(i = 0;i < n;i++)
		printf("%d%c", num[i], (i == n - 1)?'\n':' ');
}

int isPrime(int n){
	int i;

	for(i = 2;i <= n / 2;i++)
		if(n % i == 0)
			return 0;
	return 1;
}