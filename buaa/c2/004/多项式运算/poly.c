/*������������
һԪ����ʽA = anxn + �� + a1x + a0, B = bnxn + �� + b1x + b0�����������+��-��*���ֱ����A + B��A - B��A * B��
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�poly.in��
���ļ���������ɡ���һ���Ƕ���ʽA���ڶ����Ƕ���ʽB����������һ�����������ʾ��Ҫ���е����㡣
����ʽ�г����������ÿһ�����ʽΪAnxN������An(-100��An��100)��һ����������ʾ�����ϵ����x�Ǳ�������N(-100��N��100)�Ǹ���Ĵ�����
����ϵ��Ϊ����ʱ��ϵ��ǰ�ġ�+��ʡ�ԣ�������ϵ��Ϊ����ʱ������������֮��û�пո�ϵ��Ϊ0�����ʾ��
���������⣬ϵ��Ϊ1�����ʾϵ����
�����������֮�������0�������ո����
�������ʽ��
������д�ڱ�׼����ϣ�ռһ�С�
�������ʽ�����ݷ�ʽ���У�����ı�ʾ��ʽ��������ʽ��ͬ��
�����������֮���һ������ϵ��ǰ���ų��⣩��
������������
3x5 + 5x3 + 6
9x6 + 2x5 + 6x3 + x2 + 6
-
�����������
-9x6 + x5 - x3 - x2
������˵����
������������ʾҪ���㣨3x5 + 5x3 + 6��- ��9x6 + 2x5 + 6x3 + x2 + 6�������Ϊ-9x6 + x5 - x3 - x2 ��
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
enum {MAX = 100};
struct LinkList{
	int base;
	int exp;
	struct LinkList *link;
};
struct LinkList* inputList(char* buf);
struct LinkList* calList(struct LinkList *list1,struct LinkList *list2,char op);
struct LinkList* multiplyList(struct LinkList *list1, int base, int exp);
struct LinkList* mulList(struct LinkList *list1,struct LinkList *list2);
void outputList(struct LinkList *list);
void numsort(int s[][2],int n);

main()
{
	FILE *in;
	struct LinkList *list, *list1, *list2;
	char buf[MAX], op;
	int i = 0;
	in = fopen("poly.in", "r");
	//in = fopen("poly.txt", "r");
	//in = stdin;
	list1 = (struct LinkList*)malloc(sizeof(struct LinkList));
	list2 = (struct LinkList*)malloc(sizeof(struct LinkList));
	list = (struct LinkList*)malloc(sizeof(struct LinkList));
	while(fgets(buf, MAX + 1, in) != NULL){
		//fscanf(in, "%s", buf);
		if(i == 0)
			list1 = inputList(buf);
		else if(i == 1)
			list2 = inputList(buf);
		else
			op = buf[0];
		i++;
	}
	switch(op){
	case '+':
		list = calList(list1, list2, op);
		break;
	case '-':
		list = calList(list1, list2, op);
		break;
	case '*':
		list = mulList(list1, list2);
		break;
	default:
		break;
	}
	outputList(list);
	fclose(in);
}
/*Input a list*/
struct LinkList* inputList(char* buf)
{
	int i = 0, k = 0, j = 0, flag = 0;
	int data[MAX][2] = {(0,0)}, num;
	char temp[MAX];
	struct LinkList *list, *p, *r;

