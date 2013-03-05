/*【问题描述】
已知有穷自动机的状态表，给定自动机的初始状态和输入序列，求该自动机的输出序列和最终状态。
【输入形式】
输入文件为当前目录下的dfa.in。
该文件分为三部分。第一部分是有穷自动机的状态表，有N+1行M+1列。第一行第一列固定为字符串”Q\\X”。
第一行的其余各列为M个可能的输入字符。第二行到第N+1行的第一列为字母和数字组成的串，分别表示自动机的N个状态，
其余各列表示自动机的转移函数和输出函数。第i行第j列的形式为’qk, z’，表示转移函数d(qi, xj)=qk和输出函数l(qi, xj)=z。
各列之间以一个或多个空格符分隔。输入文件的第二部分占一行，描述自动机的初始状态。第三部分占一行，
是一个由可能的输入字符xi组成的序列，各输入字符xi之间以一个或多个空格分隔。
【输出形式】
输出结果写到标准输出上。占两行，第一行是自动机的最终状态，第二行是自动机的输出序列，输出序列每个元素间用空格分隔。
【输入样例】
Q\\X    0     1
q2    q1,1  q3,0
q1    q2,1  q1,0
q3    q3,0  q1,1
q1
1 0 0 0 1 0 1
【输出样例】
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
