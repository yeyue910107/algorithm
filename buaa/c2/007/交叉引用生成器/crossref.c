/*������������
��������������������cross-refrencer����ָ�������¹��ܵĳ���
�������һƪ�ĵ���ͳ�Ƴ��ֵ����е��ʼ��������кš��������Թ涨��ʽ��ӡ��
��������ʽ��
����ӱ�׼�����϶���һƪ�ĵ���
���ĵ�����������ɣ�ÿ���а���һϵ�е��ʡ����б�ʾ����������к���1��ʼ���������ĵ��е�������������500��
ÿ�����ʳ�����󲻳���20���ַ���
�������ʽ��
�ڱ�׼����ϴ�ӡ�ĵ������г��ֵĵ��ʼ��������кš�
����������У�ÿһ�ж����ĵ��г��ֵ�һ�����ʡ������¹������� 
word:line1,line2, �� ,lineN
����word�ǵ��ʣ��������һ��ð�ţ�Ȼ�����Զ��Ÿ����ĳ����к�line1��line2���ȵȡ��ڸ����ϸ��ַ������������ʹ�ÿո�ָ���
�����ʱ��ѭ���¹涨��
1.ֻ���������Ӣ����ĸ���������ַ������ɵĵ��ʣ����ֻ�������������ַ��ĵ��ʲ���������������дA?Z��ͷ���ַ���
�����Сдa?z��ͷ�ķ���
2.�����ʺ�����кŴ�С�������С��кŲ��ظ���ӡ���༴���һ��������һ���ڶ�γ��֣���ֻ��ӡһ�θ��кš�
3.ͳ�Ƶĵ��ʲ������ڴʡ����ʵ���ʵ������ĵ��ʡ��ڱ������漰�����ĸ����ʣ�
1.a
2.an
3.the
4.and
������������
Alcatel provides end-to-end solutions.
It enables enterprises to deliver content to any type of user.
lcatel operates in 130 countries.
Alcatel focus on optimizing their service offerings and revenue streams.
�����������
Alcatel:1,4
It:2
any:2
content:2
countries:3
deliver:2
enables:2
end-to-end:1
enterprises:2
focus:4
in:3
lcatel:3
of:2
offerings:4
on:4
operates:3
optimizing:4
provides:1
revenue:4
service:4
solutions:1
streams:4
their:4
to:2
type:2
user:2
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
enum {MAXLEN = 20,MAXWORD = 500,MAXLINE = 100};
int NLINE = 1;
FILE *IN, *OUT;
struct tnode{
	char *word;
	int line[MAXLINE];/*��¼����������*/
	int n;/*��¼����������±�*/
	struct tnode *left;/*��ֲ�*/
	struct tnode *right;/*�ҷֲ�*/
};
int issame(char *p,char *q);
int judge(char *p);
/*char *strdup(char *s);*/
struct tnode *addtree(char *s,struct tnode *p);
void printtree(struct tnode *p);
main()
{
	struct tnode *root;
	char buf[MAXLEN];
	int k, k1 , c, flag = 0;

	//IN = fopen("crossin.txt","r");
	//OUT = fopen("crossout.txt","w");
	IN = stdin;
	OUT = stdout;
	root = NULL;
	while(/*(c = fgetc(IN)) != EOF*/1){
		c = fgetc(IN);
		if(c == '\n'){
			if(flag)
				break;
			NLINE++;
			flag = 1;
			continue;
		}
		flag = 0;
		k = 0;
		while(isalnum(c) || c == '-'){/*��ȡһ���ַ���*/
			buf[k] = c;
			k++;
			//buf[k] = '\0';
			c = fgetc(IN);
		}
		buf[k] = '\0';
		if(!judge(buf))/*�ж�����ַ������ǲ������������ĵ���*/{
			if(c == '\n')
				flag = 1;
			continue;
		}
		else
			root = addtree(buf, root);
		//for(k1 = 0;k1 < k;k1++)/*��buf��0*/
			//buf[k1] = '0';
		/*if(c == '\n')/*������ĩ�ޱ����������*//*{
			flag = 1;
			NLINE++;
		}*/
	}
	printtree(root);
}
int issame(char *p,char *q)/*�ж����ַ����Ƿ����*/
{
	while(*p != '\0' && *q != '\0' && *p == *q){
		p++;
		q++;
	}
	return (*p == '\0'&&*q=='\0')?0:1;
}
int judge(char *p)/*�жϸ��ַ����Ƿ�Ϊ���� */
{
	int i;
	char *str1="a",*str2="an",*str3="the",*str4="and";
	char *pt;
	pt=(char *)malloc(strlen(p)+1); 
	strcpy(pt,p);
	i = 0;
	while(pt[i]!='\0'){
		if(isalpha(pt[i])||pt[i]=='-'){
			if(isupper(pt[i]))
				pt[i] = tolower(pt[i]);
			i++;
		}
		else
			break;
	}
	if(pt[i]=='\0'&&issame(pt,str1)&&issame(pt,str2)&&issame(pt,str3)&&issame(pt,str4)/*&&*p!='-'&&*p!='\0'*/&& pt[0] != '\0')
		return 1;
	else
		return 0;
}
/*char *strdup(char *s)
{
	char *p;
	p=(char *)malloc(strlen(s)+1);
	if(p!=NULL)
		strcpy(p,s);
	return p;
}*/
struct tnode *addtree(char *s,struct tnode *p)/*��pλ�û�p���·�����һ��s�ڵ�*/
{
	int comp;
	/*char *pt;
	pt=(char *)malloc(strlen(s)+1);*/
	if(p==NULL){
		p=(struct tnode*)malloc(sizeof(struct tnode));/*��p����ռ�*/
		p->word=(char *)malloc(strlen(s)+1);/*��p�е���p->word����ռ�*/
		/*p->word=strdup(s);*/
		/*if(pt!=NULL)
			strcpy(pt,s);
		p->word=pt;*/
		strcpy(p->word,s);
		p->n=0;
		p->line[0]=NLINE;
		p->n++;
		p->line[p->n]=0;
		p->left=NULL;
		p->right=NULL;
	}
	else if((comp=strcmp(s,p->word))==0){
			if(p->line[p->n-1]!=NLINE){
				p->line[p->n]=NLINE;
				p->n++;
				p->line[p->n]=0;
			}
	}
		else if(comp<0)
				p->left=addtree(s,p->left);
			else
				p->right=addtree(s,p->right);
	return p;
}
void printtree(struct tnode *p)/*��ӡ������*/
{
	int i;
	if(p!=NULL){
		printtree(p->left);
		fprintf(OUT,"%s:",p->word);
		for(i=0;i<p->n;i++)
			fprintf(OUT,"%d%c",p->line[i],(p->line[i+1]!=0)?',':'\n');
		printtree(p->right);
	}
}
