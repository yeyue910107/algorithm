/*【问题描述】
“交叉引用生成器”（cross-refrencer）是指具有如下功能的程序：
对输入的一篇文档，统计出现的所有单词及其所在行号。将其结果以规定格式打印。
【输入形式】
程序从标准输入上读入一篇文档。
该文档由若干行组成，每行中包含一系列单词。空行表示输入结束。行号由1开始计数。该文档中单词总量不超过500，
每个单词长度最大不超过20个字符。
【输出形式】
在标准输出上打印文档中所有出现的单词及其所在行号。
输出有若干行，每一行都是文档中出现的一个单词。按如下规格输出： 
word:line1,line2, … ,lineN
其中word是单词，后面紧跟一个冒号，然后是以逗号隔开的出现行号line1，line2，等等。在该行上各字符紧密输出，不使用空格分隔。
在输出时遵循以下规定：
1.只输出所有由英文字母（包括连字符）构成的单词，数字或包含其它特殊字符的单词不用输出。先输出大写A?Z开头的字符，
再输出小写a?z开头的符。
2.各单词后面的行号从小到大排列。行号不重复打印，亦即如果一个单词在一行内多次出现，则只打印一次该行号。
3.统计的单词不包括冠词、连词等无实际意义的单词。在本题中涉及如下四个单词：
1.a
2.an
3.the
4.and
【输入样例】
Alcatel provides end-to-end solutions.
It enables enterprises to deliver content to any type of user.
lcatel operates in 130 countries.
Alcatel focus on optimizing their service offerings and revenue streams.
【输出样例】
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
	int line[MAXLINE];/*记录行数的数组*/
	int n;/*记录行数数组的下标*/
	struct tnode *left;/*左分叉*/
	struct tnode *right;/*右分叉*/
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
		while(isalnum(c) || c == '-'){/*读取一个字符串*/
			buf[k] = c;
			k++;
			//buf[k] = '\0';
			c = fgetc(IN);
		}
		buf[k] = '\0';
		if(!judge(buf))/*判断这个字符数组是不是满足条件的单词*/{
			if(c == '\n')
				flag = 1;
			continue;
		}
		else
			root = addtree(buf, root);
		//for(k1 = 0;k1 < k;k1++)/*将buf归0*/
			//buf[k1] = '0';
		/*if(c == '\n')/*处理行末无标点的特殊情况*//*{
			flag = 1;
			NLINE++;
		}*/
	}
	printtree(root);
}
int issame(char *p,char *q)/*判断两字符串是否相等*/
{
	while(*p != '\0' && *q != '\0' && *p == *q){
		p++;
		q++;
	}
	return (*p == '\0'&&*q=='\0')?0:1;
}
int judge(char *p)/*判断该字符串是否为单词 */
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
struct tnode *addtree(char *s,struct tnode *p)/*在p位置或p的下方增加一个s节点*/
{
	int comp;
	/*char *pt;
	pt=(char *)malloc(strlen(s)+1);*/
	if(p==NULL){
		p=(struct tnode*)malloc(sizeof(struct tnode));/*给p分配空间*/
		p->word=(char *)malloc(strlen(s)+1);/*给p中单词p->word分配空间*/
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
void printtree(struct tnode *p)/*打印二叉树*/
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
