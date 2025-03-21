#include <stdio.h>
#include <string.h>

#define min(X, Y) ((X)<(Y)?(X):(Y))
#define max(X, Y) ((X)>(Y)?(X):(Y))
#define f(X, Y) (((X)-(Y))*((X)-(Y)))
int dp[20001][256], C[16];

int main(void)
{
    int n, m;
    while (scanf("%d%d", &n, &m), n) {
        int i, *prev, *curr, res;
        for(i=0;i<m;++i) scanf("%d", C+i);
        memset(dp, -1, sizeof(dp));
        dp[0][128]=0;
        for(i=0;i<n;++i) {
            int x, j, k;
            scanf("%d", &x);
            prev=dp[i], curr=dp[i+1];
            for(j=0;j<256;++j) if (prev[j]>=0) {
                for(k=0;k<m;++k) {
                    int t=min(255, max(0, j+C[k]));
                    int y=prev[j]+f(x, t);
                    curr[t]=curr[t]<0 ? y : min(curr[t], y);
                }
            }
        }
        res=1<<30;
        for(i=0;i<256;++i) if (curr[i]>=0) res=min(res, curr[i]);
        printf("%d\n", res);
    }
    return 0;
}