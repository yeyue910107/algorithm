/*【问题描述】
统计正文文件中指定英文单词出现的次数的和。
仅首字母大写的词应与首字母非大写的词视为同一个词。例如，“The”等同于“the”。其余大小写不一致的词应视为不同的词。
例如，“ADA”不等同于“Ada”。名词复数、第三人称单数等单词变形应视为不同的单词。单词内的符号连字符“-”、缩写符“’”
不计入标点符号之列，单词后的缩写符“.”，如U.S.中的两个后缩写符，则计入标点符号之列。
【输入形式】
输入文件为当前目录下的frequency.in。
该文件分为两部分。第一部分是一个由英文单词、数字和标点、以及空格符和换行符组成的正文串，由连续4个换行符结束（空3行）。
第二部分包含若干行，每行的形式如下：
<单词1>+<单词2> … <单词n>
每行中单词的个数小于等于100，单词与‘＋’之间由0个或多个空格符分隔。特殊单词_PUNCT_表示正文中所有标点符号。
【输出形式】
输出结果写在标准输出上。
输入文件中第二部分的每一行对应输出文件的一行，为一个整数和一个换行符，整数为对应输入行中各个单词出现次数之和。
【输入样例】
This is a book.
It is my book.



this + is + a+book
is+my
【输出样例】
6
3
*/
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
enum {MAX = 500, LINE = 1024, LEN = 50};
int recordNum = 1;
typedef struct{
	char *word;
	int times;
}WORD;
void reRecord(char *buf, WORD record[]);
void count(char *buf, WORD record[]);
//int isEqual(char *str1, char *str2);
main()
{
	FILE *in;
	WORD record[MAX];
	int i, flag = 0;
	char buf[LINE];
	in = fopen("frequency.in", "r");
	//in = fopen("frequency.txt", "r");
	//in = stdin;
	record[0].word = (char *)malloc(LEN);
	record[0].word = strcpy(record[0].word, "_PUNCT_");
	record[0].times = 0;
	while(fgets(buf, LINE + 1, in) != NULL){
		if(buf[0] == '\n'){
			flag++;
			//continue;
		}
		else if(flag == 3)
			count(buf, record);
		else
			reRecord(buf, record);
	}
	//i = 0;
	//while(fgets(buf, LINE + 1, in) != NULL)
		//count(buf, record);//k = i;
	//for(i = 0;i < k;i++)
		//printf("%d\n", rs[i]);
	fclose(in);	
}

void reRecord(char *buf, WORD record[]){
	int i = 0, j, k, flag = 0;
	char word[LEN];

	while(buf[i] != '\0'){
		k = 0;
		if(ispunct(buf[i]) && buf[i] != '-' && buf[i] != '\'')
			record[0].times++;
		//i++;
		else if(isalnum(buf[i]) || buf[i] == '-' || buf[i] == '\''){
			if(isalpha(buf[i]))
				buf[i] = tolower(buf[i]);
			while(isalnum(buf[i]) || buf[i] == '-' || buf[i] == '\'')
				word[k++] = buf[i++];
			i--;
			word[k] = '\0';
			if(ispunct(word[0]) && word[0] != '-' && word[0] != '\''){
				record[0].times++;
				i++;
				continue;
			}
			j = 0;
			while(j < recordNum){
				if(strcmp(word, record[j].word) == 0){
					record[j].times++;
					break;
				}
				j++;
			}
			if(j == recordNum){
				record[j].word = (char *)malloc(strlen(word));
				record[j].word = strcpy(record[j].word, word);
				record[j].times = 1;
				recordNum++;
			}
		}
		i++;
		//if(ispunct(buf[i]) && buf[i] != '-' && buf[i] != '\'')
		//	record[0].times++;
	}
}

void count(char *buf, WORD record[]){
	int i = 0, j, k, n = 0;
	char word[LEN];
	/*for(i = 0;i < num;i++)
		if(isEqual(line, word[i]))
			n++;
	return n;*/
	while(buf[i] != '\0'){
		if(isalnum(buf[i]) || buf[i] == '_' || buf[i] == '-' || buf[i] == '\''){
			k = 0;
			if(isalpha(buf[i]))
				buf[i] = tolower(buf[i]);
			while(isalnum(buf[i]) || buf[i] == '_' || buf[i] == '-' || buf[i] == '\'')
				word[k++] = buf[i++];
			i--;
			word[k] = '\0';
			j = 0;
			while(j < recordNum){
				if(strcmp(word, record[j].word) == 0){
					n += record[j].times;
					break;
				}
				j++;
			}
		}
		i++;
	}

	printf("%d\n", n);
}

/*int isEqual(char *str1, char *str2){
	int i = 0;

	while(str1[i] != '\0' && str2[i] != '\0' && tolower(str1[i]) == tolower(str2[i]))
		i++;
	if(str1[i] == '\0' && str2[i] == '\0')
		return 1;
	else
		return 0;
}*/