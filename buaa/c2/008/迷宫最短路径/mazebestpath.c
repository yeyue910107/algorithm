/*【问题描述】
在由M*N（5<M,N<80）个方格组成的矩形迷宫中，有若干由相连方格构成的可以通行的区域，以及不可通行的障碍物。
写一个程序，从标准输入中读入一个迷宫的布局以及位于可以通行区域中的起始点，求这两点间路径的最短距离。
【输入形式】
从标准输入读取输入。
输入数据由M行字符串组成，每行有N个字符，其中’.’表示该方格可以通行，’w’表示该方格是障碍物，’S’表示该方格是出发点，
’E’表示该方格是目标点。从一个方格可以走到其上下左右四个相邻的可通行方格中，且每个方格的距离为1。
输入末尾有换行符。
【输出形式】
向标准输出打印结果。
输出数据为一个整数，占一行，表示从出发点到目标点的步数。当起始点之间没有通路时，输出-1。
【输入样例】
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
【输出样例】
38
【样例说明】
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
上图中o序列表示其中一条最短路径。沿此路径走，从起点S出发，经过38步到达终点E。
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
