#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define type 26

int max(int D, int s[][type+1]);
int score_calc(int D, int s[][type+1], int schedul[], int c[type+1], int last[type+1]);
void swap(int D, int s[][type+1], int schedul[], int c[type+1], int last[type+1], int *ini);

int main(void)
{
    int i, j;
    int D, c[type+1], last[type+1];
    int ini;
    clock_t start, stop;
    // 計測開始
    start = clock();
    // 入力
    scanf("%d",&D);
    int s[D+1][type+1], schedul[D+1];
    for(i=1; i<type+1; i++){
        scanf("%d", &c[i]);
    }
    for(i=1; i<D+1; i++){
        for(j=1; j<type+1; j++){
            scanf("%d", &s[i][j]);
        }
    }
    // 初期
    for(i=1; i<D+1; i++){
        schedul[i] = max(i, s);
    }
    for(i=1; i<type+1; i++){
        last[i] = 0;
    }
    ini = score_calc(D, s, schedul, c, last);
    stop = clock();
    // 改善
    srand((unsigned int)time(NULL));
    while((double)(stop - start) / CLOCKS_PER_SEC < 1.990000){
        swap(D, s, schedul, c, last, &ini);
        stop = clock();
    }
    //出力
    for(i=1; i<D+1; i++){
        printf("%d\n",schedul[i]);
    }
    
    return 0;
}

int max(int D, int s[][type+1]) // D日目の満足度が一番高いタイプを返す
{
    int i;
    int max_score = 0, max_type;
    
    for(i=1; i<type+1 ;i++){
        if(s[D][i] > max_score){
            max_score = s[D][i];
            max_type = i;
        }
    }
    return max_type;
}

int score_calc(int D, int s[][type+1], int schedul[], int c[type+1], int last[type+1])
{
    int i,j;
    int score = 0;
    
    for(i=1; i<D+1; i++){
        score += s[i][schedul[i]];
        last[schedul[i]] = i;
        for(j=1; j<type+1; j++){
            score -= c[j] * (i-last[j]);
        }
    }
    
    return score;
}

void swap(int D, int s[][type+1], int schedul[], int c[type+1], int last[type+1], int *ini)
{
    int i;
    int a, b, tmp, imp = 0;
    
    a = rand()%D+1;
    b = rand()%D+1;
    tmp = schedul[a];
    schedul[a] = schedul[b];
    schedul[b] = tmp;
    
    for(i=1; i<type+1; i++){
        last[i] = 0;
    }
    imp = score_calc(D, s, schedul, c, last);
    
    if(imp > *ini){
        *ini = imp;
        
    }else{
        schedul[b] = schedul[a];
        schedul[a] = tmp;
    }
}
