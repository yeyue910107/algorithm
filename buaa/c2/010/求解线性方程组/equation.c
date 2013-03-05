/*������������
��֪���Է�����AX=B�����÷����顣
�ο��㷨��
��ȥ������������B�ӵ�����A�����һ�У������������AB����AB�����������ֳ��ȱ任��ʹԭ����A�Ĳ��ֵ����Խ����ϵ�Ԫ�ؾ�Ϊ1��
����Ԫ�ؾ�Ϊ0����ԭ������B�Ĳ��ּ�ΪX��ֵ��
1.  �������һ�г���һ����Ϊ0����
2.  �������һ�м�����һ�еı���
3.  �������������е�λ��
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�equation.in��
���ļ���N��(1��N��50)��ÿ����N + 1������������ÿ��ǰN����Ϊ����A�е�Ԫ��aij��-20��aij��20����
��N+1����Ϊ������B�е�Ԫ��bi��-200��bi��200����
�������ʽ��
����������׼����ϡ�
���ռһ�У�����N����ֵ��˳��Ϊx1x2�� ��xN��������λС����ÿ������ֵ֮���ÿո�ָ���
������������
3 6 51
5 1 31
�����������
5.00 6.00
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {MAX = 50, LINE = 80};
int inputMatrix(int matrix[][MAX + 1], FILE *in);
void lineSimplify(int matrix[][MAX + 1], int size);
int leastCommonMultiply(int a, int b);
void outputSolution(int matrix[][MAX + 1], int size);
int main()
{
	int matrix[MAX][MAX + 1];
	int size;
	FILE *in;
	in = fopen("equation.in", "r");
	//in = fopen("equation.txt", "r");
	size = inputMatrix(matrix, in);
	lineSimplify(matrix, size);
	outputSolution(matrix, size);
	fclose(in);
}

int inputMatrix(int matrix[][MAX + 1], FILE *in){
	int i, j, size;
	char *token, buf[LINE];

	i = 0;
	while(fgets(buf, LINE + 1, in) != NULL){
		j = 0;
		token = strtok(buf, " \n");
		while(token != NULL){
			matrix[i][j] = atoi(token);
			token = strtok(NULL, " \n");
			j++;
		}
		//size = j - 1;
		i++;
	}
	size = j - 1;
	return size;
}

void lineSimplify(int matrix[][MAX + 1], int size)/*������м�*/{
	int change1, change2, i, j, k, p, min_of_line, greatest_common_divisor = 1;

	for(i = 0;i < size;i++)
		for(j = i + 1;j < size;j++){
			if(matrix[i][i] == 0 && matrix[j][i] != 0)
				for(k = 0;k < size + 1;k++)
					matrix[i][k] += matrix[j][k];
			else if(matrix[i][i] == 0 && matrix[j][i] == 0){
				for(p = i + 1;p < size + 1;p++){
					if(matrix[i][p] != 0 || matrix[j][p] != 0){
						if(matrix[i][p] < 0)
							for(k = p;k < size + 1;k++)
								matrix[i][k] =- matrix[i][k];
						if(matrix[j][p] < 0)
							for(k = p;k < size + 1;k++)
								matrix[j][k] =- matrix[j][k];
						change1 = leastCommonMultiply(matrix[j][p], matrix[i][p]) / matrix[j][p];	
						change2 = leastCommonMultiply(matrix[j][p], matrix[i][p]) / matrix[i][p];
						for(k = 0;k < size + 1;k++)
							matrix[j][k] *= change1;
						for(k = 0;k < size + 1;k++)
							matrix[j][k] = matrix[j][k] - matrix[i][k] * change2;
						break;
					}
				}
				continue;
			}
			else if(matrix[i][i] != 0 && matrix[j][i] == 0)
				continue;
			if(matrix[i][i] < 0)
				for(k = i;k < size + 1;k++)
					matrix[i][k] = -matrix[i][k];
			if(matrix[j][i] < 0)
				for(k = i;k < size + 1;k++)
					matrix[j][k] = -matrix[j][k];
			change1 = leastCommonMultiply(matrix[j][i], matrix[i][i]) / matrix[j][i];	
			change2 = leastCommonMultiply(matrix[j][i], matrix[i][i]) / matrix[i][i];
			for(k = 0;k < size + 1;k++)
				matrix[j][k] *= change1;
			for(k = 0;k < size + 1;k++)
				matrix[j][k] = matrix[j][k] - matrix[i][k] * change2;
		}
	/*��ÿһ�����*/
	for(i = 0;i < size;i++){
		for(j = 0;j < size + 1 && matrix[i][j] == 0;j++)
			;
		if(j == size + 1)
			continue;
		else
			min_of_line = matrix[i][j];
		for(;j < size + 1;j++){
			//if((int)fabs(matrix[i][j]) < min_of_line && (int)fabs(matrix[i][j]) > 0)
			//	min_of_line = (int)fabs(matrix[i][j]);
			if(matrix[i][j] < 0 && matrix[i][j] > -min_of_line)
				min_of_line = -matrix[i][j];
			else if(matrix[i][j] > 0 && matrix[i][j] < min_of_line)
				min_of_line = matrix[i][j];
		}
		for(p = 1;p <= min_of_line;p++){
			for(j = 0;j < size + 1 && matrix[i][j] % p == 0;j++)
				;
			if(j == size + 1)
				greatest_common_divisor = p;
		}
		for(j = 0;j < size + 1;j++)
			matrix[i][j] /= greatest_common_divisor;
	}
	for(i = 0;i < size - 1;i++)
		for(j = i + 1;j< size;j++){
			if(matrix[i][j]==0)
				continue;
			if(matrix[i][j]<0)
				for(k = 0;k < size + 1;k++)
					matrix[i][k] = -matrix[i][k];
			if(matrix[j][j] < 0)
				for(k = 0;k < size + 1;k++)
					matrix[j][k] = -matrix[j][k];
			change1 = leastCommonMultiply(matrix[j][j], matrix[i][j]) / matrix[i][j];	
			change2 = leastCommonMultiply(matrix[j][j], matrix[i][j]) / matrix[j][j];
			for(k = 0;k < size + 1;k++)
				matrix[i][k] *= change1;
			for(k = 0;k < size + 1;k++)
				matrix[i][k] = matrix[i][k] - matrix[j][k] * change2;
		}
//	return matrix;
}

int leastCommonMultiply(int a, int b)/*��С������*/{
	int n = ((a > b)?a:b);
	
	for(;;n++)
		if(!(n % a) && !(n % b))
			break;
	return n; 
}

void outputSolution(int matrix[MAX][MAX + 1], int size){
	int i;

	for(i = 0;i < size;i++)
		printf("%.2f%c", (double)matrix[i][size] / matrix[i][i], (i == size - 1)?'\n':' ');
}