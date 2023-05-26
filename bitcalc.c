#include<stdio.h>
#include<stddef.h>

struct Store {
	int start,mskdout,start_bit,mask_bit;
	int  mask_bit_prev;
	int value;
};

// this part is bad
void get_last_digit(struct Store *store, int _start) { 
	store->start = _start;
	int w = 0,w1 = 0, start = _start;
	int tmp2 = 1;
	while(start) {
		int tmp = start, i_c = 0, e = 1;
		while(tmp!=1) {
			e = (e << 1) + 1;
			tmp>>=1;
		}
		e <<= 1;
		if(((start ^ e) - start) != 2) w1 = w;
		++w;
		start>>=1;
	}
	store->start_bit = w;
	store->mask_bit = w1;
	for(int i=1;i<w1;++i)
		tmp2=(tmp2<<1) + 1;
	store->mask_bit_prev = tmp2;
	tmp2 &= _start;
	store->mskdout = tmp2;
	tmp2 >>= 3;
	tmp2 |= 1;
	store->value = tmp2;
}

int main(int argc, char **argv) {
	int start = argc < 2 ? 355 : atoi(argv[1]);
	struct Store store;
	get_last_digit(&store,start);
	printf("%d\n", store.value);
	return 0;
}
