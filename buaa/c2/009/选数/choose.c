/*������������
��֪n��1��n��20��������x1,x2,����,xn,�Լ�һ������k��1��k��n������n����������ѡk��������ӣ��ɷֱ�õ�һϵ�еĺͣ�
�������к�Ϊ������������ж����֡�����n=4��k=3ʱ�� 4�������ֱ�Ϊ3��7��12��19ʱ��
�ɵ�ȫ������������ǵĺ�Ϊ��3+7+12=22��3+7+19=29��7+12+19=38��3+12+19=34����ʱֻ��һ�������Ϊ��������3+7+19=29���� 
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�choose.in��
���ļ���һ��Ϊһ��������k��1��k��n���������n�У�1��n��20���ֱ�Ϊx1,x2,������xn(1 ��xi��5000000)��ʾ��n������������EOF����
�������ʽ��
����ļ�Ϊ��ǰĿ¼�µ�choose.out��
���ļ�ֻ��һ������������������Ϊ������������
������������
3
3
7
12
19
�����������
1
*/
#include<stdio.h>
enum {MAX = 20};
int res[MAX];
int used[MAX] = {0};
int end[MAX] = {0};
int count = 0, primeNum = 0;
void arrange(int k, int m, int n, int num[]);
int sum(int array[], int num[], int m);
int isPrime(int n);
main()
{
	int m, n, i = 0, num[MAX];
	FILE *in, *out;
	in = fopen("choose.in", "r");
	out = fopen("choose.out", "w");
	//in = fopen("choose1.txt", "r");
	//out = fopen("choose2.txt", "w"); 

	fscanf(in, "%d", &m);
	while(fscanf(in, "%d", &num[i]) > 0)
		i++;
	n = i;
	arrange(0, m, n, num);
	fprintf(out, "%d", primeNum);

	fclose(in);
	fclose(out);
}

void arrange(int k, int m, int n, int num[]){
	int i, j;

	if(k == m){
		if(isPrime(sum(res, num, m)))
			primeNum++;
		return;
	}
	for(i = 0;i < n;i++){
		if(!used[i] && !end[i]){
			used[i] = 1;
			res[k] = i + 1;
			arrange(k + 1, m, n, num);
		}
		else
			continue;
		used[i] = 0;
	}
	end[res[k - 1] - 1] = 1;
	for(j = res[k - 1];j < n;j++)
		end[j] = 0;
}

int sum(int array[], int num[], int m){
	int i, sum = 0;

	for(i = 0;i < m;i++)
		sum += num[array[i] - 1];
		//printf("%d%c", array[i], (i == m - 1)?'\n':' ');
	return sum;
}

int isPrime(int n){
	int i;

	for(i = 2;i * i <= n;i++)
		if(n % i == 0)
			return 0;
	return 1;
}