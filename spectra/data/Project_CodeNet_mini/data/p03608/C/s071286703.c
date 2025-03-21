#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int d[201][201];
int r[9];
int res;
bool used[9];
int N, M, R;

void dfs(int c, int las, int dist){
    if(c == R + 1){
        if(res > dist){
            res = dist;
        }
        return;
    }

    for(int i = 1; i <= R; i++){
        if(!used[i]){
            used[i] = true;
            if(las == -1){
                dfs(c+1, i, 0);
            }else{
                dfs(c+1, i, dist + d[r[las]][r[i]]);
            }
            used[i] = false;
        }
    }
}

int main(void){

    scanf("%d%d%d", &N, &M, &R);

    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(i != j){
                d[i][j] = 1000000000;
            }
        }
    }

    for(int i = 1; i <= R; i++){
        scanf("%d", &r[i]);
    }

    for(int i = 1; i <= M; i++){
        int A, B, C;
        scanf("%d%d%d", &A, &B, &C);
        if(d[A][B] > C){
            d[A][B] = d[B][A] = C;
        }
    }

    for(int k = 1; k <= N; k++){
        for(int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                if(d[i][j] > d[i][k] + d[k][j]){
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }

    res = 1000000000;

    dfs(1, -1, 0);

    printf("%d\n", res);

    return 0;
}