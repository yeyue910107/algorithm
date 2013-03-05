/*������������
�Ϸ���ʵ����д��ʽ��һ���ʽ�Ϳ�ѧ��ʽ���֡��ֱ��������£�
һ���ʽΪ��������д��ʽ����Ϊ�������ֺ�С�����������֣��м����С����.�ָ������������ʼ���ܺ������Ż򸺺ţ�
֮��Ϊ����ǰ��������ִ���С����������0-9ʮ���ַ���ɵ����ⳤ���ַ�������С������Ϊ0ʱ��С�����ֺ�С�������ʡ�ԡ�
��ѧ��ʽ��ϵ�����ֺ�ָ��������������ɣ��м���Ӣ����ĸE�ָ���ϵ������Ϊʵ����д��һ���ʽ��ָ������Ϊ�ɴ������������ִ���
���磬+2��-1.56Ϊһ���ʽ��ʵ������6.2E-2��-9E8Ϊ��ѧ��ʽ��ʵ����
��̷�����Щ������д����ȷ�ģ��������ַ�ʽ��д�ġ�
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�real.in��
���ļ�����һ���ַ������Իس�����������ʾһ�����ݣ��޶���ո񣩡�
�������ʽ��
����ļ�Ϊ��ǰĿ¼�µ�real.out��
���ļ���һ�С�����������ݵ���д�ǷǷ��ģ����Wrong�����������������һ���ʽ��д�ģ������Format1����
������������ÿ�ѧ��ʽ��д�ģ������Format2���������ĩβ��Ҫ��һ���س�����Ϊ������
����������1��
+1.23
���������1��
Format1
����������2��
-5.1.1
���������2��
Wrong
����������3��
-5.1E-2
���������3��
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