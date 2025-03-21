#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int min(int a, int b){
    if(a < b){
        return a;
    }else{
        return b;
    }
}

int main(void){

    int N, M;

    scanf("%d%d", &N, &M);

    int a[M], b[M], c[M];
    int dist[N][N];

    for(int i = 0; i < M; i++){
        scanf("%d%d%d", &a[i], &b[i], &c[i]);
        a[i]--;
        b[i]--;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i == j){
                dist[i][j] = 0;
            }else{
                dist[i][j] = 1000000000;
            }
        }
    }

    for(int i = 0; i < M; i++){
        dist[a[i]][b[i]] = min(dist[a[i]][b[i]], c[i]);
        dist[b[i]][a[i]] = min(dist[b[i]][a[i]], c[i]);
    }

    for(int k = 0; k < N; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    int ans = M;

    for(int i = 0; i < M; i++){
        int f = 1;
        for(int j = 0; j < N; j++){
            if(dist[j][a[i]] + c[i] == dist[j][b[i]]){
                f = 0;
            }
        }
        if(f == 0){
            ans--;
        }
    }

    printf("%d\n", ans);

    return 0;
}