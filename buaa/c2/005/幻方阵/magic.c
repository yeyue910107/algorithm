/*【问题描述】
“幻方阵”是指一个AN×N矩阵（在本题中N仅为奇数，且1≤N＜20），以自然数1，2， ...， N2为元素进行填充，每个位置上分别放置一个元素，使每行、每列以及主、副对角线上的元素之和都相等。
如3×3阶幻方阵，其每行、每列、主对角线、副对角线上元素之和均为15，如下图：
8  1  6
3  5  7
4  9  2
输入一个奇数N，打印对应的N阶幻方阵。
【输入形式】
从标准输入读取一个奇数N(1≤N＜20)。
【输出形式】
向标准输出上输出一个N×N的幻方阵，其中每个数字占4位字符的宽度，向右对齐。
【输入样例】
3
【输出样例】
   8   1   6

   3   5   7

   4   9   2
【运行时限】
    1秒
*/
#include<stdio.h>
enum {MAX = 20};
void findMagic(int magic[][MAX], int n);
void printMagic(int magic[][MAX], int n);
main()
{
	int magic[MAX][MAX] = {0};
	int n;

	scanf("%d", &n);
	//magic[0][n / 2] = 1;
	findMagic(magic, n);
	printMagic(magic, n);
}

void findMagic(int magic[][MAX], int n){
	int k, i = 0, j = n / 2;
	
	magic[0][n / 2] = 1;
	for(k = 2;k <= n * n;k++){
		if(i == 0 && j == n - 1){
			//if(magic[i + 1][])
			i++;
			magic[i][j] = k;
		}
		else if(i == 0){
			i = n - 1;j++;
			magic[i][j] = k;
		}
		else if(j == n - 1){
			i--;j = 0;
			magic[i][j] = k;
		}
		else if(magic[i - 1][j + 1] != 0){
			i++;
			magic[i][j] = k;
		}
		else
			magic[--i][++j] = k;
	}
}

void printMagic(int magic[][MAX], int n){
	int i, j;

	for(i = 0;i < n;i++){
		for(j = 0;j < n;j++)
			printf("%4d", magic[i][j]);
		printf("\n");
	}
}