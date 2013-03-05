/*
序列的第n项
【问题描述】
序列a(1)，a(2)，…，a(n)以及正整数k。对于i>1，a(i)是满足下面2个性质的最小正整数：
(1) a(i) > a(i-1)；
(2) a(i) 的各位数字的和与k×a(i-1)的各位数字的和相等。
例如，a(1)=1,k=2,n=6时，该序列的前6个元素是1，2，4，8，16，23。
现给定a(1),k,n的值，计算该序列的第n项a(n)的值。
【输入形式】
输入文件为当前目录下的sequence.in。
文件只有一行，包含3个整数a(1),k,n (0<a(1)<1000;0<k,n<300000)。
【输出形式】
输出文件为当前目录下的sequence.out。
该输出文件只有一个整数，为序列的第n项a(n)，以换行符结束。
【输入样例】
1 2 6
【输出样例】
23
【运行时限】
1秒
【上传文件】
上传C语言源程序，以sequence.c命名。
*/

#include<stdio.h>
enum{MAX=50000};
int s[2][MAX]={0};//s[][0]记录数的长度
void find_it(int,int,int);
void find_min(int state,int d);
int get_sum_num(int*,int);
main()
{	
	int k,n;
	int temp,i=0;
	FILE *in=fopen("sequence.in","r");

	fscanf(in,"%d%d%d",&temp,&k,&n);	
	find_it(temp,k,n);
	fclose(in);
}

void find_it(int t,int k,int n)
{
	int i=1,j=1,state=0;
	FILE *out=fopen("sequence.out","w");

	while(t>0){
		s[0][i++]=t%10;
		t/=10;
	}
	s[0][0]=i-1;//记录位数
	while(j++<n){
		find_min(state,k);
		state++;
	}
	j=s[state%2][0];
	while(j>0)
		fprintf(out,"%d",s[(state)%2][j--]);
	fprintf(out,"\n");
	fclose(out);
}

void find_min(int state,int t)
{
	int diff;
	int sum_number=get_sum_num(s[state%2],1); //得到原各位数字之和
	int sum_number2=get_sum_num(s[state%2],t);//得到乘积数字之和
	int i,j,k,p,temp=0;	
	diff=sum_number2-sum_number;

	for(i=0;i<=s[state%2][0];i++)
		s[(state+1)%2][i]=s[state%2][i];
	state++;
	k=state%2;
	if(diff<=0){
		j=1;
		temp=diff;
		while(temp<=0||s[k][j]==9){
			temp+=s[k][j];
			s[k][j++]=0;
		}
		while(temp-1<0){
			temp+=s[k][j];
			s[k][j++]=0;
		}
		while(s[k][j]==9)j++;
		s[k][j]++;
		temp--;
		while(s[k][s[k][0]+1]>0)//进位
			s[k][0]++;
		p=1;
		while(p<j){
			if(temp>9){
				s[k][p++]=9;
				temp-=9;
			}
			else{
				s[k][p++]=temp;
				return;
			}
		}
	}
	j=1;
	while(diff>0){
		while(s[k][j]==9)j++;
		if(s[k][j]+diff>9){
			diff-=(9-s[k][j]);
			s[k][j]=9;
		}
		else{
			s[k][j]+=diff;
			diff=0;
			break;
		}		
	}
	if(j>s[k][0])
		s[k][0]=j;
}

int get_sum_num(int d[],int x)//得到s*x的各位数字之和
{	
	int temp=0,result=0;
	int i;
	
	for(i=1;i<=d[0];++i){
		temp+=d[i]*x;
		result+=temp%10;
		temp/=10;
	}
	while(temp!=0){
		result+=temp%10;
		temp/=10;
	}
	return result;
}
