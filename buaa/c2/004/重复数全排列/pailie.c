/*【问题描述】
输入一个字符串，字符串由字母、数字组成，可能包含重复的字符。生成这些字符的不重复的全排列，并将结果打印到标准输出上。
【输入形式】
从标准输入上读入一个由字母、数字组成的字符串，字符串的长度小于100，其中包含重复的字符。
【输出形式】
向标准输出印结果。
每个排列占1行，各字符之间无空格分隔，每行由换行符结束。各行之间不必排序，但同一个排列不得重复输出。
【输入样例】
AABB
【输出样例】
AABB
ABAB
ABBA
BABA
BAAB
BBAA
【运行时限】
10秒
*/
#include<stdio.h>
enum {MAX = 500};
char res[MAX];
int count[MAX];
int COUNT = 0;
//int COUNT = 0;
void arrange(int k, char array[]);
void swap(char *a, char *b);
void insertSort(char array[]);
void record(char array[], int num[]);
main()
{
	int i, n;
	char c;
	//scanf("%d%d", &n, &m);
	//loop = factor(n - m);
	i = 0;
	while((c = getchar()) != '\n'){
		res[i] = c;
		i++;
	}
	res[i] = '\0';
	n = i;
	insertSort(res);
	//record(res, count);
	arrange(n, res);
	//printf("%d\n", COUNT);
}

void arrange(int k, char array[]){
	int i = 0;
	int num = 0;
	//COUNT = 0;
	if(k == 1){
		printf("%s", res);
		printf("\n");
		COUNT++;
		return;
	}
	
	
	while(i < k){
		record(&array[0], count);
		if(num >= 1 && count[num] == 0){
			//num = 0;
			return;
		}
		i = count[num];
		
		swap(&array[0], &array[i]);
		//insertSort(&array[i + 1], k - i);
		//COUNT = 0;
		//circleRight(array, 1, i);
		arrange(k - 1, &array[1]);
		//circleLeft(array, 1, i);
		swap(&array[i], &array[0]);
		//record(&array[0], count);
		num++;
	}
}

void swap(char *a, char *b){
	char temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void insertSort(char array[]){
	int i, j;
	char temp;

	for(i = 0;array[i + 1] != '\0';i++){
		temp = array[i + 1];
		for(j = i + 1;j > 0 && temp < array[j - 1];j--)
			array[j] = array[j - 1];
		array[j] = temp;
	}
}

void record(char array[], int num[]){
	int i, j, k = 0;
	insertSort(array);
	//int num[MAX] = {0};
	num[k] = 0;
	for(i = 1;array[i] != '\0';i++){
		if(array[i] != array[0] && array[i] != array[i - 1])
			num[++k] = i;
	}
	num[++k] = 0;
	//num[++k] = i;
	//return num;
}