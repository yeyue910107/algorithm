/*������������
����A��B��C�����㹻����ϸ������A���Ϸ���2n���м��пյ�Բ�̣�����n����ͬ�ĳߴ磬ÿ���ߴ綼��������ͬ��Բ�̣�
ע��������Բ���ǲ������ֵġ���Ҫ����2n��Բ���Ƶ�C���ϣ����ƶ������пɷ���B�����ݴ档
Ҫ��
(1)ÿ��ֻ���ƶ�һ��Բ�̣�
(2) A��B��C����ϸ���ϵ�Բ�̶�Ҫ������С�´��˳��
(3)�������n�������������������������ƶ�����M�Լ����ӵ��ƶ�������
��������ʽ��
�ӱ�׼�����϶���һ��������n (0 < n < 12)��
�������ʽ��
�ڱ�׼�������������ƶ�����M���ƶ�������
�����ʽ����һ��Ϊ����M������M��Ϊ�ƶ�������
�ƶ�������ʽ���£�
move <���ӳߴ�> from <ԭλ��> to <��λ��>
����<���ӳߴ�>Ϊһ��С�ڵ���n����������<ԭλ��>��<��λ��>��Ϊ��ĸA��B��C�е�һ����
ע��ÿ�����ʼ�һ���пո�
������������
2
�����������
6
move 1 from A to B
move 1 from A to B
move 2 from A to C
move 2 from A to C
move 1 from B to C
move 1 from B to C
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {MAX = 5000};
int count = 0;
typedef struct{
	int n, from, to;
}PATH;
void hanoi(int n, int from, int to, int via, PATH path[]);
void move(int n, int from, int to, PATH path[]);
void output(PATH path[]);
int main()
{
	int n;
	PATH path[MAX] = {0};
	scanf("%d", &n);
	hanoi(n, 'A', 'C', 'B', path);
	output(path);
}

void hanoi(int n, int from, int to, int via, PATH path[]){
	if(n == 1){
		move(n, from, to, path);
		return;
	}
	hanoi(n - 1, from, via, to, path);
	move(n, from, to, path);
	hanoi(n - 1, via, to, from, path);
}

void move(int n, int from, int to, PATH path[]){
	path[count].n = n;
	path[count].from = from;
	path[count].to = to;
	path[count + 1].n = n;
	path[count + 1].from = from;
	path[count + 1].to = to;
	count += 2;
}

void output(PATH path[]){
	int i;
	
	printf("%d\n", count);
	for(i = 0;i < count;i++)
		printf("move %d from %c to %c\n", path[i].n, path[i].from, path[i].to);
	//printf("%d\n", count);
}