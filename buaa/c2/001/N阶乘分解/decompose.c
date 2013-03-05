/*������������
��N���ֽ�������ݵĳ˻���
��������ʽ��
�ӱ�׼�����ȡһ������N��1��N��30000����
�������ʽ��
�����ӡ����׼�����
�����ʽΪ��p1^k1*p2^k2������p1,p2��Ϊ������ki>1����ki=1ʱֻ���pi��ki=0���������ֽ�ʽ�е���������С���������
������������
5
�����������
2^3*3*5
*/
#include<stdio.h>
enum {MAX = 5000};
typedef struct{
	int prime;
	int times;
}PRIME;
int primeTable(PRIME prime[], int n);
int addTimes(PRIME prime[], int n, int primeNum);
main()
{
	int n, i, primeNum, max = 1, maxTemp;
	PRIME prime[MAX]={0};

	primeNum = primeTable(prime, 30000);
	scanf("%d", &n);
	for(i = 2;i <= n;i++){
		maxTemp = addTimes(prime, i, primeNum);
		if(maxTemp > max)
			max = maxTemp;

	}
	for(i = 0;i < primeNum;i++){
		if(prime[i].times == 0)
			continue;
		else if(prime[i].times == 1)
			printf("%d%c", prime[i].prime, (prime[i].prime == max)?'\n':'*');
		else{
			printf("%d^%d%c", prime[i].prime, prime[i].times, (prime[i].prime == max)?'\n':'*');
		}
	}
}

int primeTable(PRIME prime[], int n){
	int i, k, j = 2;
	
	prime[0].prime = 2;
	prime[1].prime = 3;
	for(i = 2;i <= n / 2;i++){
		for(k = 2;k < i && i % k != 0;k++)
			;
		if(k == i)
			prime[j++].prime = k;
	}
	return j;
}

int addTimes(PRIME prime[], int n, int primeNum){
	int i, max = 1;
	
	for(i = 0;i < primeNum;i++){
		while(n > 1 && n % prime[i].prime == 0){
			/*if((prime[i].prime * prime[i].prime * prime[i].prime) < 30000 && n % (prime[i].prime * prime[i].prime * prime[i].prime) == 0){
				prime[i].times += 3;
				n /= (prime[i].prime * prime[i].prime * prime[i].prime);
			}
			else *//*if((prime[i].prime * prime[i].prime) < 30000 && n % (prime[i].prime * prime[i].prime) == 0){
				prime[i].times += 2;
				n /= (prime[i].prime * prime[i].prime);
			}
			else if(n % prime[i].prime == 0){
				prime[i].times++;
				//if(prime[i].prime > max)
				//max = prime[i].prime;
				//break;
				n /= prime[i].prime;
			}
			//else
				//break;*/
			prime[i].times++;
			n /= prime[i].prime;
			if(prime[i].prime > max)
				max = prime[i].prime;
		}
	}
	return max;
}