/*【问题描述】
Morse电码使用两种基本码元（’. ’和’-‘），对英文字母（忽略大小写）和数字进行编码。在发送电报时，忽略标点符号，
以一个较长时间的停顿表示一个单词的结束。
由于只考虑单词之间的边界而不考虑字母之间的边界，则一串连续的“.”和“-”的信号序列可以翻译为多个单词。
比如在样例给出的编码方案中，信号“…”可以翻译为“EEE”，也可以翻译为“EI”、“IE”或者“S”。因此我们事先制定一个字典表，
规定在电报中允许出现的所有单词集合，在翻译时对照该字典表就可以确定该信号应对应哪个单词。
但是有一些单词可能是误码。在这里我们假定误差只产生于单词末尾，即一串连续的码元被意外的截短，或者在末尾处被添加了多余的码元，
从而产生字典表中所没有包含的单词。
程序的任务是输入26个英文字母和10个数字的编码表，再输入字典表，然后读入一篇Morse编码的电报。在电报中一串连续的码元表示了一个单词，
而单词内部字母的编码没有任何分隔。请按如下规则给出最佳的翻译结果：
1. 如果一串Morse编码对应字典表中唯一一个单词，则将其打印；
2. 如果一串Morse编码可以翻译为字典表中多个单词，则选取字典表中最短的单词打印（如果仍然对应多个这样的单词，
则打印字典表中最先出现的那个单词），并且在该单词后打印一个“！”号（表示存在冲突）；
3. 如果一串Morse编码无法翻译为字典表任何单词，则该编码是误码。此时应选取字典表中能够匹配最长的Morse编码前缀的单词打印
（如果仍然对应多个这样的单词，则打印字典表中最先出现的那个单词），并且在该单词后打印一个“？”号（表示存在误码）。
【输入形式】
输入文件为当前目录下的morse.in。
第一部分为编码表。每行第一个字符是一个大写英文字母或数字，后面有一个或多个空格，后接该字母或数字的Morse编码。
每个编码最长含有6位码元。在最后一行有一个“*”号作为编码表的结束。
第二部分为字典表。每行有一个单词，每个单词最长为10个字符，单词中只可能含有大写英文字母和数字。字典表中最多含有100个单词。
在最后一行有一个“*”号作为字典表的结束。
剩余部分为电报报文。一串连续的“.”和“-”代表一个单词，单词之间以任意多个空格或换行符分隔。每个单词最多含有80个码元。
在最后一行有一个“*”号表示电报结束。
【输出形式】
输入文件为当前目录下的morse.out。
按规则分行打印翻译后的所有单词。每行均从第一列开始打印，不含多余空格。在最后一行末也要输出一个回车符。
【样例输入】
设输入文件morse.in的内容如下：
A    .-
B    -...
C    -.-.
D    -..
E    .
F    ...-.
G    --.
H    ....
I    ..
J    .---
K    -.-
L    .-..
M    --
N    -.
O    ---
P    .--.
Q    --.-
R    .-.
S    ...
T    -
U    ..-
V    ...-
W    .--
X    -..-
Y    -.--
Z    --..
0    ------
1    .-----
2    ..---
3    ...--
4    ....-
5    .....
6    -....
7    --...
8    ---..
9    ----.
*
AN
EARTHQUAKE
EAT
GOD
HATH
IM
READY
TO
WHAT
WROTH
*
.--.....--     .....--....
--.----..     .--.-.----..
.--.....--      .--.
..-.-.-....--.-..-.--.-.
..--     .-...--..-.--
----             ..--
*
【样例输出】
输出文件morse.out的内容如下：
WHAT
HATH
GOD
WROTH?
WHAT
AN
EARTHQUAKE
IM!
READY
TO
IM!
*/ 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
enum {LEN = 80, MAXCODE = 36, MAXDIC = 100, MAXTEXT = 1000};
typedef struct{
	char *code;
	char c;
}CODE;
void decode(char *dicTable[], char *dic[], CODE codeTable[], int dicNum);
void getResult(char *dicTable[], char *dic[], char *text[], int dicNum, int textNum, FILE *out);
int match(char *dic, char *text);
void insertSort(CODE codeTable[]);
main()
{
	FILE *in, *out;
	int i, flag = 0, dicNum = 0, textNum = 0, len;
	CODE codeTable[MAXCODE];
	char buf[LEN]/*, *codeTable[MAXCODE]*/, *dicTable[MAXDIC], *dic[MAXDIC], *text[MAXTEXT];
	//in = fopen("morse.in", "r");
	//out = fopen("morse.out", "w");
	in = fopen("morse1.txt", "r");
	out = fopen("morse2.txt", "w");

	i = 0;
	while(fscanf(in, "%s", buf) != EOF){
		if(buf[0] == '*'){
			flag++;
			i = 0;
			continue;
		}
		switch(flag){
		case 0:
			if(isalnum(buf[0])){
				codeTable[i].c = buf[0];
				continue;
			}
			codeTable[i].code = (char *)malloc(strlen(buf));
			codeTable[i].code = strcpy(codeTable[i].code, buf);
			//sscanf(buf, "%c%s", &c, temp);
			//codeTable[i] = (char *)malloc(strlen(buf));
			//codeTable[i] = strcpy(codeTable[i], buf);
			i++;
			break;
		case 1:
			//buf[strlen[buf] - 1] = '\0';
			len = strlen(buf);
			dicTable[i] = (char *)malloc(len);
			dic[i] = (char *)malloc(len * 6);
			dicTable[i] = strcpy(dicTable[i], buf);
			i++;
			dicNum++;
			break;
		case 2:
			text[i] = (char *)malloc(strlen(buf));
			text[i] = strcpy(text[i], buf);
			i++;
			textNum++;
			break;
		default:
			break;
		}
		
	}
	insertSort(codeTable);
	decode(dicTable, dic, codeTable, dicNum);
	getResult(dicTable, dic, text, dicNum, textNum, out);

	fclose(in);
	fclose(out);
}

