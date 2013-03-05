/*������������
���÷�����ָһ��AN��N�����ڱ�����N��Ϊ��������1��N��20��������Ȼ��1��2�� ...�� N2ΪԪ�ؽ�����䣬ÿ��λ���Ϸֱ����һ��Ԫ�أ�ʹÿ�С�ÿ���Լ��������Խ����ϵ�Ԫ��֮�Ͷ���ȡ�
��3��3�׻÷�����ÿ�С�ÿ�С����Խ��ߡ����Խ�����Ԫ��֮�;�Ϊ15������ͼ��
8  1  6
3  5  7
4  9  2
����һ������N����ӡ��Ӧ��N�׻÷���
��������ʽ��
�ӱ�׼�����ȡһ������N(1��N��20)��
�������ʽ��
���׼��������һ��N��N�Ļ÷�������ÿ������ռ4λ�ַ��Ŀ�ȣ����Ҷ��롣
������������
3
�����������
   8   1   6

   3   5   7

   4   9   2
������ʱ�ޡ�
    1��
*/
#include<stdio.h>
enum {MAX = 20};
void findMagic(int magic[][MAX], int n);
void printMagic(int magic[][MAX], int n);
main()
{
	int magic[MAX][MAX] = {0};
	int n;

	scanf("%d", &n);
	//magic[0][n / 2] = 1;
	findMagic(magic, n);
	printMagic(magic, n);
}

void findMagic(int magic[][MAX], int n){
	int k, i = 0, j = n / 2;
	
	magic[0][n / 2] = 1;
	for(k = 2;k <= n * n;k++){
		if(i == 0 && j == n - 1){
			//if(magic[i + 1][])
			i++;
			magic[i][j] = k;
		}
		else if(i == 0){
			i = n - 1;j++;
			magic[i][j] = k;
		}
		else if(j == n - 1){
			i--;j = 0;
			magic[i][j] = k;
		}
		else if(magic[i - 1][j + 1] != 0){
			i++;
			magic[i][j] = k;
		}
		else
			magic[--i][++j] = k;
	}
}

void printMagic(int magic[][MAX], int n){
	int i, j;

	for(i = 0;i < n;i++){
		for(j = 0;j < n;j++)
			printf("%4d", magic[i][j]);
		printf("\n");
	}
}