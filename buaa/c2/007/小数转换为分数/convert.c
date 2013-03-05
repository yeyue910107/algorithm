/*������������
������������С��������ѭ��С��ת��Ϊ����������Ϊ�ٷ�������
��������ʽ��
�ӱ�׼�����ȡ���ݣ���������ռһ�У���ʾһ��С�����еĳ��Ȳ�����100���ַ����ɻ��з�����������С�������ֺ�һ��С������ɣ�
���磺
2.12
5.69
0.618
����ѭ��С�������ֺ�һ��С�����Լ�һ���»���(_)��ɣ�ѭ��С����ѭ���ڴ��»��ߺ�ĵ�һ�����ֿ�ʼ����������ĩβ���һ������Ϊֹ��
���磺
0._1                  ��ʾ 0.i
3.5_142851            ��ʾ 3.5i4285i
�������ʽ��
������д����׼����ϣ�ռһ�У������ֺ�һ��б����ɣ�б��ǰ�����ֱ�ʾ���ӣ�б�ߺ������ʾ��ĸ�����ֺ�б��֮�䲻���ո����
������ɻ��з����������磺
41/152
7/3
������������
3.5_142857
�����������
123/35
*/
#include<stdio.h>
#include<stdlib.h>
enum {MAX = 100};
typedef struct{
	char *num;//, *numerator, *denominator, *leftPart, *middlePart, *rightPart;*/
	int type, leftNum, middleNum, rightNum, left, middle, right, numerator, denominator;
}DECIMAL;
DECIMAL preAction(DECIMAL decimal);
void getResult(DECIMAL decimal);
void simplify(int *m, int *n);
int gcd(int a, int b);
main()
{
	DECIMAL decimal;

	decimal.num = (char *)malloc(MAX);
	scanf("%s", decimal.num);
	decimal = preAction(decimal);
	getResult(decimal);
}

DECIMAL preAction(DECIMAL decimal){
	int i, k = 0, count = 0;
	char buf[MAX];

	decimal.type = 0;
	for(i = 0;decimal.num[i] != '\0';i++){
		buf[k++] = decimal.num[i];
		count++;
		if(decimal.num[i] == '.'){
			decimal.leftNum = count - 1;
			buf[k - 1] = '\0';
			decimal.left = atoi(buf);
			//decimal.leftPart = strcpy(decimal.leftPart, buf);
			count = 0;
			k = 0;
		}
		else if(decimal.num[i] == '_'){
			if(decimal.num[i - 1] == '.'){
				decimal.type = 1;
				//decimal.middleNum = 0;
				//decimal.middlePart = NULL;
			}
			else{
				decimal.type = 2;
				decimal.middleNum = count - 1;
				buf[k - 1] = '\0';
				//decimal.middlePart = strcpy(decimal.middlePart, buf);
				decimal.middle = atoi(buf);
			}
			count = 0;
			k = 0;
		}
	}
	buf[k] = '\0';
	decimal.rightNum = count;
	//decimal.rightPart = strcpy(decimal.rightPart, buf);
	decimal.right = atoi(buf);
	return decimal;
}

void getResult(DECIMAL decimal){
	int i;
	double temp;

	switch(decimal.type){
	case 0:
		for(i = 0, decimal.denominator = 1;i < decimal.rightNum;i++)
			decimal.denominator *= 10;
		//decimal.denominator[i] = '\0';
		//for(i = 0, j = 0;i < n;i++){
			//if(i == 0 && decimal.num[i] == '0')
			//	continue;
			//if(decimal.num[i] != '.')
				//decimal.numerator[j++] = decimal.num[i];
		//}
		decimal.numerator = (int)(atof(decimal.num) * decimal.denominator);
		//decimal.numerator[j] = '\0';
		break;
	case 1:
		for(i = 0, decimal.denominator = 0;i < decimal.rightNum;i++){
			decimal.denominator *= 10;
			decimal.denominator += 9;
		}
		decimal.numerator = decimal.left * decimal.denominator + decimal.right;
		break;
	case 2:
		for(i = 0, decimal.denominator = 0;i < decimal.rightNum;i++){
			decimal.denominator *= 10;
			decimal.denominator += 9;
		}
		temp = (double)decimal.middle;
		for(i = 0;i < decimal.middleNum;i++){
			decimal.denominator *= 10;
			temp /= 10;
		}
		decimal.numerator = (decimal.left + temp) * decimal.denominator + decimal.right;
		break;
	default:
		break;
	}
	simplify(&decimal.numerator, &decimal.denominator);
	printf("%d/%d", decimal.numerator, decimal.denominator);
}

void simplify(int *m, int *n){
	int divisor;

	while(1){
		divisor = gcd(*m, *n);
		if(divisor == 1)
			break;
		*m /= divisor;
		*n /= divisor;
	}
}

