#include <stdio.h>
int a[100000], b[100000], par[100000], root_cnt[100000];
int root(int x){
    if(par[x] == x){return x;}
    return par[x] = root(par[x]);
}

int unite(int x, int y){
    int rx = root(x);
    int ry = root(y);
    if(rx == ry){
        return 0;
    }
    par[rx] = ry;
    return 1;
}

int same(int x, int y){
    int rx = root(x);
    int ry = root(y);
    if(rx == ry){
        return 1;
    }
    return 0;
}

long long int ans[100000];
int main(void){
    long long int n, m;
    int i, j, k;
    scanf("%lld%lld", &n, &m);
    for(i = 0; i < m; i++){
        scanf("%d%d", &a[i], &b[i]);
        a[i]--;
        b[i]--;
    }

    for(i = 0; i < n; i++){
        par[i] = i;
        root_cnt[i] = 1;
    }

    ans[m-1] = n*(n-1)/2;
    root_cnt[root(b[m-1])] += root_cnt[root(a[m-1])];
    root_cnt[root(a[m-1])] = 0;
    unite(a[m-1], b[m-1]);//bのrootにaが統合される
    if(m-2 >= 0){
        ans[m-2] = n*(n-1)/2 - 1;
    }
    for(i = m-2; i >= 0; i--){
        if(same(a[i], b[i])){
            ans[i-1] = ans[i];
        }else{
            ans[i-1] = ans[i] - root_cnt[root(b[i])] * root_cnt[root(a[i])];
            root_cnt[root(b[i])] += root_cnt[root(a[i])];
            root_cnt[root(a[i])] = 0;
            unite(a[i], b[i]);//bのrootにaが統合される
            
            
        }
    }

    for(i = 0; i < m; i++){
        printf("%lld\n",ans[i]);
    }
}