void decode(char *dicTable[], char *dic[], CODE codeTable[], int dicNum){
	int i, j;

	for(i = 0;i < dicNum;i++){
		for(j = 0;dicTable[i][j] != '\0';j++){
			if(isupper(dicTable[i][j]))
				if(j == 0)
					dic[i] = strcpy(dic[i], codeTable[(int)(dicTable[i][j] - 65) + 10].code);
				else
					dic[i] = strcat(dic[i], codeTable[(int)(dicTable[i][j] - 65) + 10].code);
			else if(isdigit(dicTable[i][j]))
				if(j == 0)
					dic[i] = strcpy(dic[i], codeTable[(int)(dicTable[i][j] - 48)].code);
				else
					dic[i] = strcat(dic[i], codeTable[(int)(dicTable[i][j] - 48)].code);
		}
	}
}

void getResult(char *dicTable[], char *dic[], char *text[], int dicNum, int textNum, FILE *out){
	int i, j, min, max, rs, type, len, temp;

	for(i = 0;i < textNum;i++){
		min = 10000, max = -1, rs = 0, type = -1, len = 0, temp = 0;
		for(j = 0;j < dicNum;j++){
			rs = match(dic[j], text[i]);
			if(rs == -1){
				type = 0;
				len = strlen(dicTable[j]);
				if(min != 10000)
					type = 1;
				if(len < min){
					min = len;
					temp = j;
				}
			}
			else if(type == -1){
				//type = -1;
				len = rs;
				if(len > max){
					max = len;
					temp = j;
				}
			}
		}
		switch(type){
		case -1:
			if(max == 0)
				fprintf(out, "?\n");
			else
				fprintf(out, "%s%c\n", dicTable[temp], '?');
			break;
		case 0:
			fprintf(out, "%s\n", dicTable[temp]);
			break;
		case 1:
			fprintf(out, "%s%c\n", dicTable[temp], '!');
			break;
		}
	}
}

int match(char *dic, char *text){
	int i, j, k, max = 0;

	/*if(strcmp(dic, text) == 0)
		return -1;*/
	for(i = 0;dic[i] != '\0' && text[i] != '\0' && dic[i] == text[i];i++)
		;
	if(dic[i] == '\0' && text[i] == '\0')
		return -1;
	else //if(dic[i] == '\0')
		return i;
	//else
		//return 0;
	/*for(i = 0;dic[i] != '\0';i++){
		for(j = 0;text[j] != '\0' && dic[i + j] != '\0' && text[j] == dic[i + j];j++)
			;
		if(j > max)
			max = j;
	}
	return max;*/
}
void insertSort(CODE codeTable[]){
	int i, j;
	CODE temp;

	for(i = 0;i < MAXCODE - 1;i++){
		temp = codeTable[i + 1];
		for(j = i + 1;j > 0 && temp.c < codeTable[j - 1].c;j--)
			codeTable[j] = codeTable[j - 1];
		codeTable[j] = temp;
	}
}