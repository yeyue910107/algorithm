/*【问题描述】
求从n个自然数(1-n)中选取m个数的所有的排列形式，即求P（n，m）的所有的排列形式，且按升序排列。
【输入形式】
标准输入。输入只有一行，包括两个整数n和m，其中0<n,m<=9，二者之间以一个空白符分隔。
【输出形式】
在标准输出上输出有若干行，每一行都是符合题意的一种排列形式，每个元素间用一个空格分隔，并按升序排列。
【输入样例】
3 2
【输出样例】
1 2
1 3
2 1
2 3
3 1
3 2
【运行时限】
2秒。
*/
#include<stdio.h>
enum {MAX = 10};
int res[MAX];
int count = 0;
int loop;
void arrange(int k, int array[], int m);
void output(int array[], int m);
int factor(int n);
void swap(int *a, int *b);
void circleRight(int array[], int k, int i);
void circleLeft(int array[], int k, int i);
main()
{
	int i, n, m;

	scanf("%d%d", &n, &m);
	loop = factor(n - m);
	for(i = 0;i < n;i++)
		res[i] = i + 1;
	arrange(n, res, m);
}

void arrange(int k, int array[], int m){
	int i;
	if(k == 1){
		if(count % loop == 0)
			output(res, m);
		count++;
		return;
	}
	for(i = 0;i < k;i++){
		swap(&array[0], &array[i]);
		circleRight(array, 1, i);
		arrange(k - 1, &array[1], m);
		circleLeft(array, 1, i);
		swap(&array[i], &array[0]);
	}
}

void circleRight(int array[], int k, int i){
	int temp, j;
	if(i > k){
		temp = array[i];
		for(j = i;j > k;j--)
			array[j] = array[j - 1];
		array[k] = temp;
	}
}

void circleLeft(int array[], int k, int i){
	int temp, j;
	
	if(i > k){
		temp = array[k];
		for(j = k;j < i;j++)
			array[j] = array[j + 1];
		array[i] = temp;
	}
}

void output(int array[], int m){
	int i;

	for(i = 0;i < m;i++)
		printf("%d%c", array[i], (i == m - 1)?'\n':' ');
}

int factor(int n){
	int i, res = 1;

	for(i = 2;i <= n;i++)
		res *= i;
	return res;
}

void swap(int *a, int *b){
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}