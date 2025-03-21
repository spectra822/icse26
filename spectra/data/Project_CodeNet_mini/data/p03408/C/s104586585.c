#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(void){

    int N;

    scanf("%d", &N);

    char s[N][11];

    for(int i = 0; i < N; i++){
        scanf("%s", s[i]);
    }

    int M;

    scanf("%d", &M);

    char t[M][11];

    for(int i = 0; i < M; i++){
        scanf("%s", t[i]);
    }

    int max = 0;

    for(int i = 0; i < N; i++){
        int m = 0;
        for(int j = 0; j < N; j++){
            if(strcmp(s[i], s[j]) == 0){
                m++;
            }
        }
        for(int j = 0; j < M; j++){
            if(strcmp(s[i], t[j]) == 0){
                m--;
            }
        }
        if(m > max){
            max = m;
        }
    }

    printf("%d\n", max);

    return 0;
}