	//list = (struct LinkList*)malloc(sizeof(struct LinkList));
	list = NULL;
	i = -1;
	temp[0] = '\0';
	while(1){
		i++;
		if(buf[i] == '-'){
			/*if(temp[0] != '\0'){
				if(flag){
					data[j][1] = atoi(temp);
					temp[0] = '-';
					temp[1] = '\0';
					k = 1;
					flag = 0;
				}
				else{
					data[j][0] = atoi(temp);
					temp[0] = '-';
					temp[1] = '\0';
					k = 1;
					flag = 1;
				}
			}
			else if(temp[0] == '\0'){
				if(flag){
				data[j][1] = 1;
				temp[0] = '-';
				temp[1] = '\0';
				k = 1;
				flag = 0;
				j++;
				}
				else{*/
					temp[k++] = buf[i];
					temp[k] = '\0';
				//}
		//	}
			
		}
		else if(isdigit(buf[i])){
			temp[k++] = buf[i];
			temp[k] = '\0';
		}
		else if(buf[i] == 'x'){
			if(temp[0] == '-')
				if(temp[1] != '\0'){
					data[j][0] = atoi(temp);
					temp[0] = '\0';
					k = 0;
					flag = 1;
				}
				else{
					data[j][0] = -1;
					temp[0] = '\0';
					k = 0;
					flag = 1;
				}
			else if(temp[0] != '\0'){
				data[j][0] = atoi(temp);
				temp[0] = '\0';
				k = 0;
				flag = 1;
			}
			else{
				data[j][0] = 1;
				flag = 1;
			}
		}
		else if(buf[i] == '+'){
			if(temp[0] != '\0'){
				if(flag){
					data[j][1] = atoi(temp);
					temp[0] = '\0';
					k = 0;
					flag = 0;
				}
				else{
					data[j][0] = atoi(temp);
					temp[0] = '\0';
					k = 0;
					flag = 1;
					j++;
				}
			}
			else{
				if(flag){
					data[j][1] = 1;
					flag = 0;
					j++;
				}
			}
		}
		else if(buf[i] == ' '){
			if(temp[0] == '-')
				continue;
			else if(temp[0] != '\0'){
				data[j][1] = atoi(temp);
				temp[0] = '\0';
				k = 0;
				flag = 0;
				j++;
			}
			else if(flag){
				data[j][1] = 1;
				flag = 0;
				j++;
			}
		}
		else if(buf[i] == '\n'){
			if(temp[0] != '\0' && flag == 0){
				data[j][0] = atoi(temp);
				temp[0] = '\0';
				k = 0;
				j++;
			}
			else if(temp[0] != '\0' && flag == 1){
				data[j][1] = atoi(temp);
				temp[0] = '\0';
				k = 0;
				j++;
			}
			else if(temp[0] == '\0' && flag == 1){
				data[j][1] = 1;
				j++;
			}
			//else if(temp[0] == '\0' && flag == 0){
				
			//}
			break;
		}
	}
	num = j;
	numsort(data, num);
	for(k = 1;k <= num;k++){
		p = (struct LinkList*)malloc(sizeof(struct LinkList));
		p->base = data[k-1][0];
		p->exp = data[k-1][1];
		p->link = NULL;
		if(list == NULL)
			list = p;
		else
			r->link = p;
		r = p;
	}
	return list;
}
/*add and substract*/
struct LinkList* calList(struct LinkList *list1,struct LinkList *list2, char op)
{
	struct LinkList *p, *p1, *p2, *r, *list;

	list = NULL;
	p1 = list1;p2 = list2;
	while(p1 != NULL||p2 != NULL){
		p = (struct LinkList*)malloc(sizeof(struct LinkList));
		if(p1 == NULL){
			p->exp = p2->exp;
			p->base = ((op == '+')?(p2->base):(-(p2->base)));
			p2 = p2->link;
		}
		else if(p2 == NULL){
			p->exp = p1->exp;
			p->base = p1->base;
			p1 = p1->link;
		}
		else if(p1->exp == p2->exp){
			p->exp = p1->exp;
			if(op == '+')
				p->base = p1->base + p2->base;
			else
				p->base = p1->base - p2->base;
			p1 = p1->link;p2 = p2->link;
		}
		else if(p1->exp < p2->exp){
			p->exp = p2->exp;
			p->base = ((op == '+')?(p2->base):(-(p2->base)));
			p2 = p2->link;
		}
		else if(p1->exp > p2->exp){
			p->exp = p1->exp;
			p->base = p1->base;
			p1 = p1->link;
		}
		p->link = NULL;
		if(list == NULL)
			list = p;
		else
			r->link = p;
		r = p;
	}
	return list;
}
/*multiply*/
struct LinkList* mulList(struct LinkList *list1,struct LinkList *list2)
{
	struct LinkList *p1, *p2, *list, *temp;
	int i = 0;

