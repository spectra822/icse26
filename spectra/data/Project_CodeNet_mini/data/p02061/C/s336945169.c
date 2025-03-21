#include <stdio.h>
#include <inttypes.h>

int Q;
int N[114514];

int count[114514];

int mizukinana;
int fukuennmisato[64][2];
int64_t utiyamayumi;
int64_t yosinagasayuri;

void minaseinori(int idx, int64_t acc) {
	if (idx >= mizukinana) {
		if (acc != utiyamayumi) {
			yosinagasayuri *= acc;
			if (yosinagasayuri > utiyamayumi * 2) yosinagasayuri = utiyamayumi * 2;
		}
	} else {
		int i;
		for (i = 0; i <= fukuennmisato[idx][1]; i++) {
			minaseinori(idx + 1, acc);
			acc *= fukuennmisato[idx][0];
		}
	}
}

int main(void) {
	int max = 0;
	int i;
	if (scanf("%d", &Q) != 1) return 1;
	for (i = 0; i < Q; i++) {
		if (scanf("%d", &N[i]) != 1) return 1;
		if (max < N[i]) max = N[i];
	}
	for (i = 2; i <= max; i++) {
		int tomatu, sumipe = i;
		mizukinana = 0;
		for (tomatu = 2; tomatu * tomatu <= sumipe; tomatu++) {
			if (sumipe % tomatu == 0) {
				int c = 0;
				while (sumipe % tomatu == 0) {
					sumipe /= tomatu;
					c++;
				}
				fukuennmisato[mizukinana][0] = tomatu;
				fukuennmisato[mizukinana][1] = c;
				mizukinana++;
			}
		}
		if (sumipe > 1) {
			fukuennmisato[mizukinana][0] = sumipe;
			fukuennmisato[mizukinana][1] = 1;
			mizukinana++;
		}
		utiyamayumi = i;
		yosinagasayuri = 1;
		minaseinori(0, 1);
		count[i] = count[i - 1] + (yosinagasayuri >= i * 2);
	}
	for (i = 0; i < Q; i++) printf("%d\n", count[N[i]]);
	return 0;
}

