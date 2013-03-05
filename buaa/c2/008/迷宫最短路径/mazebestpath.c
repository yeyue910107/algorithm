/*������������
����M*N��5<M,N<80����������ɵľ����Թ��У����������������񹹳ɵĿ���ͨ�е������Լ�����ͨ�е��ϰ��
дһ�����򣬴ӱ�׼�����ж���һ���Թ��Ĳ����Լ�λ�ڿ���ͨ�������е���ʼ�㣬���������·������̾��롣
��������ʽ��
�ӱ�׼�����ȡ���롣
����������M���ַ�����ɣ�ÿ����N���ַ������С�.����ʾ�÷������ͨ�У���w����ʾ�÷������ϰ����S����ʾ�÷����ǳ����㣬
��E����ʾ�÷�����Ŀ��㡣��һ����������ߵ������������ĸ����ڵĿ�ͨ�з����У���ÿ������ľ���Ϊ1��
����ĩβ�л��з���
�������ʽ��
���׼�����ӡ�����
�������Ϊһ��������ռһ�У���ʾ�ӳ����㵽Ŀ���Ĳ���������ʼ��֮��û��ͨ·ʱ�����-1��
������������
..........w.......
..........w.......
..........w.......
..........w.......
S.........w.......
wwwwww..www.......
........w.....wwww
........w.........
........w.........
.......ww.........
......www.........
......w...........
......w......w....
......w......w..ww
.............w....
.............w....
.............w....
.............w...E
�����������
38
������˵����
..........w.......
..........w.......
..........w.......
..........w.......
Soooooo...w.......
wwwwwwo.www.......
......o.w.....wwww
......o.w.........
......o.w.........
.....ooww.........
.....owww.........
.....ow....ooooo..
.....ow....o.w.o..
.....ow....o.w.oww
.....ooooooo.w.ooo
.............w...o
.............w...o
.............w...E
��ͼ��o���б�ʾ����һ�����·�����ش�·���ߣ������S����������38�������յ�E��
*/
#include<stdio.h>
enum {MAX = 80};
typedef struct{
	int i, j, pi, pj;
}POINT;
void readMaze(char maze[][MAX], int *row, int *column, POINT *start, POINT *end);
int getResult(char maze[][MAX], int row, int column, POINT start, POINT end);
int main()
{
	char maze[MAX][MAX];
	POINT start = {-1, -1, -1, -1}, end = {-1, -1, -1, -1};
	int row, column;

	readMaze(maze, &row, &column, &start, &end);
	printf("%d\n", getResult(maze, row, column, start, end));
}

void readMaze(char maze[][MAX], int *row, int *column, POINT *start, POINT *end){
	int i, j;
	char c;
	
	c = getchar();
	for(i = 0;c != EOF;i++){
		for(j = 0;c != '\n';j++){
			if(c == 'S'){
				start->i = i;
				start->j = j;
				maze[i][j] = '.';
			}
			else if(c == 'E'){
				end->i = i;
				end->j = j;
				maze[i][j] = '.';
			}
			else
				maze[i][j] = c;
			c = getchar();
		}
		c = getchar();
	}
	*column = i;
	*row = j;
}

int getResult(char maze[][MAX], int row, int column, POINT start, POINT end){
	POINT queue[640000];
	int front = -1, rear = 0, k = 1, count = 0;

	queue[0] = start;
	//while(front != rear && (queue[rear].i != end.i || queue[rear].j != end.j)){
		//item = queue[front + 1];
	while(queue[front + 1].i != end.i || queue[front + 1].j != end.j){
		front++;
		//if(queue[])
		if(queue[front].i > 0 && (queue[front].pi != queue[front].i - 1 || queue[front].pj != queue[front].j) && maze[queue[front].i - 1][queue[front].j] == '.'){
			queue[rear + k].i = queue[front].i - 1;
			queue[rear + k].j = queue[front].j;
			queue[rear + k].pi = queue[front].i;
			queue[rear + k].pj = queue[front].j;
			maze[queue[front].i - 1][queue[front].j] = 'o';
			k++;
		}
		if(queue[front].j > 0 && (queue[front].pi != queue[front].i || queue[front].pj != queue[front].j - 1) && maze[queue[front].i][queue[front].j - 1] == '.'){
			queue[rear + k].i = queue[front].i;
			queue[rear + k].j = queue[front].j - 1;
			queue[rear + k].pi = queue[front].i;
			queue[rear + k].pj = queue[front].j;
			maze[queue[front].i][queue[front].j - 1] = 'o';
			k++;
		}
		if(queue[front].i < column && (queue[front].pi != queue[front].i + 1 || queue[front].pj != queue[front].j) && maze[queue[front].i + 1][queue[front].j] == '.'){
			queue[rear + k].i = queue[front].i + 1;
			queue[rear + k].j = queue[front].j;
			queue[rear + k].pi = queue[front].i;
			queue[rear + k].pj = queue[front].j;
			maze[queue[front].i + 1][queue[front].j] = 'o';
			k++;
		}
		if(queue[front].j < row && (queue[front].pi != queue[front].i || queue[front].pj != queue[front].j + 1) && maze[queue[front].i][queue[front].j + 1] == '.'){
			queue[rear + k].i = queue[front].i;
			queue[rear + k].j = queue[front].j + 1;
			queue[rear + k].pi = queue[front].i;
			queue[rear + k].pj = queue[front].j;
			maze[queue[front].i][queue[front].j + 1] = 'o';
			k++;
		}
		if(front == rear){
			if(k == 1){
				return -1;
			}
			else{
				rear += k - 1;
				k = 1;
				count++;
			}
		}
	}
	//}
	return count;
}
