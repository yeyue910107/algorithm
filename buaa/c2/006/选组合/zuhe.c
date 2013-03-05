/*【问题描述】
求n个自然数(1-n)的所有m-组合，即C（n，m）的所有不可重复的组合形式。
【输入形式】
标准输入。输入只有一行，包括两个整数n和m，其中0<n<=20，0<m<=9，二者之间以一个空白符分隔。
输入内容可以保证在算法得当情况下，规定时间内可以完成。
【输出形式】
在标准输出上输出有若干行，每一行都是符合题意的一种排列形式，每个元素间用一个空格分隔，并按升序排列。
【输入样例】
3 2
【输出样例】
1 2 
1 3
2 3
*/
#include<stdio.h>
enum {MAX = 20};
int res[MAX];
int used[MAX] = {0};
int end[MAX] = {0};
int count = 0;
void arrange(int k, int m, int n);
void output(int array[], int m);
main()
{
	int n, m;

	scanf("%d%d", &n, &m);
	arrange(0, m, n);
}

void arrange(int k, int m, int n){
	int i, j;

	if(k == m){
		output(res, m);
		return;
	}
	for(i = 0;i < n;i++){
		if(!used[i] && !end[i]){
			used[i] = 1;
			res[k] = i + 1;
			arrange(k + 1, m, n);
		}
		else
			continue;
		used[i] = 0;
	}
	end[res[k - 1] - 1] = 1;
	for(j = res[k - 1];j < n;j++)
		end[j] = 0;
}

void output(int array[], int m){
	int i;

	for(i = 0;i < m;i++)
		printf("%d%c", array[i], (i == m - 1)?'\n':' ');
}