int gcd(int a, int b){
	int r;

	if(b == 0)
		return a;
	for(r = a % b;r != 0;r = a % b){
		a = b;
		b = r;
	}
	return b;
}
/*#include<stdio.h>
#include<string.h>
#include<stdlib.h>
enum {MAX = 100};
typedef struct{
	char *num, *numerator, *denominator, *leftPart, *middlePart, *rightPart;
	int type, leftNum, middleNum, rightNum;
}DECIMAL;
main()
{
	DECIMAL decimal;

	decimal = (DECIMAL)malloc(sizeof(DECIMAL));
	scanf("%s", decimal.num);
	preAction(decimal);
	getResult(decimal);
}

void preAction(DECIMAL decimal){
	int i, j, k = 0, count = 0;
	char buf[MAX];

	decimal.type = 0;
	for(i = 0;decimal.num[i] != '\0';i++){
		buf[k++] = decimal.num[i];
		count++;
		if(decimal.num[i] == '.'){
			decimal.leftNum = count;
			buf[k] = '\0';
			decimal.leftPart = strcpy(decimal.leftPart, buf);
			count = 0;
			k = 0;
		}
		else if(decimal.num[i] == '_'){
			if(decimal.num[i - 1] == '.'){
				decimal.type = 1;
				decimal.middleNum = 0;
				decimal.middlePart = NULL;
			}
			else{
				decimal.type = 2;
				decimal.middleNum = count;
				buf[k] = '\0;'
				decimal.middlePart = strcpy(decimal.middlePart, buf);
			}
			count = 0;
			k = 0;
		}
	}
	buf[k] = '\0';
	decimal.rightNum = count;
	decimal.rightPart = strcpy(decimal.rightPart, buf);
}

void getResult(DECIMAL decimal){
	int i, j, k, n = strlen(decimal.num);

	switch(decimal.type){
	case 0:
		decimal.denominator[0] = '1';
		for(i = 0;i < decimal.rightNum;i++)
			decimal.denominator[i] = '0';
		decimal.denominator[i] = '\0';
		for(i = 0, j = 0;i < n;i++){
			if(i == 0 && decimal.num[i] == '0')
				continue;
			if(decimal.num[i] != '.')
				decimal.numerator[j++] = decimal.num[i];
		}
		decimal.numerator[j] = '\0';
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
	simplify(decimal.numerator, decimal.denominator);
	printf("%s/%s", decimal.numerator, decimal.denominator);
}

void simplify(char *numerator, char *denominator){
	int num = strlen(numerator), denom = strlen(denominator), max = ((num > denom)?num:denom);
	char *divisor;

	divisor = (char *)malloc(max);
	while(1){
		divisor = gcd(numerator, denominator);
		if(strcmp(divisor, "1") == 0)
			break;
		div(numerator, divisor);
		div(denominator, divisor);
	}
}

char* gcd(char *s, char *t){


}

void mul(char *s, char *t){

}

void div(char *s, char *t){
	
}

void sub(char *s, char *t){
	int i, sLen = strlen(s), tLen = strlen(t), m, flag = 0;
	
	if(strcmp(s, t) == 0){
		s[0] = '0';
		s[1] = '\0';
		return 0;
	}
	reverseStr(s);
	reverseStr(t);
	for(i = sLen;i < tLen;i++)
		s[i] = '0';
	s[i] = '\0';
	sLen = tLen;
	for(i = 0;s[i] != '\0';i++){
		if(flag){
			if(s[i] != '0')
				s[i]--;
			else
				s[i] = '9';
		}
		if(s[i] >= t[i]){
			s[i] = (char)(s[i] - t[i] + 48);
			flag = 0;
		}
		else{
			s[i] = (char)(s[i] + 10 - t[i] + 48);
			flag = 1;
		}		
	}
	for(i = sLen - 1;i >= 0 && s[i] == '0';i--)
		s[i] = '\0';
	reverseStr(s);
	reverseStr(t);
}

void add(char *s, char *t){
	int i, sLen = strlen(s), tLen = strlen(t), m, mod = 0;
	
	reverseStr(s);
	reverseStr(t);
	for(i = sLen;i < tLen;i++)
		s[i] = '0';
	s[i] = '\0';
	sLen = tLen;
	for(i = 0;s[i] != '\0';i++){
		m = (int)((s[i] - 48) + (t[i] - 48) + mod);
        s[i] = (char)(m % 10 + 48);
        mod = m / 10;		
	}
	if(mod != 0){
        s[i] = (char)(mod + 48);
        s[i + 1]='\0';
    }
	reverseStr(s);
	reverseStr(t);
}

void reverseStr(char* s){
	int i, length = strlen(s);
	char temp;

	for(i = 0;i < length / 2;i++){
		temp = s[i];
		s[i] = s[length - i - 1];
		s[length - i - 1] = temp;
	}
}*/
