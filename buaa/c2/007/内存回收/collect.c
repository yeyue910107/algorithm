/*【问题描述】
程序运行过程中可能产生没用的内存块，称为内存垃圾。需要使用内存回收技术不断检查是否存在内存垃圾，并将它们及时释放，
以备后面重新使用。
在内存中存在多个内存块，每一个内存块中都有一个索引表，指向和它相关联的其它内存块。有用的内存块称为“活动”的内存块。
从当前已知的活动内存块出发，通过一级或多级索引能够检索到的其它内存块，也是活动的。否则该内存块就是垃圾内存块。
例如，如下图所示的索引关系中，标有root的内存块1、2为已知的活动内存块。从内存块1、2出发，沿箭头方向检索，
可得知3、4、5、8都是活动内存块（在图中以黄色表示）。需要回收的垃圾内存块为6、7、9、10、11。
现已知有若干个内存块和它们之间的索引关系，要求编程找出所有内存垃圾。
【输入形式】
输入文件为当前目录下的collect.in。
该文件第一行为两个整数n（1≤n≤5）和m（0≤m≤50）， n表示root内存块的个数，m表示其它内存块的个数。n和m之间用空格分隔。
后面紧跟有n+m行，每行有若干个以空格分隔的整数。第i行（1≤ i≤m+n）整数表示从第i个内存块可以直接检索到的内存块的编号，
每行数字都以0结尾。其中前n行是活动的root内存块。
【输出形式】
输入文件为当前目录下的collect.out。
要求在该文件中输出一行整数，是所有垃圾内存块的编号。各整数按从小到大的次序输入，之间以一个空格符分隔。
如果没有垃圾内存块，则输出一个整数-1。
【输入样例】
2 9
3 4 0
4 5 0
0
8 0
0
1 0
8 10 11 0
0
0
11 0
0
【输出样例】
6 7 9 10 11
【样例说明】
第一行输入n=2，m=9，表示共有11个内存块，其中有2个root内存块。
以后的11行分别表示了各内存块可以直接索引到的内存块编号。
计算结果如上例所示。
*/
#include<stdio.h>
enum {MAX = 100};
void getResult(int mem[][MAX], int n, int m, FILE *out);
main()
{
	int n, m, i = 0, k, temp;
	int mem[MAX][MAX] = {0};
	FILE *in, *out;

	in = fopen("collect.in", "r");
	out = fopen("collect.out", "w");
	//in = stdin;
	//out = stdout;
	fscanf(in, "%d%d", &n, &m);
	while(i < n + m){
		k = 0;
		while(1){
			fscanf(in, "%d", &temp);
			if(temp == 0)
				break;
			mem[i][k++] = temp;
		}
		i++;
	}
	getResult(mem, n, m, out);
}

void getResult(int mem[][MAX], int n, int m, FILE *out){
	int i, j, k, stack[MAX], used[MAX] = {0}, flag = 0, count = 0, top = -1, temp;

	/*for(i = 0; i < n;i++){
		for(j = 0;mem[i][j] != 0;j++){
			used[mem[i][j] - 1] = 1;
			for(k = 0;mem[mem[i][j] - 1][k] != 0;k++)
				used[mem[mem[i][j] - 1][k] - 1] = 1;
		}
	}*/
	for(i = 0;i < n;i++){
		for(j = 0;mem[i][j] != 0;j++){
			if(!used[mem[i][j] - 1]){
				used[mem[i][j] - 1] = 1;
				stack[++top] = mem[i][j];
			}
		}
	}
	while(top >= 0){
		for(k = 0;mem[stack[top] - 1][k] != 0;k++){
			temp = mem[stack[top] - 1][k];
			if(!used[temp - 1]){
				stack[++top] = temp;
				used[temp - 1] = 1;
				//top++;
				break;
			}
		}
		if(mem[stack[top] - 1][k] == 0)
			top--;
	}
	for(i = n;i < m + n;i++)
		if(!used[i]){
			if(!flag)
				flag = 1;
			else
				fputc(' ', out);
			fprintf(out, "%d", i + 1);
		}
	if(!flag)
		fprintf(out, "-1");
	fputc('\n', out);
}