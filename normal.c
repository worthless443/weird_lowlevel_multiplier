#include<stdi.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>

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
	if(argc < 3) {
		fprintf(stderr, "give two numbers to multiply\n");
		return 1;
	}
	int ret = multiply(argv[1],argv[2]);
	printf("%d\n", ret);
}
