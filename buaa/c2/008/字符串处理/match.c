/*������������
���á�ͨ������������ü򵥵ķ������һ���ַ�����
ͨ���������������������һ�������ַ�����*������0�����������ַ������磺
AB?.txt���Ա�ʾAB1.txt��AB2.txt��ABa.txt �ȡ�
AB*.txt���Ա�ʾAB.txt�� AB1.txt��AB332.txt��ABaa.txt�ȡ�
��д�����ж�һ���ַ����Ƿ����һ������ͨ����Ĵ���
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�match.in��
��һ����һ����������ͨ�����������*���������߼��С�
������n��(3��n��10)��ÿ����һ������ͨ����Ĵ����鴮��
�����е����д���ֻ����Ӣ����ĸ����Сд���ɣ������֣������ո񣬳�����80�ַ����ڡ�
������EOF������
�������ʽ��
����ļ�Ϊ��ǰĿ¼�µ�match.out��
�����з��ϵĴ���ԭ˳�������ʾ������ļ��С�
������������
abcd?123*45*
abce123
abcda123456
abcda123
1234
abcda1234645

abcd?12*3*
abce123
abcda12345
abcda123
1234
�����������
abcda12345
abcda123
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {MAX = 10, LEN = 100};
void getResult(char *line[], FILE *out);
int isMatch(char *dst, char *src, int i, int j);
int lineNum = 0;
main()
{
	int i = 0;
	FILE *in, *out;
	char buf[LEN], *line[MAX];
	in = fopen("match.in", "r");
	//in = stdin;
	out = fopen("match.out", "w");
	//out = stdout;

	while(fgets(buf, LEN + 1, in) != NULL){
		buf[strlen(buf) - 1] = '\0';
		line[i] = (char *)malloc(strlen(buf));
		line[i] = strcpy(line[i], buf);
		i++;
	}
	lineNum = i;
	getResult(line, out);
	fclose(in);
	fclose(out);
}

void getResult(char *line[], FILE *out){
	int i;

	for(i = 1;i < lineNum;i++)
		if(isMatch(line[i], line[0], 0, 0))
			fprintf(out, "%s\n", line[i]);
}

int isMatch(char *dst, char *src, int i, int j){
	int k, flag;

	if(dst[i] == '\0' && src[j] == '\0')
		return 1;
	else if(dst[i] == '\0' && src[j] != '*')
		return 0;
	else if(src[j] == '?' || dst[i] == src[j])
		return isMatch(dst, src, i + 1, j + 1);
	else if(src[j] == '*'){
		k = 0;
		if(src[j + 1] == '\0')
			return 1;
		//if(dst[i + k] == '\0' && src[j + 1] == '\0')
		//	return 1;
		while(dst[i + k] != '\0'){
			if(dst[i + k] == src[j + 1] || src[j + 1] == '?' || src[j + 1] == '*'){
				flag = isMatch(dst, src, i + k, j + 1);
				if(flag)
					return 1;
			}
			k++;
		}
		//if(src[j + 1] == '*')
		//	return 1;
		//else
			return 0;
	}
	//else
		return 0;
	/*int i, j, k;

	for(i = 0;dst[i] != '\0' && src[i] != '\0';i++){
		if(src[i] == '*')
			for(k = 1;dst[i + k] != '\0';k++){
				if(dst[i + k] == src[i + 1]){
			}
		else if(src[i] != '?' && dst[i] != src[i])
			break;
	}
	
	return (dst[i] == '\0' && src[i] == '\0')?1:0;*/
}