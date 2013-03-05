/*【问题描述】
合法的实数书写格式分一般格式和科学格式两种。分别描述如下：
一般格式为常见的书写格式，分为整数部分和小数部分两部分，中间分用小数点.分隔。整数部分最开始可能含有正号或负号，
之后为不含前导零的数字串；小数部分是由0-9十种字符组成的任意长的字符串。当小数部分为0时，小数部分和小数点可以省略。
科学格式由系数部分和指数部分两部分组成，中间用英文字母E分隔。系数部分为实数书写的一般格式；指数部分为可带有正负号数字串。
例如，+2、-1.56为一般格式的实数，而6.2E-2、-9E8为科学格式的实数。
编程分析哪些数的书写是正确的，是用哪种方式书写的。
【输入形式】
输入文件为当前目录下的real.in。
该文件包含一个字符串，以回车符结束，表示一个数据（无多余空格）。
【输出形式】
输出文件为当前目录下的real.out。
该文件有一行。如果输入数据的书写是非法的，输出Wrong；如果输入数据是用一般格式书写的，输出“Format1”；
如果该数据是用科学格式书写的，输出“Format2”。输出的末尾均要以一个回车符作为结束。
【输入样例1】
+1.23
【输出样例1】
Format1
【输入样例2】
-5.1.1
【输出样例2】
Wrong
【输入样例3】
-5.1E-2
【输出样例3】
Format2
*/
#include<stdio.h>
#include<ctype.h>
main()
{
	FILE *in, *out;
	char c;
	int state = 0;
	//in = fopen("real.in", "r");
	//out = fopen("real.out", "w");
	in = stdin;
	out = stdout;
	while(c = fgetc(in)){
		switch(state){
			case 0:
				if(c == '+' || c == '-')
					state = 1;
				else if(isdigit(c) && c != '0')
					state = 2;
				else{
					fprintf(out, "Wrong\n");
					fclose(in);
					fclose(out);
					return 0;
				}
				break;
			case 1:
				if(isdigit(c) && c != '0')
					state = 2;
				else{
					fprintf(out, "Wrong\n");
					fclose(in);
					fclose(out);
					return 0;
				}
				break;
			case 2:
				if(isdigit(c))
					state = 2;
				else if(c == '.')
					state = 3;
				else if(c == 'E')
					state = 5;
				else if(c == '\n'){
					fprintf(out, "Format1\n");
					fclose(in);
					fclose(out);
					return 0;
				}
				else{
					fprintf(out, "Wrong\n");
					fclose(in);
					fclose(out);
					return 0;
				}
				break;
			case 3:
				if(isdigit(c))
					state = 4;
				else{
					fprintf(out, "Wrong\n");
					fclose(in);
					fclose(out);
					return 0;
				}
				break;
			case 4:
				if(c == 'E')
					state = 5;
				else if(isdigit(c))
					state = 4;
				else if(c == '\n'){
					fprintf(out, "Format1\n");
					fclose(in);
					fclose(out);
					return 0;
				}
				else{
					fprintf(out, "Wrong\n");
					fclose(in);
					fclose(out);
					return 0;
				}
				break;
			case 5:
				if(c == '+' || c == '-')
					state = 6;
				else if(isdigit(c))
					state = 7;
				else{
					fprintf(out, "Wrong\n");
					fclose(in);
					fclose(out);
					return 0;
				}
				break;
			case 6:
				if(isdigit(c))
					state = 7;
				else if(c == '\n'){
					fprintf(out, "Format2\n");
					fclose(in);
					fclose(out);
					return 0;
				}
				else{
					fprintf(out, "Wrong\n");
					fclose(in);
					fclose(out);
					return 0;
				}
				break;
			case 7:
				if(isdigit(c))
					state = 7;
				else if(c == '\n'){
					fprintf(out, "Format2\n");
					fclose(in);
					fclose(out);
					return 0;
				}
				else{
					fprintf(out, "Wrong\n");
					fclose(in);
					fclose(out);
					return 0;
				}
				break;
			default:
				fprintf(out, "Wrong\n");
				fclose(in);
				fclose(out);
				return 0;
				break;
		}
	}
	fclose(in);
	fclose(out);
	return 0;
}