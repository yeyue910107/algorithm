/*������������
��n����Ȼ��(1-n)������m-��ϣ���C��n��m�������в����ظ��������ʽ��
��������ʽ��
��׼���롣����ֻ��һ�У�������������n��m������0<n<=20��0<m<=9������֮����һ���հ׷��ָ���
�������ݿ��Ա�֤���㷨�õ�����£��涨ʱ���ڿ�����ɡ�
�������ʽ��
�ڱ�׼���������������У�ÿһ�ж��Ƿ��������һ��������ʽ��ÿ��Ԫ�ؼ���һ���ո�ָ��������������С�
������������
3 2
�����������
1 2 
1 3
2 3
*/
#include<stdio.h>
enum {MAX = 20};
int res[MAX];
int used[MAX] = {0};
int end[MAX] = {0};
int count = 0;
void arrange(int k, int m, int n);
void output(int array[], int m);
main()
{
	int n, m;

	scanf("%d%d", &n, &m);
	arrange(0, m, n);
}

void arrange(int k, int m, int n){
	int i, j;

	if(k == m){
		output(res, m);
		return;
	}
	for(i = 0;i < n;i++){
		if(!used[i] && !end[i]){
			used[i] = 1;
			res[k] = i + 1;
			arrange(k + 1, m, n);
		}
		else
			continue;
		used[i] = 0;
	}
	end[res[k - 1] - 1] = 1;
	for(j = res[k - 1];j < n;j++)
		end[j] = 0;
}

void output(int array[], int m){
	int i;

	for(i = 0;i < m;i++)
		printf("%d%c", array[i], (i == m - 1)?'\n':' ');
}
