/*������������
ͳ���ļ��и���ĸ�ĳ��ִ����Լ�������ĸ���ִ������ܺ͡�ͬһ��ĸ��Сд�ĳ��ִ����ϲ����㡣
��������ʽ��
�����ļ�Ϊfreq.in���ļ���󳤶Ȳ�����2000000���ַ���
�������ʽ��
����ļ�Ϊfreq.out
����������У���һ��������ļ��г��ִ�������ǰ10 λ��ĸ������ִ������Ӵ�С���򣩡����ִ�����ͬ����ĸ����ĸ˳�����С�
��ĸ����ִ���������������һ�ո����в��е�10�����������11����֮���������ֵ���10����ͬ����������еĲ����
�ڶ������������ĸ���ֵ��ܺ͡�
������������
Iraqi leaders attempted Thursday to close the widening sectarian divide in the wake of widespread reprisals by Shiite Muslims 
against Sunnis after the bombing of a Shiite shrine. Iraqi and U.S. officials called for calm, but a powerful Sunni Arab 
political bloc said it is boycotting national unity talks. A curfew was imposed Thursday evening in Baghdad and three 
surrounding provinces, which could stir even more controversy because it will remain in effect through Friday's noon Muslim 
prayers -- the most sacred prayers of the week for followers.
�����������
e45 i45 a38 s36 r33 t31 n29 o28 d20 l20 
453
����ʾ����e 45��,i 45��...�ܼ���ĸ453��
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
