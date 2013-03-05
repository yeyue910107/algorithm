/*【问题描述】
写一程序，计算数据文件中指定列中数据的最大值、最小值和平均值。
【输入形式】
输入文件为当前目录下的colst.in。
文件由N + 1(1≤N≤20)行组成，第i行(1 ≤ i ≤ N)的第一列是由字母或数字组成的字符串，其余Mi列(1 ≤ Mi ≤ 20)是整数，
整数范围为（-1000000，1000000），各列之间用1个或多个空格符分隔。最后一行是一个整数k， (2 ≤ k ≤ max(Mi))，
为需要计算最大值、最小值和平均值的列号。
若某行的列数小于k，则认为该行k列的值为0。
【输出形式】
输出文件为当前目录下的colst.out。
文件只有一行，包含3个整数，分别是指定列中数据的最大值、最小值和平均值的四舍五入值，各整数之间用1个空格符分隔。
【输入样例】
Apple  290    370    341    732    3794   345 
Orange 7845   7485   20     783
Pear021    9354   521    8967   6745   892 
Banana 834    783    986    673
Grape  3581
watermelon 634    45871  4691   378    4571
Strawberry 6986   686    8368   623
Lemon      6982   343
Peach121      87     6784   345    778
Longan     8345   2798   783    224    683
Pineapple     3534   2843
5
【输出样例】
6745 0 994
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define DELTA 1E-9 
enum {MAX = 30, LEN = 200};
typedef struct{
	int num[MAX];
	int count;
}ARRAY;
void getResult(ARRAY array[], int n, int lineNum, FILE *out);
int main()
{
	FILE *in, *out;
	ARRAY array[MAX] = {0, 0};
	char buf[LEN], *token, temp[LEN];
	int i, lineNum, k, n;
	in = fopen("colst.in", "r");
	out = fopen("colst.out", "w");
	//in = fopen("colst1.txt", "r");
	//out = fopen("colst2.txt", "w");
	
	for(i = 0;fgets(buf, LEN + 1, in) != NULL;i++){
		strcpy(temp, buf);
		token = strtok(temp, " \n");
		k = 0;
		while(token){
			if(k > 0){
				array[i].num[k - 1] = atoi(token);
				array[i].count++;
			}
			k++;
			token = strtok(NULL, " \n");
		}
		if(k == 1)
			n = atoi(buf);
	}
	lineNum = i - 1;
	getResult(array, n - 2, lineNum, out);

	fclose(in);
	fclose(out);
}

void getResult(ARRAY array[], int n, int lineNum, FILE *out){
	int i, max, min, sum = 0, avg;

	max = min = array[0].num[n];
	for(i = 0;i < lineNum;i++){
		if(array[i].num[n] > max)
			max = array[i].num[n];
		if(array[i].num[n] < min)
			min = array[i].num[n];
		sum += array[i].num[n];
	}
	if(((double)(sum) / lineNum < DELTA && (double)(sum) / lineNum > -DELTA) || sum == 0)
		avg = 0;
	else if(sum > 0)
		avg = (int)((double)(sum) / lineNum + 0.5);
	else
		avg = (int)((double)(sum) / lineNum - 0.5);
	fprintf(out, "%d %d %d\n", max, min, avg);
}