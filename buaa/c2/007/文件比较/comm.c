/*������������
���������ֵ������е������ļ�file1��file2�����ݽ��бȽϣ������������������file1�г��ֵ��У�����file2�г��ֵ��У�
�������ļ��ж����ڵ��У�����������ֵ������С�
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�comm.in��
���ļ��������У�ÿ�д���һ���ļ�������һ��Ϊfile1���ƣ��ڶ���Ϊfile2���ơ��������ļ������ݽ��бȽϡ�
ÿ���ļ������ݲ�����50�У��Ұ��ֵ������С�
�������ʽ��
����ļ�Ϊ��ǰĿ¼�µ�comm.out��
���ļ����ֵ������У���һ��Ϊ����file1�г��ֵ��У��ڶ���Ϊ����file2�г��ֵ��У�������Ϊ�����ļ��ж����ڵ��У���һ����������ף�
����֮����Tab����\t���ָ���
������������
comm.in���������£�
comm_1.in
comm_2.in

comm_1.in���������£�
1
2
3
4
i
This is a test, test, test, test, test, test, test

comm_2.in���������£�
1
2
3
5
6
This is a test, test, test, test, test, test
�����������
		1
		2
		3
4
	5
	6
i
	This is a test, test, test, test, test, test
This is a test, test, test, test, test, test, test
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {MAX = 50, LEN = 80};
int inputText(FILE *file, char *text[]);
void getResult(char *text1[], char *text[], int line1, int line2, FILE *out);
main()
{
	FILE *in, *out, *file1, *file2;
	char file[LEN];
	char *text1[MAX], *text2[MAX];
	int line1, line2;

	in = fopen("comm.in", "r");
	out = fopen("comm.out", "w");
	//in = fopen("commin.txt", "r");
	//out = fopen("commout.txt", "w");
	fscanf(in, "%s", file);
	file1 = fopen(file, "r");
	fscanf(in, "%s", file);
	file2 = fopen(file, "r");
	line1 = inputText(file1, text1);
	line2 = inputText(file2, text2);
	getResult(text1, text2, line1, line2, out);

	fclose(in);
	fclose(out);
	fclose(file1);
	fclose(file2);
}

int inputText(FILE *file, char *text[]){
	int i = 0, line;
	char buf[LEN];

	while(fgets(buf, LEN + 1, file) != NULL){
		text[i] = (char *)malloc(strlen(buf) + 1);
		text[i] = strcpy(text[i], buf);
		i++;
	}
	line = i;

	return line;
}

void getResult(char *text1[], char *text2[], int line1, int line2, FILE *out){
	int i = 0, j = 0;

	while(i < line1 && j < line2){
		if(strcmp(text1[i], text2[j]) < 0)
			fprintf(out, "%s", text1[i++]);
		else if(strcmp(text1[i], text2[j]) > 0)
			fprintf(out, "\t%s", text2[j++]);
		else{
			fprintf(out, "\t\t%s", text1[i++]);
			j++;
		}
	}
	while(i < line1){
		fprintf(out, "%s", text1[i++]);
	}
	while(j < line2)
		fprintf(out, "\t%s", text2[j++]);
}