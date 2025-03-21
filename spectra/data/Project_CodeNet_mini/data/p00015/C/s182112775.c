#include <stdio.h>
#include <string.h>
#define LEN 128

void convert(char charNum[], int intNum[]) {
    int i, j = 0;
    for (i = (int)strlen(charNum) - 1; i >= 0 ; i --) {
        intNum[j] = (int)charNum[i] - 48;
        j ++;
    }
}

int main(int argc, const char * argv[]) {
    int dataSet;
    int count = 1;
    scanf("%d", &dataSet);
    char firstNum[LEN], secondNum[LEN];
    int fNum[LEN], sNum[LEN], sum[LEN];
    int i, j, k, l;
    while (count <= dataSet) {
        count ++;
        while (scanf("%s", firstNum) != EOF) {
            break;
        }
        while (scanf("%s", secondNum) != EOF) {
            break;
        }
        if (strlen(firstNum) > 80 || strlen(secondNum) > 80) {
            printf("overflow\n");
            continue;
        }
        for (i = 0; i < LEN; i ++) {
            fNum[i] = 0;
            sNum[i] = 0;
            sum[i] = 0;
        }
        convert(firstNum, fNum);
        convert(secondNum, sNum);
        for (i = 0; i < LEN; i ++) {
            sum[i] = fNum[i] + sNum[i];
        }
        for (i = 0; i < LEN; i ++) {
            if (sum[i] >= 10) {
                sum[i] %= 10;
                sum[i + 1] += 1;
            }
        }
        k = 0;
        j = LEN - 1;
        while (j >= 0) {
            if (sum[j] == 0 && j != 0) {
                k ++;
                j --;
            } else {
                break;
            }
        }
        if (k < LEN - 80) {
            printf("overflow");
        } else {
            for (l = LEN - k - 1; l >= 0; l --) {
                printf("%d", sum[l]);
            }
        }
        printf("\n");
    }
    return 0;
}

