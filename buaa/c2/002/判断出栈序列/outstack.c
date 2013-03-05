/*【问题描述】
对于一个栈，已知元素的进栈序列，判断一个由栈中所有元素组成的排列是否是可能的出栈序列。
比如，进栈序列为1 2 3 4，则可能的出栈序列有4 3 2 1，1 4 3 2等。而1 4 2 3就不是。
【输入形式】
从标准输入读取输入。
第一行是一个整数N（3≤N≤10），代表有N个元素，其进栈序列是1 2 3 …… N。
第二行是以空格分隔的1~N的数字的一个排列。
【输出形式】
向标准输出打印结果。
如果该排列是可能的出栈序列，则打印“YES”，否则打印“NO”。在行末要输出一个回车符。
【输入样例】
4
1 4 3 2
【输出样例】
YES
【运行时限】
1秒
*/
#include<stdio.h>
enum {MAX = 10};
main()
{
	int standard[MAX] = {0}, array[MAX] = {0}, i, j = 0, n;
	int stack[MAX] = {0}, top = -1;
	scanf("%d", &n);
	for(i = 0;i < n;i++){
		standard[i] = i + 1;
		scanf("%d", &array[i]);
	}
	i = 0;
	
	while(i < n && j < n){
		if(array[j] != standard[i]){
			stack[++top] = standard[i];
			i++;
		}
		else{
			i++;j++;
		}	
	}
	while(j < n && top >= 0 && stack[top] == array[j]){
		j++;top--;
	}
	if(top == -1)
		printf("YES\n");
	else
		printf("NO\n");
}

