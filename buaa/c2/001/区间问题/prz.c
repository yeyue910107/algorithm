#include<stdio.h>
enum {MAX = 50000};

typedef struct{
	long sup;//上界
	long inf;//下界
}INTERVAL;
void insertSort(long array[], int n);
main()
{
	FILE *in, *out;
	long sup[MAX], inf[MAX];
	int i, n, flag = 0;
	in = fopen("prz.in", "r");
	out = fopen("prz.out", "w");
	//test = fopen("test.tet", "w");

	//in = stdin;
	//out = stdout;
	fscanf(in, "%ld", &n);
	for(i = 0;i < n;i++){
		fscanf(in, "%ld%ld", &sup[i], &inf[i]);
	}
	insertSort(sup, n);
	insertSort(inf, n);
	fprintf(out, "%ld ", sup[0]);
		for(i = 0;i < n;i++){
			if(flag == 1){
				fprintf(out, "%ld ", sup[i]);
				flag = 0;
			}
			if(i == n - 1)
				fprintf(out, "%ld\n", inf[i]);
			else if(inf[i] < sup[i + 1]){
				fprintf(out, "%ld\n", inf[i]);
				flag = 1;
			}
			else if(inf[i] >= sup[i + 1])
				continue;
				//fprintf(out, "%ld ", sup[i + 1]);
		}
	fclose(in);
	fclose(out);
}

void insertSort(long array[], int n){
	int i, j;
	long temp;

	for(i = 0;i < n - 1;i++){
		temp = array[i + 1];
		for(j = i + 1;j > 0 && temp < array[j - 1];j--)
			array[j] = array[j - 1];
		array[j] = temp;
	}
}