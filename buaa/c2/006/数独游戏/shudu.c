/*【输入形式】
输入文件为shudu.in。输入文件共9行，每行含9个数字，无分隔符。0表示待确定的空格。
【输出形式】
输出文件为shudu.out。输出共9行，每行9个数字，无分隔符。
【输入样例】
100006004
008090050
400300000
800002040
009605200
060700005
000007002
080030400
300200009
【样例输出】
193576824
628491753
457328961
835912647
719645238
264783195
946857312
582139476
371264589
【运行时限】
2秒
*/
#include<stdio.h>
enum {MAX = 9};
void scanMatrix(FILE *in, int matrix[][MAX][2]);
void getResult(FILE *out, int matrix[][MAX][2], int m, int n);
void printMatrix(FILE *out, int matrix[][MAX][2]);
//void setUsed(int matrix[][MAX][MAX], int i, int j, int n);
//void resetUsed(int matrix[][MAX][MAX], int i, int j, int n);
int res[MAX][MAX][2];
//int used[MAX][MAX][MAX] = {0};
int rowUsed[MAX][MAX] = {0};
int columnUsed[MAX][MAX] = {0};
int used[MAX][MAX] = {0};
int flag = 0;
main()
{
	FILE *in, *out;
	in = fopen("shudu.in", "r");
	out = fopen("shudu.out", "w");
	//in = stdin;
	//out = stdout;

	scanMatrix(in, res);
	getResult(out, res, 0, 0);
		
	fclose(in);
	fclose(out);
}

void scanMatrix(FILE *in, int matrix[][MAX][2]){
	int i, j;
	char c;

	for(i = 0;i < MAX;i++){
		for(j = 0;j < MAX;j++){
			c = fgetc(in);
			matrix[i][j][0] = (int)c - 48;
			matrix[i][j][1] = 0;
			if(matrix[i][j][0] > 0){
				//setUsed(used, i, j, matrix[i][j] - 1);
				matrix[i][j][1] = 1;
				columnUsed[i][matrix[i][j][0] - 1] = 1;
				rowUsed[j][matrix[i][j][0] - 1] = 1;
				used[i / 3 * 3 + j / 3][matrix[i][j][0] - 1] = 1;
			}
		}
		c = fgetc(in);
	}
}

/*void setUsed(int matrix[][MAX], int i, int n){
	int k;

	for(k = 0;k < MAX;k++)
		matrix[i][n] = 1;
}

void resetUsed(int matrix[][MAX], int i, int n){
	int k;

	for(k = 0;k < MAX;k++)
		matrix[i][k] = 0;
}
*/
void getResult(FILE *out, int matrix[][MAX][2], int m, int n){
	int i;
	if(flag)
		return;
	if(m == MAX){
		printMatrix(out, res);
		flag = 1;
		return;
	}
	for(i = 0;;i++){
		if(i == MAX)
			return;
		if(!matrix[m][n][0]){
			if(!rowUsed[n][i] && !columnUsed[m][i] && !used[m / 3 * 3 + n / 3][i]){
				matrix[m][n][0] = i + 1;
				//setUsed(used, m, n, i);
				//used[m][n][i] = 1;
				columnUsed[m][i] = 1;
				rowUsed[n][i] = 1;
				used[m / 3 * 3 + n / 3][i] = 1;
			}
			else
				continue;
		}
		if(n < MAX - 1)
			getResult(out, res, m, n + 1);
		else
			getResult(out, res, m + 1, 0);
		if(!matrix[m][n][1]){
			matrix[m][n][0] = 0;
			columnUsed[m][i] = 0;
			rowUsed[n][i] = 0;
			used[m / 3 * 3 + n / 3][i] = 0;
		}
		else
			return;
	}
	
}

void printMatrix(FILE *out, int matrix[][MAX][2]){
	int i, j;

	for(i = 0;i < MAX;i++){
		for(j = 0;j < MAX;j++)
			fprintf(out, "%d", matrix[i][j][0]);
		fputc('\n', out);
	}
}