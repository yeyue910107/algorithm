/*【问题描述】
正文中只含有英文字母和分隔符，分隔符只包括空格、逗号（,）、句号（.）和换行符。
一个句子的内容从开头（或上一个句号后）的第一个非空字符开始到下一个句号前的最后一个非空字符截至。  
统计正文中指定英文单词出现的句子的数目，并输出包含该单词的所有句子。不区分大小写，例如，ABC、AbC、ABc、aBC、abc…视为同一单词。
【输入形式】
输入文件为当前目录下的check.in
输入文件分为两部分。第一部分是一个正文串，长度任意，由连续3个换行符（空两行）和单占一行的字符串_END_结束。
第二部分包含N（0<N<20）行，每行为一个要统计的单词。
【输出形式】
输出文件为当前目录下的check.out。
输出文件分为N部分，每部分的第一行对应输入文件中第二部分的每一行输出，为要统计的单词、其出现次数及一个换行符，
单词及其出现次数之间以一个空格分隔；每部分其余行按字典序输出包含该单词的所有句子的内容，当一个单词在同一个句子中多次出现时，
该句子的内容只输出一次。
【输入样例】
Every computer will have MsDos, Borland C Microsoft Quick Basic. And Turbo Pascal. Each student will have the opportunity for some practice. On the equipment.


_END_
will
on
【输出样例】
will 2
Each student will have the opportunity   for some practice
Every computer will have MsDos, Borland C Microsoft Quick Basic
on 1
On the equipment
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
enum {MAXLINE = 20, MAXSEN = 200, MAXWORD = 800, LEN = 20, LINE = 300};
typedef struct{
	char *name;
	int times;
	int index[MAXSEN], indexNum;
}WORD;
typedef struct{
	char *name;
	int index;
}SEN;
int senNum = 0, wordNum = 0;
void senSort(SEN sen[]);
void setWord(WORD word[], SEN sen[]);
void getResult(char *buf, WORD word[], SEN sen[], FILE *out);
void stringToLower(char *str);
void dealSen(char *sen);
int main()
{
	FILE *in, *out;
	SEN sen[MAXSEN];
	char *token, *ctoken;
	WORD word[MAXWORD] = {"", 0, 0, 0};
	char buf[LINE], text[MAXLINE * LINE], *temp;
	int flag = 0, i = 0, k = 0, count = 0;
	in = fopen("check.in", "r");
	out = fopen("check.out", "w");
	//in = fopen("check1.txt", "r");
	//out = fopen("check2.txt", "w");
	
	text[0] = '\0';
	while(fgets(buf, LINE + 1, in) != NULL){
		if(buf[0] == '\n'){
			count++;
			continue;
		}
		if(count >= 2 && strcmp(buf, "_END_\n") == 0){
			break;
			//flag = 1;
			//senSort(sen);
			//setWord(word, sen);
			//continue;
		}
		buf[strlen(buf) - 1] = '\0';
		strcat(text, buf);
		if(count < 2)
			count = 0;
	}
		//if(!flag){
	//ptoken = strtok(text, "\n");
		//while(ptoken){
			token = strtok(text, ".");
			while(token){
				//temp = (char *)malloc(strlen(token));
				//temp = strcpy(temp, token);
				sen[i].name = (char *)malloc(strlen(token));
				sen[i].name = strcpy(sen[i].name, token);
		//		sen[i].index = k;
				while(isspace(*(sen[i].name)))
					sen[i].name++;
				dealSen(sen[i].name);
				//while(isspace(*(temp)))
				//	temp++;
				//dealSen(temp);
				//for(k = 0;k < senNum;k++){
					//if(strcmp(temp, sen[k].name) == 0){
					//	token = strtok(NULL, ".");
					//	break;
					//}
				//}
				//if(k == senNum){
					//sen[senNum].name = (char *)malloc(strlen(token));
					//sen[senNum].name = strcpy(sen[senNum].name, token);
					i++;
					senNum++;
					token = strtok(NULL, ".");
			//	}
				//strcmp(temp, sen[i].name);
		
				//temp[0] = '\0';
				//ctoken = strtok(sen[i].name, "\n");
			//	while(ctoken){
				//	strcat(temp, ctoken);
				//	ctoken = strtok(NULL, "\n");
				//}		
			//	strcpy(sen[i].name, temp);
				//sen[i] = strcpy(sen[])
			//	word = addWord(sen[i], word);
				//i++;
				
			}
		//	ptoken = strtok(NULL, "\n");
		//	k++;
		//}
			senSort(sen);
			setWord(word, sen);
		//}
		//else{
			while(fgets(buf, LINE + 1, in) != NULL){
			buf[strlen(buf) - 1] = '\0';
			getResult(buf, word, sen, out);
		}
	//	k++;
	//}

	fclose(in);
	fclose(out);
}

void senSort(SEN sen[]){
	int i, j;
	SEN temp;

	for(i = 0;i < senNum - 1;i++){
		temp = sen[i + 1];
		for(j = i + 1;j > 0 && strcmp(temp.name, sen[j - 1].name) < 0;j--)
			sen[j] = sen[j - 1];
		sen[j] = temp;
	}
}

void setWord(WORD word[], SEN sen[]){
	int i, j, k, flag;
	char *token, *temp;
	
	temp = (char *)malloc(LINE);
	for(i = 0;i < senNum;i++){
		temp = strcpy(temp, sen[i].name);
		token = strtok(temp, " ,.\n");
		//flag = 0;
		while(token){
			stringToLower(token);
			for(j = 0;j < wordNum;j++){
				if(strcmp(token, word[j].name) == 0){
					
		//			for(k = 0;k < word[j].indexNum && sen[word[j].index[k]].index != sen[i].index;k++)
		//				;
		//			if(k == word[j].indexNum)
					//if(flag == 0){
						
						//flag = 1;
					//}
					if(word[j].index[word[j].indexNum - 1] != i){
						word[j].times++;
						word[j].index[word[j].indexNum++] = i;
					}
					break;
				}
			}
			if(j == wordNum){
				word[j].name = (char *)malloc(strlen(token));
				word[j].name = strcpy(word[j].name, token);
				stringToLower(word[j].name);
				word[j].times = 1;
				word[j].indexNum = 1;
				word[j].index[0] = i;
				wordNum++;
			}
			token = strtok(NULL, " ,.\n");
		}
	}
}

void getResult(char *buf, WORD word[], SEN sen[], FILE *out){
	int i, j;
	char *temp;

	temp = (char *)malloc(strlen(buf));
	temp = strcpy(temp, buf);
	stringToLower(temp);
	for(i = 0;i < wordNum;i++){
		if(strcmp(temp, word[i].name) == 0){
			fprintf(out, "%s %d\n", buf, word[i].times);
			for(j = 0;j < word[i].indexNum;j++)
				fprintf(out, "%s\n", sen[word[i].index[j]].name);
			break;
		}
	}
	if(i == wordNum)
		fprintf(out, "%s %d\n", buf, 0);
}

void stringToLower(char *str){
	int i;

	for(i = 0;str[i] != '\0';i++)
		if(isupper(str[i]))
			str[i] = tolower(str[i]);
}

void dealSen(char *sen){
	int i, j;

	for(i = 0;sen[i] != '\0';i++){
		if(sen[i] == '\n')
			for(j = i;sen[j] != '\0';j++)
				sen[j] = sen[j + 1];
	}
	i--;
	for(;isspace(sen[i]);i--)
		;
	sen[i + 1] = '\0';
}