/*������������
���������ַ���s��t��s��t���Ժ��ո�length(t)��length(s)��50������s�����״���tƥ����Ӵ����ã�����������s�������
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�invertsub.in��
�ļ����������ַ���s��t���ֱ��Ի��з���Ϊ�����������л��з�������Linux�µĻ��з���Ҳ������Windows�µĻ��з���
�������ʽ��
����ļ�Ϊ��ǰĿ¼�µ�invertsub.out��
����ļ�ֻ��һ�У�����һ������ΪҪ�������������ĩҪ���һ���س����� 
������������
helloworld
llowor
�����������
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

