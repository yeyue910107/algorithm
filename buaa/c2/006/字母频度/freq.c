/*【问题描述】
统计文件中各字母的出现次数以及所有字母出现次数的总和。同一字母大小写的出现次数合并计算。
【输入形式】
输入文件为freq.in，文件最大长度不超过2000000个字符。
【输出形式】
输出文件为freq.out
输出包括两行，第一行输出在文件中出现次数最多的前10 位字母及其出现次数（从大到小排序）。出现次数相同的字母按字母顺序排列。
字母与出现次数连续输出，后接一空格。如有并列第10的情况，即第11项与之后若干项的值与第10项相同，则输出所有的并列项。
第二行输出所有字母出现的总和。
【输入样例】
Iraqi leaders attempted Thursday to close the widening sectarian divide in the wake of widespread reprisals by Shiite Muslims 
against Sunnis after the bombing of a Shiite shrine. Iraqi and U.S. officials called for calm, but a powerful Sunni Arab 
political bloc said it is boycotting national unity talks. A curfew was imposed Thursday evening in Baghdad and three 
surrounding provinces, which could stir even more controversy because it will remain in effect through Friday's noon Muslim 
prayers -- the most sacred prayers of the week for followers.
【输出样例】
e45 i45 a38 s36 r33 t31 n29 o28 d20 l20 
453
（表示出现e 45次,i 45次...总计字母453）
*/
#include<stdio.h>
enum {MAX = 26};
typedef struct{
	int num;
	char letter;
}COUNT;
void init(COUNT count[]);
void getResult(FILE *in, COUNT count[]);
void insertSort(COUNT array[], int n);
void printResult(FILE *out, COUNT count[]);
int sum = 0;
main()
{
	FILE *in, *out;
	COUNT count[MAX] = {0};
	in = fopen("freq.in", "r");
	out = fopen("freq.out", "w");
	//in = fopen("freq1.txt", "r");
	//out = fopen("freq2.txt", "w");
	//in = stdin;
	//out = stdout;

	init(count);
	getResult(in, count);
	insertSort(count, MAX);
	printResult(out, count);
	fclose(in);
	fclose(out);
}

void init(COUNT count[]){
	int i;

	for(i = 0;i < MAX;i++){
		count[i].letter = 'a' + i;
		count[i].num = 0;
	}
}

void getResult(FILE *in, COUNT count[]){
	char c;

	while((c = fgetc(in)) != EOF){
		if(c >= 'a' && c <= 'z'){
		//	count[(int)(c - 'a')].letter = c;
			count[(int)(c - 'a')].num++;
			sum++;
		}
		else if(c >= 'A' && c <= 'Z'){
		//	count[(int)(c - 'A')].letter = c;
			count[(int)(c - 'A')].num++;
			sum++;
		}
	}
}

void insertSort(COUNT array[], int n){
	int i, j;
	COUNT temp;

	for(i = 0;i < n - 1;i++){
		temp = array[i + 1];
		for(j = i + 1;j > 0 && temp.num > array[j - 1].num;j--)
			array[j] = array[j - 1];
		array[j] = temp;
	}
}

void printResult(FILE *out, COUNT count[]){
	int i;

	for(i = 0;i < 10;i++)
		fprintf(out, "%c%d%c", count[i].letter, count[i].num, (i == 9 && count[i + 1].num < count[i].num)?'\n':' ');
	for(;i < MAX && count[i].num == count[i - 1].num;i++)
		fprintf(out, "%c%d%c", count[i].letter, count[i].num, (i < MAX - 1 && count[i + 1].num == count[i].num)?' ':'\n');
	fprintf(out, "%d\n", sum);
}