	temp = NULL;
	list = NULL;
	p1 = list1;
	p2 = list2;
	while(p2 != NULL){
		temp = multiplyList(list1, p2->base, p2->exp);
		if(i == 0)
			list = temp;
		else
			list = calList(list, temp, '+');
		p2 = p2->link;
		i++; 
	}
	return list;
}

struct LinkList* multiplyList(struct LinkList *list1, int base, int exp)
{
	struct LinkList *list, *p, *p1, *r;

	list = NULL;
	p1 = list1;
	while(p1 != NULL){
		p = (struct LinkList*)malloc(sizeof(struct LinkList));
		p->base = p1->base * base;
		p->exp = p1->exp + exp;
		p1 = p1->link;
		p->link = NULL;
		if(list == NULL)
			list = p;
		else
			r->link = p;
		r = p;
	}
	return list;
}
/*Output a list*/
void outputList(struct LinkList *list)
{
	int i = 0;
	struct LinkList *p;

	p = list;
	while(p != NULL){
		if(i == 0){
			if(p->base != 0){
				if(p->exp != 0 && p->exp != 1){
					if(p->base == 1)
						printf("x%d%c",p->exp,(p->link == NULL || p->link->base == 0)?'\n':' ');
					else if(p->base == -1)
						printf("-x%d%c",p->exp,(p->link == NULL || p->link->base == 0)?'\n':' ');
					else
						printf("%dx%d%c",p->base,p->exp,(p->link == NULL || p->link->base == 0)?'\n':' ');
				}
				else if(p->exp == 1){
					if(p->base == 1)
						printf("x%c",(p->link == NULL || p->link->base == 0)?'\n':' ');
					else if(p->base == -1)
						printf("-x%c",(p->link == NULL || p->link->base == 0)?'\n':' ');
					else
						printf("%dx%c",p->base,(p->link == NULL || p->link->base == 0)?'\n':' ');
				}
				else{
					printf("%d%c",p->base,(p->link == NULL || p->link->base == 0)?'\n':' ');
				}
			}
			else if(p->link == NULL)
				printf("%d%c",p->base,(p->link == NULL || p->link->base == 0)?'\n':' ');
			else{
				p = p->link;
				continue;
			}
		}
		else{
			if(p->base > 0){
				if(p->exp != 0 && p->exp != 1){
					if(p->base == 1)
						printf("+ x%d%c",p->exp,(p->link == NULL || p->link->base == 0)?'\n':' ');
					else
						printf("+ %dx%d%c",p->base,p->exp,(p->link == NULL || p->link->base == 0)?'\n':' ');
				}
				else if(p->exp == 1){
					if(p->base == 1)
						printf("+ x%c",(p->link == NULL || p->link->base == 0)?'\n':' ');
					else
						printf("+ %dx%c",p->base,(p->link == NULL || p->link->base == 0)?'\n':' ');
				}
				else{
					printf("+ %d%c",p->base,(p->link == NULL || p->link->base == 0)?'\n':' ');
				}
			}
			else if(p->base < 0){
				if(p->exp != 0 && p->exp != 1){
					if(p->base == -1)
						printf("- x%d%c",p->exp,(p->link == NULL || p->link->base == 0)?'\n':' ');
					else
						printf("- %dx%d%c",-(p->base),p->exp,(p->link == NULL || p->link->base == 0)?'\n':' ');
				}
				else if(p->exp == 1){
					if(p->base == -1)
						printf("- x%c",(p->link == NULL || p->link->base == 0)?'\n':' ');
					else
						printf("- %dx%c",-(p->base),(p->link == NULL || p->link->base == 0)?'\n':' ');
				}
				else{
					printf("- %d%c",-(p->base),(p->link == NULL || p->link->base == 0)?'\n':' ');
				}
			}
		}
		i++;
		p = p->link;
	}
}
/*sort*/
void numsort(int s[][2],int n)
{
	int i, j;
	int temp1, temp2;

	for(i =1;i < n;i ++)
		for(j = n - 1;j >= i;j --){
			if(s[j][1] > s[j-1][1]){
				temp1 = s[j-1][0];
				temp2 = s[j-1][1];
				s[j-1][0] = s[j][0];
				s[j-1][1] = s[j][1];
				s[j][0] = temp1;
				s[j][1] = temp2;
			}
		}
}

