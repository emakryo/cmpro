//#include<iostream>
//#include<iomanip>
#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
const int Nmax = 100000;
int N,Q;
int par[Nmax+1];
bool marked[Nmax+1];

int find(int x){
	if(marked[x]) return x;
	int m = find(par[x]);
	return m;
}


int main(){
	while(true){
		scanf("%d%d", &N, &Q);
		if(N==0&&Q==0) break;
		par[1] = 1;
		for(int i=2; i<=N; i++){
			int p;
			scanf("%d", &p);
			par[i] = p;
		}
		ll ans = 0;
		fill(marked, marked+N+1, false);
		marked[1] = true;
		for(int i=0; i<Q; i++){
			char s[5];
			int v;
			scanf("%s%d", s, &v);
			if(s[0] == 'Q'){
				ans += find(v);
			}
			else{
				marked[v] = true;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
