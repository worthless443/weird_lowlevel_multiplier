#define __USE_UTILS
struct Store {
	int start,mskdout,start_bit,mask_bit;
	int  mask_bit_prev;
	int value;
	int bound;
};
struct Llist {
	int round,diff;
	struct Llist *next;
	int start;
	int n_diff;
};

int get_last_digit2(int start);
int treverse_tree_logical(struct Llist *list);
struct Llist *get_last_digit_as_tree(int start);
