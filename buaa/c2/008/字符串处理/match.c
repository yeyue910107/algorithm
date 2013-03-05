/*【问题描述】
利用“通配符”，可以用简单的方法标记一组字符串。
通配符有两个：“？”代表一个任意字符，“*”代表0个或多个任意字符。例如：
AB?.txt可以表示AB1.txt，AB2.txt，ABa.txt 等。
AB*.txt可以表示AB.txt， AB1.txt，AB332.txt，ABaa.txt等。
编写程序，判断一个字符串是否符合一个含有通配符的串。
【输入形式】
输入文件为当前目录下的match.in。
第一行是一个串，含有通配符“？”或“*”，或两者兼有。
后面有n行(3≤n≤10)，每行有一个不含通配符的待检验串。
输入中的所有串均只包含英文字母（大小写均可）和数字，不含空格，长度在80字符以内。
输入以EOF结束。
【输出形式】
输出文件为当前目录下的match.out。
将所有符合的串按原顺序分行显示在输出文件中。
【输入样例】
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
【输出样例】
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