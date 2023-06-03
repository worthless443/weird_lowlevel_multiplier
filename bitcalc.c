#include<stdio.h>
#include<stddef.h>
#include<stdlib.h>

//#include<utils.h>

struct Store {
	int start,mskdout,start_bit,mask_bit;
	int  mask_bit_prev;
	int value;
	int bound;
};
struct Llist {
	int round,diff;
	struct Llist *next;
};

int check_alignment(int _n, struct Store store) {
	int n = _n;
	int width = 0;
	int mask_string = 1;
	while(n) (n>>=1,++width);
	mask_string <<= (width - 1);
	store.bound = (_n << 1) & mask_string;
	return ((_n  & mask_string) == _n);
}

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

// this part is a party trick
struct Llist *get_last_digit_as_tree(int start) {
	struct Llist *list = malloc(sizeof(struct Llist));
	if((start ^ (start - 1)) > start) return NULL;
	int mask = 1, _start = start,n=0;
	int round;
	for(;_start>>=1;mask<<=1,++n);
	int diff = start ^ mask;
	if(n & 2 && n % 2) (round = mask + 2,diff-=2);
	else if(n & 2 && !(n % 2)) (round = mask - 4,diff+=4);
	else if(!(n & 2) && !(n % 2)) (round = mask + 4,diff-=4);
	else if(!(n & 2) && n % 2) (round = mask - 2,diff+=2);
	list->round = round;
	list->diff = diff;
	if(!diff) {
		list->next = NULL;
		return list;
	}
	printf("%d %d\n", round, diff);
	list->next = get_last_digit_as_tree(diff);
	return list;
}

//wow! very smart
int get_last_digit2(int start) {
	int mask = 1, _start = start,n=0;
	int round;
	for(;_start>>=1;mask<<=1,++n);
	int diff = start ^ mask;
	if(n & 2 && n % 2) (round = mask + 2,diff-=2);
	else if(n & 2 && !(n % 2)) (round = mask - 4,diff+=4);
	else if(!(n & 2) && !(n % 2)) (round = mask + 4,diff-=4);
	else if(!(n & 2) && n % 2) (round = mask - 2,diff+=2);
	if(start < 10) {
		if(start<0)
			return round + diff;
		return start;
	}
	return get_last_digit2(diff);
}

// utils
void print_list(struct Llist *list) {
	printf("-> %d + %d\n", list->round,list->diff);
	if(list->next == NULL) return;
	print_list(list->next);
}

void free_list(struct Llist *list) {
	if(list->next == NULL) return;
	print_list(list->next);
	free(list);
} 

int main(int argc, char **argv) {
	int start = argc < 2 ? 355 : atoi(argv[1]);
	printf("%d\n", get_last_digit2(start))	;
	//struct Llist *list = get_last_digit2(start);
	//print_list(list);
	//free_list(list);
	//struct Store store;
	//check_alignment(start,store);
	//get_last_digit(&store,start);
	//printf("%d\n", store.value);
	return 0;
}
