#include <stdio.h>
#include <string.h>

#define MOD (10007)

int main(void)
{
    int N;
    char in[1001];
    int key, key_prev, key_prev_prev;
    int schedule[8], schedule_next[8];
    int conv;
    int i, j, k;
    
    
    scanf("%d", &N);
    scanf("%s", in);

    key_prev = 1;   // 最初に鍵を持っているのはJ
    key_prev_prev = 0;
 
 
    memset(schedule, 0, sizeof(schedule));
    schedule[1] = 1;
    
    for (i = 0; i < N; i++){
        switch (in[i]){
          case 'J':
            key = 1;
            break;
          
          case 'O':
            key = 2;
            break;
            
          case 'I':
            key = 4;
            break;
        }
        memset(schedule_next, 0, sizeof(schedule_next));
 
        if (i == 0){
            for (j = 0; j <= 7; j++){
                if ((j & (key | key_prev)) == (key | key_prev)){
                    schedule_next[j] = 1;
                }
            }
            key_prev_prev = key_prev;
            key_prev = key;
            memcpy(schedule, schedule_next, sizeof(schedule));

//for (j = 0; j <= 7; j++){
//    printf("(%d:%d)", j, schedule[j]);
//}
//printf("\n");
            continue;
        }
        for (j = 0; j <= 7; j++){
//            if ((j & (key | key_prev)) == (key | key_prev)){
            if ((j & (key | key_prev)) != 0){
                for (k = 0; k <= 7; k++){

                    if (((k & j) != 0) && ((k & key) != 0)){
//printf("(%d,%d,%d)", k, j, key);
                        schedule_next[k] += schedule[j];
						schedule_next[k] %= MOD;
                    }
                }
            }
        }
        
        key_prev_prev = key_prev;
        key_prev = key;
        memcpy(schedule, schedule_next, sizeof(schedule));
        
//for (j = 0; j <= 7; j++){
//    printf("[%d:%d]", j, schedule[j]);
//}
//printf("\n");

    }
    conv = 0;
    for (i = 0; i <= 7; i++){
        conv += schedule[i];
		conv %= MOD;
    }
    
    printf("%d\n", conv);
    
    return (0);
}