/*������������
Morse����ʹ�����ֻ�����Ԫ����. ���͡�-��������Ӣ����ĸ�����Դ�Сд�������ֽ��б��롣�ڷ��͵籨ʱ�����Ա����ţ�
��һ���ϳ�ʱ���ͣ�ٱ�ʾһ�����ʵĽ�����
����ֻ���ǵ���֮��ı߽����������ĸ֮��ı߽磬��һ�������ġ�.���͡�-�����ź����п��Է���Ϊ������ʡ�
���������������ı��뷽���У��źš��������Է���Ϊ��EEE����Ҳ���Է���Ϊ��EI������IE�����ߡ�S����������������ƶ�һ���ֵ��
�涨�ڵ籨��������ֵ����е��ʼ��ϣ��ڷ���ʱ���ո��ֵ��Ϳ���ȷ�����ź�Ӧ��Ӧ�ĸ����ʡ�
������һЩ���ʿ��������롣���������Ǽٶ����ֻ�����ڵ���ĩβ����һ����������Ԫ������Ľض̣�������ĩβ��������˶������Ԫ��
�Ӷ������ֵ������û�а����ĵ��ʡ�
���������������26��Ӣ����ĸ��10�����ֵı�����������ֵ��Ȼ�����һƪMorse����ĵ籨���ڵ籨��һ����������Ԫ��ʾ��һ�����ʣ�
�������ڲ���ĸ�ı���û���κηָ����밴���¹��������ѵķ�������
1. ���һ��Morse�����Ӧ�ֵ����Ψһһ�����ʣ������ӡ��
2. ���һ��Morse������Է���Ϊ�ֵ���ж�����ʣ���ѡȡ�ֵ������̵ĵ��ʴ�ӡ�������Ȼ��Ӧ��������ĵ��ʣ�
���ӡ�ֵ�������ȳ��ֵ��Ǹ����ʣ��������ڸõ��ʺ��ӡһ���������ţ���ʾ���ڳ�ͻ����
3. ���һ��Morse�����޷�����Ϊ�ֵ���κε��ʣ���ñ��������롣��ʱӦѡȡ�ֵ�����ܹ�ƥ�����Morse����ǰ׺�ĵ��ʴ�ӡ
�������Ȼ��Ӧ��������ĵ��ʣ����ӡ�ֵ�������ȳ��ֵ��Ǹ����ʣ��������ڸõ��ʺ��ӡһ���������ţ���ʾ�������룩��
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�morse.in��
��һ����Ϊ�����ÿ�е�һ���ַ���һ����дӢ����ĸ�����֣�������һ�������ո񣬺�Ӹ���ĸ�����ֵ�Morse���롣
ÿ�����������6λ��Ԫ�������һ����һ����*������Ϊ�����Ľ�����
�ڶ�����Ϊ�ֵ��ÿ����һ�����ʣ�ÿ�������Ϊ10���ַ���������ֻ���ܺ��д�дӢ����ĸ�����֡��ֵ������ຬ��100�����ʡ�
�����һ����һ����*������Ϊ�ֵ��Ľ�����
ʣ�ಿ��Ϊ�籨���ġ�һ�������ġ�.���͡�-������һ�����ʣ�����֮�����������ո���з��ָ���ÿ��������ຬ��80����Ԫ��
�����һ����һ����*���ű�ʾ�籨������
�������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�morse.out��
��������д�ӡ���������е��ʡ�ÿ�о��ӵ�һ�п�ʼ��ӡ����������ո������һ��ĩҲҪ���һ���س�����
���������롿
�������ļ�morse.in���������£�
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
�����������
����ļ�morse.out���������£�
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