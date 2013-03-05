/*������������
���ɷֲ���һ�ֳ��õ���ɢ�͸��ʷֲ�����ѧ����Ϊm�Ĳ��ɷֲ��ķֲ������������£�
P(m, k) = mk * e-m/k!  (k = 0, 1, 2, 3, ��)
���ڸ�����m��k (0<m<2000, 0<= k < 2500)����������ʣ��Կ�ѧ��ʽ���������С�����6λ��Ч���֡�
��������ʽ��
�����ļ�Ϊ��ǰĿ¼�µ�poisson.in��
�ļ��а����������֣��ֱ�Ϊm,k��ֵ��
�������ʽ��
����ļ�Ϊ��ǰĿ¼�µ�poisson.out��
�ļ���������ɷֲ���ֵ��ֵ�Կ�ѧ��ʽ���������С�����6λ��Ч���֡�
������������
1  0
�����������
3.678794e-01
������ʱ�ޡ�
1��
�����ֱ�׼��
����ʹ����ѧ�⺯����������0.000001��
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

