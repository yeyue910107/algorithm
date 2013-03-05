/*������������
��n��һ����Ȼ������������е���Ȼ��x��x<n����x��Լ������������n��Լ�����������n��һ��Antiprime�����磺1, 2, 4, 6, 12, 24��
�Լ��㲻����n�����Antiprime����
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�antiprime.in��
���ļ�ֻ��һ������n����1��n��20 000 000 00����
�������ʽ��
����ļ�Ϊ��ǰĿ¼�µ�antiprime.out��
���ļ�ֻ����һ����������������n�����Antiprime����
������������ 
100
�����������
60
*/
#include<stdio.h>
enum {PrimeNum = 11};
int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
int getAntiprime(int n);
int divisors(int n);
main()
{
	int n;
	FILE *in, *out;

	in = fopen("antiprime.in", "r");
	out = fopen("antiprime.out", "w");
	//in = stdin;
	//out = stdout;
	fscanf(in, "%d", &n);
	fprintf(out, "%d", getAntiprime(n));
	fclose(in);
	fclose(out);
}

int getAntiprime(int n){
	int m, i, k, max = 0, num = 0, count;

	for(i = 0, k = 1;(double)k * (double)k <= n;i++)
		k *= prime[i];
	m = k;
	while(k <= n){
		count = divisors(k);
		if(count > max){
			max = count;
			num = k;
		}
		k += m;
	}
	return num;
}

int divisors(int n){
	int i, k = 1, m;

	for(i = 0;i < PrimeNum;i++){
		for(m = 0;n % prime[i] == 0;m++)
			n /= prime[i];
		if(m > 0)
			k *= (m + 1);
	}
	if(k == 1)
		return 0;
	return k;
}
