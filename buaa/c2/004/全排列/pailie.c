/*������������
���n����Ȼ��(1-n)��ѡȡm���������е�������ʽ������P��n��m�������е�������ʽ���Ұ��������С�
��������ʽ��
��׼���롣����ֻ��һ�У�������������n��m������0<n,m<=9������֮����һ���հ׷��ָ���
�������ʽ��
�ڱ�׼���������������У�ÿһ�ж��Ƿ��������һ��������ʽ��ÿ��Ԫ�ؼ���һ���ո�ָ��������������С�
������������
3 2
�����������
1 2
1 3
2 1
2 3
3 1
3 2
������ʱ�ޡ�
2�롣
*/
#include<stdio.h>
enum {MAX = 10};
int res[MAX];
int count = 0;
int loop;
void arrange(int k, int array[], int m);
void output(int array[], int m);
int factor(int n);
void swap(int *a, int *b);
void circleRight(int array[], int k, int i);
void circleLeft(int array[], int k, int i);
main()
{
	int i, n, m;

	scanf("%d%d", &n, &m);
	loop = factor(n - m);
	for(i = 0;i < n;i++)
		res[i] = i + 1;
	arrange(n, res, m);
}

void arrange(int k, int array[], int m){
	int i;
	if(k == 1){
		if(count % loop == 0)
			output(res, m);
		count++;
		return;
	}
	for(i = 0;i < k;i++){
		swap(&array[0], &array[i]);
		circleRight(array, 1, i);
		arrange(k - 1, &array[1], m);
		circleLeft(array, 1, i);
		swap(&array[i], &array[0]);
	}
}

void circleRight(int array[], int k, int i){
	int temp, j;
	if(i > k){
		temp = array[i];
		for(j = i;j > k;j--)
			array[j] = array[j - 1];
		array[k] = temp;
	}
}

void circleLeft(int array[], int k, int i){
	int temp, j;
	
	if(i > k){
		temp = array[k];
		for(j = k;j < i;j++)
			array[j] = array[j + 1];
		array[i] = temp;
	}
}

void output(int array[], int m){
	int i;

	for(i = 0;i < m;i++)
		printf("%d%c", array[i], (i == m - 1)?'\n':' ');
}

int factor(int n){
	int i, res = 1;

	for(i = 2;i <= n;i++)
		res *= i;
	return res;
}

void swap(int *a, int *b){
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}