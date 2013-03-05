/*【问题描述】
写一个程序，对于给定的一个自然数N（1≤N≤4999），和M个互不相同的十进制数字X1， X2，…,XM (M≥1)， 找出N的一个最小的正倍数，
使得该倍数中仅包含数字X1，X2，…，XM。
【输入形式】
输入文件为当前目录下的multiple.in，输入文件第一行为整数N，接下来M行分别列出数字 X1,X2..XM ，以EOF结束。
【输出形式】
输入文件为当前目录下的multiple.out，输出文件输出为这个倍数，如果无解输出0。在所有的测试数据中答案都不会超过500位。
【输入样例】
22
7
0
1
【输出样例】
110
【运行时限】
1秒
*/
#include<stdio.h>
enum {LEN = 10000, MAX = 10};
int digit_num;
typedef struct node{
	int num, mod;
	int parent;
}NODE;
void output(FILE* out, NODE queue[], int n);
void insertSort(int array[], int n);
main()
{	
	FILE *in, *out;
	NODE queue[LEN];
	int i = 0, j, k, p, n, rear = 0, digit[MAX];
	in = fopen("multiple.in", "r");
	out = fopen("multiple.out", "w");
	//in = stdin;
	//out = stdout;
	fscanf(in, "%d", &n);
	while(fscanf(in, "%d", &digit[i]) > 0){
		i++;
	}
	digit_num = i;
	insertSort(digit, digit_num);
	
	queue[0].num = 0;
	queue[0].mod = 0;
	queue[0].parent = 0;
	for(k = 1;k <= digit_num;k++){
		queue[k].num = digit[k - 1];
		queue[k].mod = digit[k - 1] % n;
		queue[k].parent = 0;
		rear++;
	}
	for(i = 1;i <= rear;i++){
		if(i == 1 && queue[i].num == 0)
			continue;
		j = 0;
		while(j < digit_num){
			if((queue[i].mod * 10 + digit[j]) % n == 0){
				queue[k].num = digit[j];
				queue[k].parent = i;
				output(out, queue, k);
				fprintf(out, "\n");
				return 0;
			}
			else{
				for(p = 0;p <= rear && (queue[i].mod * 10 + digit[j]) % n != queue[p].mod;p++)
					;
				if(p == rear + 1){
					queue[k].num = digit[j];
					queue[k].parent = i;
					queue[k].mod = (queue[i].mod * 10 + digit[j]) % n;
					k++;
					rear++;
				}
				j++;
			}
		}
	}
	fprintf(out, "0\n");
	fclose(in);
	fclose(out);
	return 0;
}

void output(FILE* out, NODE queue[], int n){
	if(n <= digit_num && n > 0){
		fprintf(out, "%d", queue[n].num);
	}
	else{
		output(out, queue, queue[n].parent);
		fprintf(out, "%d", queue[n].num);
	}
}

void insertSort(int array[], int n){
	int i, j;
	int temp;

	for(i = 0;i < n - 1;i++){
		temp = array[i + 1];
		for(j = i + 1;j > 0 && temp < array[j - 1];j--)
			array[j] = array[j - 1];
		array[j] = temp;
	}
}