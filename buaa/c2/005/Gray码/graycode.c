/*【问题描述】
格雷码(Gray Code)是一种在位置传感器中常用的编码，其特点是每两个相邻的数的格雷码只有一个二进制位是不同的。
例如，0－7的格雷码编码如下：
0    000 
1    001 
2    011 
3    010 
4    110 
5    111 
6    101 
7    100
普通二进制编码到格雷码的转换方式如下: 
Gn-1 = Bn-1
Gi = Bi+1 ^ Bi  (0<=i<n-1,n为编码的长度)
格雷码到普通二进制编码的转换方式如下： 
Bn-1 = Gn-1
Bn-2 = Gn-2 ^ Bn-1 
... ...
B0 = G0 ^ B1 
转换公式中的Gk和Bk分别表示格雷码和二进制编码中的第k位。编码的位序从0开始，从右向左递增。 
【输入形式】
从标准输入读取数据。
读入的数据为一系列的0、1字符串，长度在50个字符之内。在0、1串之前分别有选项是-b或-g，
前者表示将读入的正整数作为格雷码转换成二进制码，后者表示将这些正整数作为二进制码转换成格雷码，无选项时等同于-b。
选项与编码之间，以及每行前后无多余空格。输入以EOF结束。
【输出形式】
将结果打印到标准输出上。
输出转换的结果，每个数占一行。
【输入样例】
-g0111
-b0011
101
【输出样例】
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