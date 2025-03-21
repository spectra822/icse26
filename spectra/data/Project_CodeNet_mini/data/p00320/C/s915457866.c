#include <stdio.h>

/* {1,2,3} -> ... -> {3,2,1} */
int next_permutation(int arr[],int n) {
	int target;
	int i;
	int temp;
	for (i = n - 2; i >= 0; i--) {
		if (arr[i] < arr[i + 1]) break;
	}
	if (i < 0) return 0;
	target = i;

	for (i = 0; target + i + 1 < n - i - 1; i++) {
		temp = arr[target + 1 + i];
		arr[target + 1 + i] = arr[n - 1 - i];
		arr[n - i - 1] = temp;
	}

	for (i = target + 1; i < n; i++) {
		if (arr[i] > arr[target]) break;
	}
	temp = arr[i];
	arr[i] = arr[target];
	arr[target] = temp;
	return 1;
}

/*
 1
4025
 3
*/
int connect[12][4] = {
	/* {pos, h/w, pos, h/w} */
	{0, 1, 1, 1},
	{0, 0, 2, 0},
	{0, 1, 3, 1},
	{0, 0, 4, 0},

	{1, 0, 2, 1},
	{2, 1, 3, 0},
	{3, 0, 4, 1},
	{4, 1, 1, 0},

	{5, 1, 1, 1},
	{5, 0, 4, 0},
	{5, 1, 3, 1},
	{5, 0, 4, 0}
};

int main(void) {
	int hw[6][2];
	int i;
	int permutation[6] = {0, 1, 2, 3, 4, 5};
	int rotate;
	for (i = 0; i < 6; i++) {
		if (scanf("%d%d", &hw[i][0], &hw[i][1]) != 2) return 1;
	}
	do {
		for (rotate = 0; rotate < (1 << 6); rotate++) {
			int ng = 0;
			for (i = 0; i < 12; i++) {
				int len1 = hw[permutation[connect[i][0]]][connect[i][1] ^ ((rotate >> connect[i][0]) & 1)];
				int len2 = hw[permutation[connect[i][2]]][connect[i][3] ^ ((rotate >> connect[i][2]) & 1)];
				if (len1 != len2) {
					ng = 1;
					break;
				}
			}
			if (!ng) {
				puts("yes");
				return 0;
			}
		}
	} while (next_permutation(permutation, 6));
	puts("no");
	return 0;
}