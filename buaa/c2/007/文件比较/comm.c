/*【问题描述】
对两个按字典序排列的有序文件file1和file2的内容进行比较，生成三列输出：仅在file1中出现的行，仅在file2中出现的行，
在两个文件中都存在的行，并将输出按字典序排列。
【输入形式】
输入文件为当前目录下的comm.in。
该文件中有两行，每行存有一个文件名。第一行为file1名称，第二行为file2名称。对两个文件的内容进行比较。
每个文件的内容不超过50行，且按字典序排列。
【输出形式】
输出文件为当前目录下的comm.out。
该文件按字典序排列，第一列为仅在file1中出现的行，第二列为仅在file2中出现的行，第三列为两个文件中都存在的行，第一列输出到行首，
各列之间用Tab键“\t”分隔。
【输入样例】
comm.in的内容如下：
comm_1.in
comm_2.in

comm_1.in的内容如下：
1
2
3
4
i
This is a test, test, test, test, test, test, test

comm_2.in的内容如下：
1
2
3
5
6
This is a test, test, test, test, test, test
【输出样例】
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