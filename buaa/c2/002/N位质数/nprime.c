/*【问题描述】
给定一个整数N（2 <= N <= 8），生成所有的具有下列特性的特殊的N位质数：其前任意位都是质数。
例如，7331即是这样一个4位的质数，因为7、73和733也都是质数。
【输入形式】
标准输入上输入一个正整数N（2 <= N <= 8）
【输出形式】
标准输出。
输出所有符合题意的N位质数，每个数占一行，且按升序排列。
【输入样例】
2
【输出样例】
23
29
31
37
53
59
71
73
79
【运行时限】
5秒
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
