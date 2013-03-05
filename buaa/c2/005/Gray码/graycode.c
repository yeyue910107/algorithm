/*������������
������(Gray Code)��һ����λ�ô������г��õı��룬���ص���ÿ�������ڵ����ĸ�����ֻ��һ��������λ�ǲ�ͬ�ġ�
���磬0��7�ĸ�����������£�
0    000 
1    001 
2    011 
3    010 
4    110 
5    111 
6    101 
7    100
��ͨ�����Ʊ��뵽�������ת����ʽ����: 
Gn-1 = Bn-1
Gi = Bi+1 ^ Bi  (0<=i<n-1,nΪ����ĳ���)
�����뵽��ͨ�����Ʊ����ת����ʽ���£� 
Bn-1 = Gn-1
Bn-2 = Gn-2 ^ Bn-1 
... ...
B0 = G0 ^ B1 
ת����ʽ�е�Gk��Bk�ֱ��ʾ������Ͷ����Ʊ����еĵ�kλ�������λ���0��ʼ��������������� 
��������ʽ��
�ӱ�׼�����ȡ���ݡ�
���������Ϊһϵ�е�0��1�ַ�����������50���ַ�֮�ڡ���0��1��֮ǰ�ֱ���ѡ����-b��-g��
ǰ�߱�ʾ���������������Ϊ������ת���ɶ������룬���߱�ʾ����Щ��������Ϊ��������ת���ɸ����룬��ѡ��ʱ��ͬ��-b��
ѡ�������֮�䣬�Լ�ÿ��ǰ���޶���ո�������EOF������
�������ʽ��
�������ӡ����׼����ϡ�
���ת���Ľ����ÿ����ռһ�С�
������������
-g0111
-b0011
101
�����������
0100
0010
110
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {MAX = 100, LEN = 50, TO_GRAY = 0, TO_BINARY = 1};
typedef struct code{
	int type;
	char *str;
}CODE;
void to_binary(char *str);
void to_gray(char *str);
main()
{
	char c, buf[LEN];
	CODE code[MAX];
	int i = 0, k = 0, flag = 0, num;
	c = getchar();
	while(1){
		if(c == '-' || c == 'g' || c == 'b'){
			if(c == 'g')
				code[k].type = TO_GRAY;
			else if(c == 'b')
				code[k].type = TO_BINARY;
			flag = 1;
			c = getchar();
			continue;
		}
		else{
			if(flag == 0)
				code[k].type = TO_BINARY;
			while(c != '\n' && c != EOF){
				if(c == '0' || c == '1')
					buf[i++] = c;
				c = getchar();
			}
			buf[i] = '\0';
			code[k].str = (char *)malloc(sizeof(buf) + 1);
			code[k].str = strcpy(code[k].str, buf);
			i = 0;k++;flag = 0;
		}
		if(c == EOF)
			break;
		c = getchar();
	}
	num = k;
	for(k = 0;k < num;k++){
		if(code[k].type)
			to_binary(code[k].str);
		else
			to_gray(code[k].str);
	}
}

void to_binary(char *str){
	int i, length = strlen(str);
	char temp;

	for(i = 0;i < length;i++){
		if(i == 0){
			temp = str[i];
			printf("%c", temp);
		}
		else{
			temp = (char)(((int)str[i] - 48) ^ ((int)temp - 48)) + 48;
			printf("%c", temp);
		}
	}
	printf("\n");
}

void to_gray(char *str){
	int i, length = strlen(str);

	for(i = 0;i < length;i++){
		if(i == 0)
			printf("%c", str[i]);
		else
			printf("%c", ((char)(((int)str[i - 1] - 48) ^ ((int)str[i] - 48)) + 48));
	}
	printf("\n");
}