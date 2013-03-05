/*【问题描述】
泊松分布是一种常用的离散型概率分布，数学期望为m的泊松分布的分布函数定义如下：
P(m, k) = mk * e-m/k!  (k = 0, 1, 2, 3, …)
对于给定的m和k (0<m<2000, 0<= k < 2500)，计算其概率，以科学格式输出，保留小数点后6位有效数字。
【输入形式】
输入文件为当前目录下的poisson.in。
文件中包含两个数字，分别为m,k的值。
【输出形式】
输出文件为当前目录下的poisson.out。
文件中输出泊松分布的值，值以科学格式输出，保留小数点后6位有效数字。
【输入样例】
1  0
【输出样例】
3.678794e-01
【运行时限】
1秒
【评分标准】
可以使用数学库函数，误差不超过0.000001。
*/
#include<stdio.h>
#include<math.h>
main(){
	FILE *in, *out;
	int m, k, i;
	double temp1, temp2 = 0, temp3;
	in = fopen("poisson.in", "r");
	out = fopen("poisson.out", "w");
	//in = stdin;
	//out = stdout;
	
	fscanf(in, "%d%d", &m, &k);
	temp1 = k * log(m) - m;
	for(i = 1;i <= k;i++)
		temp2 += log(i);
	temp3 = exp((temp1 - temp2));
	fprintf(out, "%e", temp3);
	fclose(in);
	fclose(out);
}

