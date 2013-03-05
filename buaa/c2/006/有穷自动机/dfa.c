/*������������
��֪�����Զ�����״̬�������Զ����ĳ�ʼ״̬���������У�����Զ�����������к�����״̬��
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�dfa.in��
���ļ���Ϊ�����֡���һ�����������Զ�����״̬����N+1��M+1�С���һ�е�һ�й̶�Ϊ�ַ�����Q\\X����
��һ�е��������ΪM�����ܵ������ַ����ڶ��е���N+1�еĵ�һ��Ϊ��ĸ��������ɵĴ����ֱ��ʾ�Զ�����N��״̬��
������б�ʾ�Զ�����ת�ƺ����������������i�е�j�е���ʽΪ��qk, z������ʾת�ƺ���d(qi, xj)=qk���������l(qi, xj)=z��
����֮����һ�������ո���ָ��������ļ��ĵڶ�����ռһ�У������Զ����ĳ�ʼ״̬����������ռһ�У�
��һ���ɿ��ܵ������ַ�xi��ɵ����У��������ַ�xi֮����һ�������ո�ָ���
�������ʽ��
������д����׼����ϡ�ռ���У���һ�����Զ���������״̬���ڶ������Զ�����������У��������ÿ��Ԫ�ؼ��ÿո�ָ���
������������
Q\\X    0     1
q2    q1,1  q3,0
q1    q2,1  q1,0
q3    q3,0  q1,1
q1
1 0 0 0 1 0 1
�����������
q1
0 1 1 1 0 0 1
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {LEN = 10, MAX = 500};
typedef struct{
	char next[LEN];
	int nextNum;
	char outStr[LEN];
	//int inCharNum, stateNum;
}FUN;
typedef struct{
	FUN fun[MAX];
	char stateStr[LEN];
}STATE;
void input(FILE *in, STATE state[], char *initState, char *inArray[], char *inChar[]);
void setState(STATE state[]);
void getResult(STATE state[],  char *initState, char *inArray[], char *inChar[], char *outArray);
int index0(char *str, char *inChar[]);
int inCharNum = 0, stateNum = 0, inArrayNum = 0;
main()
{
	FILE *in;
	STATE state[MAX] = {0};
	char initState[LEN], *inArray[MAX], *inChar[MAX], outArray[MAX];
	in = fopen("dfa.in", "r");
	//in = fopen("dfa.txt", "r");
	//in = stdin;
	
	input(in, state, initState, inArray, inChar);
	setState(state);
	getResult(state, initState, inArray, inChar, outArray);
	fclose(in);
}

void input(FILE *in, STATE state[], char *initState, char *inArray[], char *inChar[]){
	int i, k, j, p;
	char c, buf[LEN];

	fscanf(in, "%s", buf);
	i = 0;
	while(1){
		inChar[i] = (char *)malloc(LEN);
		fscanf(in, "%s", inChar[i++]);
		if((c = fgetc(in)) == '\n')
			break;
	}
	inCharNum = i;
	i = 0;
	while(1){
		fscanf(in, "%s", state[i].stateStr);
		if((c = fgetc(in)) == '\n')
			break;
		//state[i].stateStr = strcpy(state[i].stateStr, buf);
		k = 0;
		while(k < inCharNum){
			fscanf(in, "%s", buf);
			j = 0;p = 0;
			//while(buf[j] != '\0'){
				while(buf[j] != ','){
					state[i].fun[k].next[p] = buf[j];
					p++;j++;
				}
				state[i].fun[k].next[p] = '\0';
				//fscanf(in, "%s%c%s", state[i].fun[k].next, &temp, state[i].fun[k].outStr);
				//j++;
				p = 0;
				j++;
				while(buf[j] != '\0'){
					state[i].fun[k].outStr[p] = buf[j];
					p++;j++;
				}
				state[i].fun[k].outStr[p] = '\0';
			//}
			k++;
		}
		i++;
	}
	initState = strcpy(initState, state[i].stateStr);
	stateNum = i;
	i = 0;
	while(1){
		inArray[i] = (char *)malloc(LEN);
		fscanf(in, "%s", inArray[i++]);
		c = fgetc(in);
		if(c == '\n' || c == EOF)
			break;
	}
	inArrayNum = i;
	//fscanf(in, "%s", inArray);
}

void setState(STATE state[]){
	int i, j, k;

	for(i = 0;i < stateNum;i++){
		for(j = 0;j < inCharNum;j++){
			for(k = 0;k < stateNum;k++){
				if(strcmp(state[i].fun[j].next, state[k].stateStr) == 0){
					state[i].fun[j].nextNum = k;
					break;
				}
			}
		}
	}
}

void getResult(STATE state[],  char *initState, char *inArray[], char *inChar[], char *outArray){
	int i, curState, nextState, temp;
	for(i = 0;i < stateNum;i++){
		if(strcmp(initState, state[i].stateStr) == 0){
			curState = i;
			break;
		}
	}
	outArray[0] = '\0';
	for(i = 0;i < inArrayNum;i++){
		temp = index0(inArray[i], inChar);
		nextState = state[curState].fun[temp].nextNum;
		//outArray[i] = state[curState].fun[temp].
		outArray = strcat(outArray, state[curState].fun[temp].outStr);
		if(i == inArrayNum - 1)
			outArray = strcat(outArray, "\n");
		else
			outArray = strcat(outArray, " ");
		curState = nextState;
	}
	printf("%s\n%s", state[curState].stateStr, outArray);
}

int index0(char *str, char *inChar[]){
	int i;

	for(i = 0;i < inCharNum;i++){
		if(strcmp(str, inChar[i]) == 0)
			return i;
	}
	return 0;
}
