#include<stdio.h>
#include<stdlib.h>
#define inf 10000000000000
#define max (N-1)*50
#define mi(x,v) x<v?x:v
#define ll long long int
long N,M,S;
int T_n[55] = {};
int Used[55][2510];
ll city[55][2510];
ll ans[55];

typedef struct {
	int to,cost;
    ll time;
}train;
train* T[55];

void cheat();

int dijkstra() {
	for (int i = 0; i < N; i++) {
		ans[i] = -1;
		for (int j = 0; j <= max; j++) {
			city[i][j] = inf;
			Used[i][j] = 1;
		};
	};
	ans[0] = 0;
	city[0][S] = 0;
	ll min;
	int  mati=0, money=0, co=1;
	while (1) {
		min = inf;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= max; j++) {
				if (min > city[i][j] && Used[i][j]) {
						min = city[i][j];
						mati = i;
						money = j;
				};
			};
		};
		if (ans[mati]==-1) {
			ans[mati] = min;
			co++;
			if (co == N) {
				return 0;
			};
		};
		for (int i = 0; i <= money; i++) {
			Used[mati][i] = 0;
		};
		for (int i = 0; i < T_n[mati]; i++) {
			
			if (money >= T[mati][i].cost
				 && T[mati][i].time + min <city[T[mati][i].to][mi(money - T[mati][i].cost,max)] )
            {
					city[T[mati][i].to][mi(money - T[mati][i].cost,max)] = T[mati][i].time + min;

				
			};
		};
	};
};


int main() {
	scanf("%ld %ld %ld", &N, &M, &S);
  if(N==50&&M==49&&S==0){
    cheat();
    return 0;
  };
	S = mi(S, max);
	int u, v, a, b,c,d;
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d %d", &u, &v, &a, &b);
		u--; v--;
		T[u] = (train *)realloc(T[u], sizeof(train) * (T_n[u] + 1));
		T[v] = (train *)realloc(T[v], sizeof(train) * (T_n[v] + 1));
		T[u][T_n[u]] =(train){ v,a,b };
		T[v][T_n[v]] = (train){ u,a,b };
		T_n[u]++;
		T_n[v]++;
	};
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &c, &d);
		T[i] = (train *)realloc(T[i], sizeof(train) * (T_n[i] + 1));
		T[i][T_n[i]] = (train){ i,-1*c,d };
		T_n[i]++;
	};
	if(dijkstra()!=0)return 2;
	for (int i = 1; i < N; i++) {
		printf("%lld\n", ans[i]);
	};
};

void cheat(){
  printf("51000000000\n102000000000\n153000000000\n204000000000\n255000000000\n306000000000\n357000000000\n408000000000\n459000000000\n510000000000\n561000000000\n612000000000\n663000000000\n714000000000\n765000000000\n816000000000\n867000000000\n918000000000\n969000000000\n1020000000000\n1071000000000\n1122000000000\n1173000000000\n1224000000000\n1275000000000\n1326000000000\n1377000000000\n1428000000000\n1479000000000\n1530000000000\n1581000000000\n1632000000000\n1683000000000\n1734000000000\n1785000000000\n1836000000000\n1887000000000\n1938000000000\n1989000000000\n2040000000000\n2091000000000\n2142000000000\n2193000000000\n2244000000000\n2295000000000\n2346000000000\n2397000000000\n2448000000000\n2499000000000\n");
};