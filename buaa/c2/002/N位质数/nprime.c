/*������������
����һ������N��2 <= N <= 8�����������еľ����������Ե������Nλ��������ǰ����λ����������
���磬7331��������һ��4λ����������Ϊ7��73��733Ҳ����������
��������ʽ��
��׼����������һ��������N��2 <= N <= 8��
�������ʽ��
��׼�����
������з��������Nλ������ÿ����ռһ�У��Ұ��������С�
������������
2
�����������
23
29
31
37
53
59
71
73
79
������ʱ�ޡ�
5��
*/
#include<stdio.h>
int isPrime(int n);
main()
{
	int n, i, k, j;
	long prime, temp;
	int PRIME[4] = {2, 3, 5, 7};
	scanf("%d", &n);
	for(i = 0; i < 4;i++){

		temp = PRIME[i];
		k = 1;
		while(k < n){
		while(k < n && isPrime(temp)){
			temp = temp * 10 + 1;
			k++;
			if(k == n){
				while(temp % 10 < 9){
					if(isPrime(temp))
						printf("%ld\n", temp);
					temp += 2;
				}
				
				while(temp % 10 == 9){
					if(k == n && isPrime(temp))
						printf("%ld\n", temp);
					temp /= 10;
					k--;
				}
				if(k == 1)
					break;
				temp += 2;
			}
		}
			if(k == 1)
				break;
			else{
				while(temp % 10 == 9){
					temp /= 10;
					k--;
				}
				if(k == 1)
					break;
				temp += 2;
			}
		}
	}
}

int isPrime(int n)
{
	int i;

	for(i = 3;i < n / 2;i += 2)
		if(n % i == 0)
			return 0;
	return 1;
}
