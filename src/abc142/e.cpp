#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
#ifdef DEBUG
#define debug(...) pr(any{__VA_ARGS__})
#define debugv(x) pr((x))
#else
#define debug(...)
#define debugv(x)
#endif

int main(){
	int N, M; cin >> N >> M;
	vector<int> A(M), C(M);
	for(int i=0; i<M; i++){
		int b;
		cin >> A[i] >> b;
		for(int j=0; j<b; j++){
			int c; cin >> c;
			C[i] += 1<<(c-1);
		}
	}

	vector<int> cost(1<<N, 1e9);
	queue<pair<int, int>> que;
	for(int i=0; i<M; i++) que.push({C[i], A[i]});
	while(!que.empty()){
		int x = que.front().first;
		int c = que.front().second;
		que.pop();
		if(cost[x] <= c) continue;
		cost[x] = c;
		for(int i=0; i<1<<N; i++){
			int y = x | i;
			if(cost[i]==1e9) continue;
			if(cost[y] > cost[x]+cost[i]){
				que.push({y, cost[x]+cost[i]});
			}
		}
	}

	if(cost[(1<<N)-1] == 1e9) cout << -1 << endl;
	else cout << cost[(1<<N)-1] << endl;

	return 0;
}
