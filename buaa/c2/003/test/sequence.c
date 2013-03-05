/*
���еĵ�n��
������������
����a(1)��a(2)������a(n)�Լ�������k������i>1��a(i)����������2�����ʵ���С��������
(1) a(i) > a(i-1)��
(2) a(i) �ĸ�λ���ֵĺ���k��a(i-1)�ĸ�λ���ֵĺ���ȡ�
���磬a(1)=1,k=2,n=6ʱ�������е�ǰ6��Ԫ����1��2��4��8��16��23��
�ָ���a(1),k,n��ֵ����������еĵ�n��a(n)��ֵ��
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�sequence.in��
�ļ�ֻ��һ�У�����3������a(1),k,n (0<a(1)<1000;0<k,n<300000)��
�������ʽ��
����ļ�Ϊ��ǰĿ¼�µ�sequence.out��
������ļ�ֻ��һ��������Ϊ���еĵ�n��a(n)���Ի��з�������
������������
1 2 6
�����������
23
������ʱ�ޡ�
1��
���ϴ��ļ���
�ϴ�C����Դ������sequence.c������
*/

#include<stdio.h>
enum{MAX=50000};
int s[2][MAX]={0};//s[][0]��¼���ĳ���
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
	s[0][0]=i-1;//��¼λ��
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
	int sum_number=get_sum_num(s[state%2],1); //�õ�ԭ��λ����֮��
	int sum_number2=get_sum_num(s[state%2],t);//�õ��˻�����֮��
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
		while(s[k][s[k][0]+1]>0)//��λ
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

int get_sum_num(int d[],int x)//�õ�s*x�ĸ�λ����֮��
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
