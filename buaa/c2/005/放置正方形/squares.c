/*������������
��һ�����λ��ֳ�N*M�����ӣ�ÿ�������б�ռ�ú�δ��ռ�������������һ���߳�Ϊi�������η�������У�
Ҫ�������������в�������ռ�õĸ��ӣ��ʹ��ж����ֺ��ʵķ��÷�����
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�squares.in��
���ļ���һ����һ������i (1<i<=min(M,N))����ʾ�����εı߳���֮����N(1<=N <=1000)�У�
ÿ����M(1<=M<=1000)��0��1��1��ʾ�ø�δ��ռ�ã�0��ʾ�ø�ռ�ã���������EOF������
�������ʽ��
����ļ�Ϊ��ǰĿ¼�µ�squares.out��
���ļ�ֻ��һ�������������ʾ�߳�Ϊi���������ھ����к��ʵķ��÷�������
������������
2
1011
1111
1110
1110
�����������
5
������ʱ�ޡ�
2��
*/
/*#include<stdio.h>
enum {MAX = 2000};
void getNum(short square[][MAX], int coloum, int row, int n);
int COUNT = 0;
short record[MAX] = {0};
main()
{
	short square[MAX][MAX] = {0};
	int i, j, row, column, n;
	char c;
	FILE *in, *out;
	in = fopen("squares.in", "r");
	out = fopen("squares.out", "w");
	//in = stdin;
	//out = stdout;
	
	fscanf(in, "%d", &n);
	c = fgetc(in);
	c = fgetc(in);
	for(i = 0;c != EOF;i++){
		for(j = 0;c != '\n' && c != EOF;j++){
			if(c == '1' || c == '0')
				square[i][j] = (int)c - 48;
			c = fgetc(in);
		}
		if(c == EOF)
			break;
		c = fgetc(in);
	}
	column = i + 1;
	row = j;
	getNum(square, column, row, n);
	fprintf(out, "%d\n", COUNT);
	fclose(in);
	fclose(out);
}

void getNum(short square[][MAX], int column, int row, int n){
	int i, j, k;

	for(i = column - 1;i >= 0;i--)
		for(j = row - 1;j >= 0;j--){
			if(i == column - 1 || j == row - 1){
				if(square[i][j] >= n)
					COUNT++;
			}
			else if(square[i][j]){
				if(square[i + 1][j + 1] > 0){
					for(k = 1; k <= square[i + 1][j + 1] && i + k < column && j + k < row && square[i + k][j] > 0 && square[i][j + k] > 0;k++)
						;
					square[i][j] = k;
					if(square[i][j] >= n)
						COUNT++;
				}
				else if(square[i][j] >= n)
					COUNT++;
			}
		}
}*/
/*#include<stdio.h>
enum {MAX = 1001};
long getNum(char square[][MAX], short rightAndBelow[][MAX][2], int n, int row, int column);
//int isSquare(int square[][MAX], int i, int j, int n);
void getRightAndBelow(char square[][MAX], short rightAndBelow[][MAX][2], int row, int column);
main()
{
	char square[MAX][MAX] = {0};
	short rightAndBelow[MAX][MAX][2] = {0};
	//int below[MAX][MAX] = {0};
	int i, j, row, column, n;
	char c;
	FILE *in, *out;
	//FILE *test;
	in = fopen("squares.in", "r");
	out = fopen("squares.out", "w");
	//test = fopen("test.txt", "w");
	//in = fopen("test.txt", "r");
	//in = stdin;
	//out = stdout;
	
	/*for(i = 0;i < 20;i++){
		for(j = 0;j < 20;j++)
			fputc('1', test);
		fputc('\n', test);
	}*/
