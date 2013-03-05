/*������������
ͳ�������ļ���ָ��Ӣ�ĵ��ʳ��ֵĴ����ĺ͡�
������ĸ��д�Ĵ�Ӧ������ĸ�Ǵ�д�Ĵ���Ϊͬһ���ʡ����磬��The����ͬ�ڡ�the���������Сд��һ�µĴ�Ӧ��Ϊ��ͬ�Ĵʡ�
���磬��ADA������ͬ�ڡ�Ada�������ʸ����������˳Ƶ����ȵ��ʱ���Ӧ��Ϊ��ͬ�ĵ��ʡ������ڵķ������ַ���-������д��������
�����������֮�У����ʺ����д����.������U.S.�е���������д��������������֮�С�
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�frequency.in��
���ļ���Ϊ�����֡���һ������һ����Ӣ�ĵ��ʡ����ֺͱ�㡢�Լ��ո���ͻ��з���ɵ����Ĵ���������4�����з���������3�У���
�ڶ����ְ��������У�ÿ�е���ʽ���£�
<����1>+<����2> �� <����n>
ÿ���е��ʵĸ���С�ڵ���100�������롮����֮����0�������ո���ָ������ⵥ��_PUNCT_��ʾ���������б����š�
�������ʽ��
������д�ڱ�׼����ϡ�
�����ļ��еڶ����ֵ�ÿһ�ж�Ӧ����ļ���һ�У�Ϊһ��������һ�����з�������Ϊ��Ӧ�������и������ʳ��ִ���֮�͡�
������������
This is a book.
It is my book.



this + is + a+book
is+my
�����������
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