#include <stdio.h>
const int MAX = 1000001;
const int MOD = 1000000007;

long long fac[1000001], finv[1000001], inv[1000001];
void COMinit() {
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++){
        fac[i] = fac[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD%i] * (MOD / i) % MOD;
        finv[i] = finv[i - 1] * inv[i] % MOD;
    }
}

long long COM(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * (finv[k] * finv[n - k] % MOD) % MOD;
}
int main(void){
    int x, y;
    scanf("%d%d", &x, &y);
    int n;
    if((x + y) % 3 != 0){
        printf("0\n");
        return 0;
    }
    n = (x + y)/3;

    int x_, y_;
    x_ = x - n;
    y_ = y - n;

    if(x_ < 0 || y_ < 0){
        printf("0\n");
        return 0;
    }

    COMinit();
    printf("%lld\n", COM(x_+y_, x_)% MOD);
    return 0;

}