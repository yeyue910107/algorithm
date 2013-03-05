/*【问题描述】
输入两行字符串s和t（s和t可以含空格，length(t)≤length(s)≤50），将s串中首次与t匹配的子串逆置，并将处理后的s串输出。
【输入形式】
输入文件为当前目录下的invertsub.in。
文件中有两行字符串s和t，分别以换行符作为结束符，其中换行符可能是Linux下的换行符，也可能是Windows下的换行符。
【输出形式】
输出文件为当前目录下的invertsub.out。
输出文件只有一行，包含一个串，为要求的输出结果。行末要输出一个回车符。 
【输入样例】
helloworld
llowor
【输出样例】
herowollld
*/
#include<stdio.h>
#include<string.h>
enum {MAX = 50};
int index1(char s[], char t[])
{
	int i, j;

	for(i = 0;i < strlen(s) - 1;i++){
		for(j = 0;j < strlen(t) - 1 && t[j] == s[i];j++)
			i++;
		if(j == strlen(t) - 1)
			return (i - strlen(t) + 1);
		else continue;
	}
	return -1;
}
main()
{
	char s[MAX], t[MAX];
	int i, j, k, position, sLength, tLength;
	FILE *in, *out;

	in=fopen("invertsub.in","r");
	out=fopen("invertsub.out","w");
	//in = stdin;
	//out = stdout;
	fgets(s, MAX + 1, in);
	fgets(t, MAX + 1, in);
	sLength = strlen(s);
	tLength = strlen(t);
	position = index1(s, t);
	if(position == -1)
		fputs(s, out);
	else{
		for(i = 0;i < position;i++)
			fputc(s[i], out);
		for(j = strlen(t) - 2;j >= 0;j--)
			fputc(t[j], out);
		for(i = strlen(t) + position - 1;i < strlen(s);i++)
			fputc(s[i], out);
	}
	fclose(in);
	fclose(out);
}

