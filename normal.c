#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>

#include<bitcalc.h>

int **parse_params(char *a, char *b) {
	int *v1 = malloc(sizeof(int)*strlen(a));
	int *v2 = malloc(sizeof(int)*strlen(b));
	int **v2d = malloc(sizeof(int*)*2);
	char zeros[1000] = {0};
	char tmpbuf[100] = {0};
	for(signed int i = strlen(a) - 1,ii=0; i>=0;--i,++ii) {
 		char nig = a[i];
		sprintf(tmpbuf, "%c%s", nig, zeros);
		v1[ii] = atoi(tmpbuf);
		memcpy(zeros + ii,"0",1);
	}
	memset(zeros,'\0',1000);
	for(signed int i = strlen(b) - 1,ii=0; i>=0;--i,++ii) {
 		char nig = b[i];
		sprintf(tmpbuf, "%c%s", nig, zeros);
		v2[ii] = atoi(tmpbuf);
		memcpy(zeros + ii,"0",1);
	}
	v2d[0] = v1;
	v2d[1] = v2;
	return v2d;
}

int *whole_array(int start) {
	int *v = malloc(sizeof(int)*4);
	struct Llist *list = get_last_digit_as_tree(start);
	int  last_i = get_last_digit2(start);
	int res = treverse_tree_logical(list);
	v[2] = (start/100) * 100;
	v[1] = res;
	v[0] = last_i;
	v[3] = 0;
	return v;
}

int multiply2(int a, int b) {
	int *v1 = whole_array(a);
	int *v2 = whole_array(b);
	int ret = 0;
	for(int i=0;*(v2 + i);++i) {
		int out = 0;
		for(int j=0;*(v1 + j);++j) {
			int tmp = 0;
			for(int ii=0;ii<v2[i];++ii)	
				tmp+=v1[j];
			out+=tmp;
		}
		ret+=out;
	}
	free(v1);
	free(v2);
	return ret;
}

int multiply(char *a, char *b) {
	int **v2d = parse_params(a,b);
	int ret = 0;
	for(int i = 0;i<strlen(b);++i) {
		int out = 0;
		for(int j=0;j<strlen(a);++j) {
			int tmp = 0;
			for(int ii = 0;ii<v2d[1][i];++ii)
				tmp+=v2d[0][j];
			out+=tmp;
		}
		ret+=out;
	}
	return ret;
}

int main(int argc, char **argv) {
	int ret_main = 0;
	if(argc < 3) {
		fprintf(stderr, "give two numbers to multiply\n");
		return 1;
	}
	int ret0 = multiply(argv[1],argv[2]);
	int ret1 = multiply2(atoi(argv[1]),atoi(argv[2]));
	printf("normal -> %d\n", ret0);
	printf("explicit -> %d\n", ret1);
	printf("exiting with %d\n", ret0 == ret1);
	return ret_main;

}
