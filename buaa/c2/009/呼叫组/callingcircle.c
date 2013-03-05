/*������������
һ���������顱�Ķ���Ϊ�����Aֱ�ӻ��Ӻ��й�B��ͬʱBҲֱ�ӻ��Ӻ��й�A����A��B����ͬһ�������顣
���磬A���й�B��B���й�C��C���й�A����ôA��B��Cͬ����һ�������飻�������������£�A���й�D��D���й�A��
��ôA��B��C��Dͬ����һ�������飻�������������£�A���й�E����Eû�к��й�A��B��C��D����һ������E��������������顣
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�callingcircle.in
�����ļ��ж��У���EOF������ÿһ��Ϊһ�����м�¼�����м�¼�����ظ���һ�����м�¼����������Ա���ƣ�����֮����һ�������հ׷��ָ���
���硰a b����ʾa���й�b����Ա����Ϊ���Ȳ�����25���ַ����ַ����������г��ֵĳ�Ա���Ʋ�����20����
�������ʽ��
����ļ�Ϊ��ǰĿ¼�µ�callingcircle.out
�����������������������ÿ��������ռһ�С�ÿ��������ĳ�Ա֮����1��Ӣ�Ķ��ż�1���ո��������, ���ָ���
ÿ���������Ա�������Ƶ�ASCII���������У���ͬ������֮�䰴�յ�һ����Ա���Ƶ�ASCII���������С����������ʽ�ο����������
����������1��
A B
B C
C A
A D
D E
E B
���������1��
A, B, C, D, E
����������2��
Ben  Alexander
Alexander  Dolly
Dolly    Ben
Dolly    Benedict
Benedict  Dolly
Alexander   Aaron
���������2��
Aaron
Alexander, Ben, Benedict, Dolly
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {MAX = 30, LINE = 200, LEN = 50};
typedef struct{
	char *name;
	int index;
}PERSON;
typedef struct{
	int member[MAX];
	int memberNum;
}GROUP;
int personNum = 0, groupNum = 0;
void getResult(PERSON person[], short matrix[][MAX], FILE *out);
void getCircle(GROUP group[], short matrix[][MAX]);
void matrixCopy(short matrix0[][MAX], short matrix[][MAX]);
void sort(GROUP group[], PERSON person[]);
void DFS(GROUP group[], short matrix[][MAX], short visited[], int vertex);
void output(GROUP group[], PERSON person[], FILE *out);
int addWord(char temp[], PERSON person[]);
int main()
{
	FILE *in, *out;
	PERSON person[MAX];
	char buf[LINE], *token, temp1[LEN], temp2[LEN];
	int i1, i2;
	short matrix[MAX][MAX] = {0};
	in = fopen("callingcircle.in", "r");
	out = fopen("callingcircle.out", "w");
	//in = fopen("callingcircle1.txt", "r");
	//out = fopen("callingcircle2.txt", "w");

	//i = 0;
	while(fgets(buf, LINE + 1, in) != NULL){
		token = strtok(buf, " \t\n");
		strcpy(temp1, token);
		token = strtok(NULL, " \t\n");
		strcpy(temp2, token);
		i1 = addWord(temp1, person);
		i2 = addWord(temp2, person);
		matrix[i1][i2] = 1;
	}
	//personNum = i;
	getResult(person, matrix, out);
	fclose(in);
	fclose(out);
}

void getResult(PERSON person[], short matrix[][MAX], FILE *out){
	int p, i, j, k, temp = 0;
	GROUP group[MAX] = {0};
	short matrixTemp1[MAX][MAX] = {0}, matrixTemp2[MAX][MAX] = {0}, matrixTemp3[MAX][MAX] = {0};
	matrixCopy(matrixTemp1, matrix);
	matrixCopy(matrixTemp2, matrix);
	for(p = 1;p < personNum;p++){
		for(i = 0;i < personNum;i++){
			for(j = 0;j < personNum;j++){
				for(k = 0;k < personNum;k++)
					matrixTemp3[i][j] += matrixTemp1[i][k] * matrixTemp2[k][j];
				if(matrixTemp3[i][j]){
					matrix[i][j] = 1;
				}
			}
		}
		matrixCopy(matrixTemp1, matrixTemp3);
	}
	/*for(i = 0;i < personNum;i++)
		for(j = i + 1;j < peronNum;j++){
			if(matrix[i][j] && matrix[j][i])
				for(k = 0;k < groupNum;k++)
					for(p = 0;p < group[k].memberNum;p++){
						 
					}
		}*/
	getCircle(group, matrix);
	sort(group, person);
	output(group, person, out);
}

void matrixCopy(short matrix0[][MAX], short matrix[][MAX]){
	int i, j;

	for(i = 0;i < personNum;i++)
		for(j = 0;j < personNum;j++)
			matrix0[i][j] = matrix[i][j];
}

void getCircle(GROUP group[], short matrix[][MAX]){
	short visited[MAX] = {0};
	int i;

	while(1){
		for(i = 0;i < personNum;i++)
			if(!visited[i])
				break;
		if(i == personNum)
			break;
		else{
			groupNum++;
			group[groupNum - 1].member[group[groupNum - 1].memberNum++] = i;
			DFS(group, matrix, visited, i);
		}
	}
}

void sort(GROUP group[], PERSON person[]){
	GROUP tempGroup;
	int i, j, k;
	int tempMember;


	for(k = 0;k < groupNum;k++){
		for(i = 0;i < group[k].memberNum - 1;i++){
			tempMember = group[k].member[i + 1];
			for(j = i + 1;j > 0 && strcmp(person[tempMember].name, person[group[k].member[j - 1]].name) < 0;j--)
				group[k].member[j] = group[k].member[j - 1];
			group[k].member[j] = tempMember;
		}
	}
	for(i = 0;i < groupNum - 1;i++){
		tempGroup = group[i + 1];
		for(j = i + 1;j > 0 && strcmp(person[tempGroup.member[0]].name, person[group[j - 1].member[0]].name) < 0;j--)
			group[j] = group[j - 1];
		group[j] = tempGroup;
	}
}

void output(GROUP group[], PERSON person[], FILE *out){
	int i, j;

	for(i = 0;i < groupNum;i++){
		for(j = 0;j < group[i].memberNum;j++){
			fprintf(out, "%s", person[group[i].member[j]].name);
			if(j == group[i].memberNum - 1)
				fprintf(out, "\n");
			else
				fprintf(out, ", ");
		}
	}
}

void DFS(GROUP group[], short matrix[][MAX], short visited[], int vertex){
	int i;
	
	visited[vertex] = 1;
	
	for(i = vertex + 1;i < personNum;i++){
		if(matrix[vertex][i] && matrix[i][vertex] && !visited[i]){
			group[groupNum - 1].member[group[groupNum - 1].memberNum++] = i;
			visited[i] = 0;
			DFS(group, matrix, visited, i);
		}
	}
	if(i == personNum)
		return;
}

int addWord(char temp[], PERSON person[]){
	int k;

	for(k = 0;k < personNum;k++)
		if(strcmp(temp, person[k].name) == 0)
			break;
	if(k == personNum){
		person[personNum].name = (char *)malloc(strlen(temp));
		person[personNum].name = strcpy(person[personNum].name, temp);
		person[personNum].index = personNum;
		personNum++;
	}
	return k;
}