/*	fscanf(in, "%d", &n);
	//while(1){
		c = fgetc(in);
		c = fgetc(in);
		for(i = 0;c != EOF;i++){
			for(j = 0;c != '\n' && c != EOF;j++){
				if(c == '1' || c == '0')
					square[i][j] = c;
				c = fgetc(in);
			}
			if(c == EOF)
				break;
			c = fgetc(in);
		}
	//}
	column = i;
	row = j;
	getRightAndBelow(square, rightAndBelow, row, column);
	fprintf(out, "%d\n", getNum(square, rightAndBelow, n, row, column));
	fclose(in);
	fclose(out);
}

void getRightAndBelow(char square[][MAX], short rightAndBelow[][MAX][2], int row, int column){
	int i, j;
	
	if(square[column - 1][row - 1] == '1')
		rightAndBelow[column - 1][row - 1][0] = rightAndBelow[column - 1][row - 1][1] = 1;
	else
		rightAndBelow[column - 1][row - 1][0] = rightAndBelow[column - 1][row - 1][1] = 0;
	for(i = column - 1;i >=0;i--){
		for(j = row - 1;j >= 0;j--){
			if(i == column - 1)
				rightAndBelow[i][j][1] = (short)square[i][j] - 48;
			else{
				if(square[i][j] == '1'){
					if(rightAndBelow[i + 1][j][1])
						rightAndBelow[i][j][1] = rightAndBelow[i + 1][j][1] + 1;
					else
						rightAndBelow[i][j][1] = 1;
				}
				else
					rightAndBelow[i][j][1] = 0;
			}
			if(j == row - 1)
				rightAndBelow[i][j][0] = (short)square[i][j] - 48;
			else{
				if(square[i][j] == '1'){
					if(rightAndBelow[i][j + 1][0])
						rightAndBelow[i][j][0] = rightAndBelow[i][j + 1][0] + 1;
					else
						rightAndBelow[i][j][0] = 1;
				}
				else
					rightAndBelow[i][j][0] = 0;
			}
		}
	}
}

/*int getNum(int square[][MAX], int n, int row, int column){
	int i, j, count = 0;
	
	for(i = 0;i <= column - n;i++)
		for(j = 0;j <= row - n;j++){
			if(square[i][j] == 0)
				continue;
			if(isSquare(square, i, j, n))
				count++;
		}
	return count;
}

int isSquare(int square[][MAX], int i, int j, int n){
	int k1, k2;
	for(k1 = 0;k1 < n;k1++)
		for(k2 = 0;k2 < n;k2++)
			if(square[i + k1][j + k2] == 0)
				return 0;
	return 1;
}
*/
/*long getNum(char square[][MAX], short rightAndBelow[][MAX][2], int n, int row, int column){
	int i, j, k, i0, j0;
	long count = 0;
	
	for(i = 0;i <= column - n;i++)
		for(j = 0;j <= row - n;j++){
			i0 = i;j0 = j;
			for(k = n;(k > 0) && (rightAndBelow[i0][j0][1] >= k) && (rightAndBelow[i0][j0][0] >= k);k--){
				i0++;
				j0++;
			}
			if(k == 0)
				count = count + 1;
		}
	return count;
}*/

#include<stdio.h>
enum {MAX = 2001};
int getNum(short square[][MAX], int n, int row, int column);
//int isSquare(int square[][MAX], int i, int j, int n);
void getRecord(short square[][MAX], int row, int column);
main()
{
	short square[MAX][MAX] = {0};
	int i, j, row, column, n;
	char c;
	FILE *in, *out;
	in = fopen("squares.in", "r");
	out = fopen("squares.out", "w");
	//in = stdin;
	//out = stdout;

	fscanf(in, "%d", &n);
		c = fgetc(in);
		c = fgetc(in);
		for(i = 0;c != EOF;i++){
			for(j = 0;c != '\n' && c != EOF;j++){
				if(c == '1' || c == '0')
					square[i][j] = (int)c - 48;
				c = fgetc(in);
			}
			if(c == EOF)
				break;
			c = fgetc(in);
		}
	column = i + 1;
	row = j;
	getRecord(square, row, column);
	fprintf(out, "%d\n", getNum(square, n, row, column));
	fclose(in);
	fclose(out);
}

void getRecord(short square[][MAX], int row, int column){
	int i, j;
	
	for(i = column - 1;i >= 0;i--){
		for(j = row - 1;j >= 0;j--){
			if(i == column - 1 || j == row - 1)
				continue;
			else{
				if(square[i][j] == 1){
					square[i][j] = ((square[i + 1][j] > square[i][j + 1])?(square[i][j + 1]):(square[i + 1][j])) + 1;
				}
				else
					square[i][j] = 0;
			}
		}
	}
}

int getNum(short square[][MAX], int n, int row, int column){
	int i, j, k, i0, j0;
	int count = 0;
	
	for(i = 0;i <= column - n;i++)
		for(j = 0;j <= row - n;j++){
			i0 = i;j0 = j;
			for(k = n;k > 0 && square[i0][j0] >= k;k--){
				i0++;
				j0++;
			}
			if(k == 0)
				count++;
		}
	return count;
}