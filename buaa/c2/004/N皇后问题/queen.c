/*【问题描述】
在一个N×N的国际象棋棋盘上放置N（1 ￡ N ￡ 12）个皇后,使其不能互相攻击，即任意两个皇后都不能处于同一行、同一列或同一斜线上，
问所有正确的摆法。
【输入形式】
程序从标准输入上读入一个整数N。 
【输出形式】
在标准输出上打印所有符合要求的皇后摆放方法。
如果有解，输出有若干行，每行包含N个整数，表示符合题意的一种摆放方法，按照字典序排列，
每种摆放方法依次表示从从第一行到最后一行皇后所在的列。每列同样按字典序排列。每个数字占4个字符宽度，向右对齐，不足部分补以空格。
在每一行末均输出一个回车符。 
如果无解，输出“No”（N大写，o小写）。
【输入样例】
4
【输出样例】
###2###4###1###3
###3###1###4###2
其中#代表空格
【运行时限】
2秒
*/
#include<stdio.h>
enum {MAX = 100};
int judge(int i, int j, int m, int n);
main()
{
	int n, i, j, p, q, chess[MAX] = {0}, count = 0;

	scanf("%d", &n);
	for(i = 0;i < n;i++){
		p = 0;
		chess[p] = i + 1;
		while(p >= 0 && p < n){
			chess[p + 1] = 1;
			for(j = 0;j < p;j++){
				while(chess[p] <= n){
					if(!judge(j, p, chess[j], chess[p])){
						chess[p]++;
						j = -1;
					}
					break;
				}
				if(chess[p] > n){
					chess[--p]++;
					p--;
					break;
				}
			}
			p++;
			if(chess[0] != i + 1)
				continue;
			if(p == n){
				for(q = 0;q < n;q++)
					printf("%4d", chess[q]);
				printf("\n");
				count++;
				chess[--p]++;
			}
		}
		
	}
	if(count == 0)
		printf("No\n");
}

int judge(int i, int j, int m, int n){
	if(m == n || ((m - n) == (j - i)) || ((n - m) == (j - i)))
		return 0;
	else
		return 1;
}