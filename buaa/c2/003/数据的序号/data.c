/*【问题描述】
将N(1<= N <= 200000)个整数小到大连续编号，相同的数应具有相同的编号。并按这N个数输入时的顺序输出它们的编号序列。
例如，设输入数据为 5 3 4 7 3 5 6，则输出数据为3 1 2 5 1 3 4。
【输入形式】
从标准输入读取数据。
输入包含N个数字(1<= N <= 200000)，之间由空格分隔，以回车符作为结束。
【输出形式】
计算结果输出到标准输出。
按这N个数输入时的顺序输出它们的编号序列。每个序号之后紧跟一个空格符，最后输出回车符。
【输入样例】
5 3 4 7 3 5 6
【输出样例】
3 1 2 5 1 3 4
*/
#include<stdio.h>
enum {MAX = 20000};
typedef struct{
	int num;
	int rank;
	int position;
}DATA;
void insertSort(DATA data[], int n);
main()
{
	int n, i;
	char c;
	DATA data[MAX];

	i = 0;
	while(1){
		scanf("%d", &data[i].num);
		data[i].rank = i + 1;
		data[i].position = i;
		c = getchar();
		i++;
		if(c == '\n')
			break;
	}
	n = i;
	insertSort(data, n);
	for(i = 0;i < n;i++)
		printf("%d%c", data[i].rank, (i == n - 1)?'\n':' ');
}

void insertSort(DATA data[], int n){
	int i, j, temp, m, p, count = 0;
	//DATA tempData;
	//DATA num[MAX];

	//for(i = 0;i < n;i++)
		//num[i].num = data[i].num;
	for(i = 0;i < n - 1;i++){
		temp = data[i + 1].num;
		m = data[i + 1].position;
		for(j = i + 1;j > 0 && temp < data[j - 1].num;j--){
			data[j].num = data[j - 1].num;
			data[j].position = data[j - 1].position;
		}
		data[j].num = temp;
		data[j].position = m;
	}
	for(i = 1;i < n;i++){
		if(data[i].num == data[i - 1].num)
			data[i].rank = data[i - 1].rank;
		else
			data[i].rank = data[i - 1].rank + 1;
	}

	for(i = 0;i < n - 1;i++){
		m = data[i + 1].position;
		temp = data[i + 1].rank;
		p = data[i + 1].num;
		for(j = i + 1;j > 0 && m < data[j - 1].position;j--){
			data[j].num = data[j - 1].num;
			data[j].rank = data[j - 1].rank;
			data[j].position = data[j - 1].position;
			//data[j] = data[j - 1];
		}
		data[j].num = p;
		data[j].rank = temp;
		data[j].position = m;
		//data
	}
}