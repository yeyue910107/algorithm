/*【问题描述】
给定A、B、C三根足够长的细柱，在A柱上放有2n个中间有空的圆盘，共有n个不同的尺寸，每个尺寸都有两个相同的圆盘，
注意这两个圆盘是不加区分的。现要将这2n个圆盘移到C柱上，在移动过程中可放在B柱上暂存。
要求：
(1)每次只能移动一个圆盘；
(2) A、B、C三根细柱上的圆盘都要保持上小下大的顺序；
(3)对输入的n，求解完成上述任务所需最少移动次数M以及盘子的移动动作。
【输入形式】
从标准输入上读入一个正整数n (0 < n < 12)。
【输出形式】
在标准输出上输出最少移动次数M和移动动作。
输出形式：第一行为整数M，其余M行为移动动作。
移动动作格式如下：
move <盘子尺寸> from <原位置> to <新位置>
其中<盘子尺寸>为一个小于等于n的正整数，<原位置>和<新位置>均为字母A、B、C中的一个。
注：每个单词间一个有空格。
【输入样例】
2
【输出样例】
6
move 1 from A to B
move 1 from A to B
move 2 from A to C
move 2 from A to C
move 1 from B to C
move 1 from B to C
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {MAX = 5000};
int count = 0;
typedef struct{
	int n, from, to;
}PATH;
void hanoi(int n, int from, int to, int via, PATH path[]);
void move(int n, int from, int to, PATH path[]);
void output(PATH path[]);
int main()
{
	int n;
	PATH path[MAX] = {0};
	scanf("%d", &n);
	hanoi(n, 'A', 'C', 'B', path);
	output(path);
}

void hanoi(int n, int from, int to, int via, PATH path[]){
	if(n == 1){
		move(n, from, to, path);
		return;
	}
	hanoi(n - 1, from, via, to, path);
	move(n, from, to, path);
	hanoi(n - 1, via, to, from, path);
}

void move(int n, int from, int to, PATH path[]){
	path[count].n = n;
	path[count].from = from;
	path[count].to = to;
	path[count + 1].n = n;
	path[count + 1].from = from;
	path[count + 1].to = to;
	count += 2;
}

void output(PATH path[]){
	int i;
	
	printf("%d\n", count);
	for(i = 0;i < count;i++)
		printf("move %d from %c to %c\n", path[i].n, path[i].from, path[i].to);
	//printf("%d\n", count);
}