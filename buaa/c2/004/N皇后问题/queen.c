/*������������
��һ��N��N�Ĺ������������Ϸ���N��1 �� N �� 12�����ʺ�,ʹ�䲻�ܻ��๥���������������ʺ󶼲��ܴ���ͬһ�С�ͬһ�л�ͬһб���ϣ�
��������ȷ�İڷ���
��������ʽ��
����ӱ�׼�����϶���һ������N�� 
�������ʽ��
�ڱ�׼����ϴ�ӡ���з���Ҫ��Ļʺ�ڷŷ�����
����н⣬����������У�ÿ�а���N����������ʾ���������һ�ְڷŷ����������ֵ������У�
ÿ�ְڷŷ������α�ʾ�Ӵӵ�һ�е����һ�лʺ����ڵ��С�ÿ��ͬ�����ֵ������С�ÿ������ռ4���ַ���ȣ����Ҷ��룬���㲿�ֲ��Կո�
��ÿһ��ĩ�����һ���س����� 
����޽⣬�����No����N��д��oСд����
������������
4
�����������
###2###4###1###3
###3###1###4###2
����#����ո�
������ʱ�ޡ�
2��
*/
#include<stdio.h>
enum {MAX = 100};
int judge(int i, int j, int m, int n);
main()
{
	int n, i, j, p, q, chess[MAX] = {0}, count = 0;

	scanf("%d", &n);
	for(i = 0;i < n;i++){
		p = 0;
		chess[p] = i + 1;
		while(p >= 0 && p < n){
			chess[p + 1] = 1;
			for(j = 0;j < p;j++){
				while(chess[p] <= n){
					if(!judge(j, p, chess[j], chess[p])){
						chess[p]++;
						j = -1;
					}
					break;
				}
				if(chess[p] > n){
					chess[--p]++;
					p--;
					break;
				}
			}
			p++;
			if(chess[0] != i + 1)
				continue;
			if(p == n){
				for(q = 0;q < n;q++)
					printf("%4d", chess[q]);
				printf("\n");
				count++;
				chess[--p]++;
			}
		}
		
	}
	if(count == 0)
		printf("No\n");
}

int judge(int i, int j, int m, int n){
	if(m == n || ((m - n) == (j - i)) || ((n - m) == (j - i)))
		return 0;
	else
		return 1;
}