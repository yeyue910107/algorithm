/*【问题描述】
已知线性方程组AX=B，求解该方程组。
参考算法：
消去法：将列向量B加到矩阵A的最后一列，构成增广矩阵AB。对AB进行下列三种初等变换，使原矩阵A的部分的主对角线上的元素均为1，
其余元素均为0，则原列向量B的部分即为X的值：
1.  将矩阵的一行乘以一个不为0的数
2.  将矩阵的一行加上另一行的倍数
3.  交换矩阵中两行的位置
【输入形式】
输入文件为当前目录下的equation.in。
该文件有N行(1≤N≤50)，每行有N + 1个整数，其中每行前N个数为矩阵A中的元素aij（-20≤aij≤20），
第N+1个数为列向量B中的元素bi（-200≤bi≤200）。
【输出形式】
结果输出到标准输出上。
输出占一行，包含N个数值，顺序为x1x2… …xN，保留两位小数。每两个数值之间用空格分隔。
【输入样例】
3 6 51
5 1 31
【输出样例】
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

void lineSimplify(int matrix[][MAX + 1], int size)/*矩阵的行简化*/{
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
	/*将每一行最简化*/
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

int leastCommonMultiply(int a, int b)/*最小公倍数*/{
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