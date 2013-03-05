/*【问题描述】
给定n个闭区间[ai, bi]（1 ￡ i ￡ n），这些区间的并可以表示为一些不相交的闭区间的并。
要求在这些表示方式中找出包含不相交区间数目最少的方案。
【输入形式】
输入文件为当前目录下的prz.in。
该文件的第一行包含一个整数n（3 ￡ n ￡ 50000），为区间的数目。以下有n行，每行各包括两个以空格分隔的整数ai 和 bi，
表示一个区间[ai, bi]（1 ￡ ai ￡ bi ￡ 1000000）。
【输出形式】
输出文件为当前目录下的prz.out。
该文件内容为计算出来的不相交的区间。每一行都是对一个区间的描述，包括两个以空格分开的整数，分别为区间的下界和上界。
输出时将各区间按照升序排列输出。这里说两个区间[a, b]和[c, d]是按照升序排列的，是指a ￡ b < c ￡ d。
【输入样例】
5
5 6
1 4
10 10
6 9
8 10
【输出样例】
1 4
5 10
*/
#include<stdio.h>
enum {MAX = 100};

typedef struct{
	long sup;//上界
	long inf;//下界
}INTERVAL;
void insertSortDouble(double array[], int n);
void insertSortLong(long array[], int n);
int isInInterval(long n, INTERVAL interval);
main()
{
	FILE *in, *out, *test;
	int i, j, k = 0, p = 0, t = 0, arrayNum, flag = 0, rsNum;
	long n, temp, sup, inf, num = 0;
	double array[MAX] = {0.0};
	long isolate[MAX] = {0};
	INTERVAL interval[MAX] = {0};
	INTERVAL rs[MAX] = {0};

	//in = fopen("prz.in", "r");
	//out = fopen("prz.out", "w");
	test = fopen("test.tet", "w");

	in = stdin;
	out = stdout;
	fscanf(in, "%ld", &n);
	for(i = 0;i < n;i++){
		fscanf(in, "%ld%ld", &sup, &inf);
		if(sup == inf)
			isolate[p++] = sup;
		else{
			interval[num].sup = sup;
			interval[num].inf = inf;
			for(j = interval[num].sup;j < interval[num].inf;j++){
				array[k++] = j + 0.5;
			}
			num++;
		}
	}
	arrayNum = k;
	if(k == 0){
		insertSortLong(isolate, p);
		i = 0;
		while(i < p){
			if(i > 0 && isolate[i] == isolate[i - 1]){
				i++;
				continue;
			}
			fprintf(out, "%ld %ld\n", isolate[i], isolate[i]);
			i++;
		}
	}
	else{
		insertSortDouble(array, arrayNum);
		insertSortLong(isolate, p);
		temp = (long)(array[0] - 0.5);
		rs[t].sup = temp;
		//if()
		//fprintf(out, "%ld ", temp);
		flag = 1;
		k = 0;
		while(k < arrayNum){
			if(k > 0 && array[k] == array[k - 1]){
				k++;
				continue;
			}
			else if(temp >= (long)(array[k] - 0.5)){
				if(flag == 0)
					//fprintf(out, "%ld ", temp);
					rs[t].sup = temp;
				temp++;
				k++;
				flag = 1;
				continue;
			}
			else{
				//fprintf(out, "%ld\n", temp);
				rs[t++].inf = temp;
				temp = (int)(array[k] - 0.5);
				flag = 0;
			}
		}
		//fprintf(out, "%ld\n", temp);
		rs[t++].inf = temp;
		rsNum = t;
		t = 0;
		i = 0;
		flag = 1;
		while(t < rsNum && i < p){
			if(i > 0 && isolate[i] == isolate[i - 1]){
				i++;
				continue;
			}
				if(isInInterval(isolate[i], rs[t])){
					if(flag){
						fprintf(out, "%ld %ld\n", rs[t].sup, rs[t].inf);
						flag = 0;
					}
					i++;
				}
				else if(isolate[i] < rs[t].sup){
					fprintf(out, "%ld %ld\n", isolate[i], isolate[i]);
					i++;
				}
				else if(isolate[i] > rs[t].sup){
					if(flag){
						fprintf(out, "%ld %ld\n", rs[t].sup, rs[t].inf);
					}
					t++;
					flag = 1;
				}
		}
		while(t < rsNum && flag == 1){
			fprintf(out, "%ld %ld\n", rs[t].sup, rs[t].inf);
			t++;
		}
		while(i < p){
			fprintf(out, "%ld %ld\n", isolate[i], isolate[i]);
			i++;
		}
	}
	fclose(in);
	fclose(out);
}

void insertSortDouble(double array[], int n){
	int i, j;
	double temp;

	for(i = 0;i < n - 1;i++){
		temp = array[i + 1];
		for(j = i + 1;j > 0 && temp < array[j - 1];j--)
			array[j] = array[j - 1];
		array[j] = temp;
	}
}

void insertSortLong(long array[], int n){
	int i, j;
	long temp;

	for(i = 0;i < n - 1;i++){
		temp = array[i + 1];
		for(j = i + 1;j > 0 && temp < array[j - 1];j--)
			array[j] = array[j - 1];
		array[j] = temp;
	}
}

int isInInterval(long n, INTERVAL interval){
	if(n <= interval.inf && n >= interval.sup)
		return 1;
	else
		return 0;
}