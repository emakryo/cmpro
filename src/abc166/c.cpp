#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__);
#else
#define dbg(...) 
#endif

int main() {
	ios_base::sync_with_stdio(false);
	int N, M;
	cin >> N >> M;
	vector<ll> H(N);
	for(int i=0; i<N; i++) cin >> H[i];
	vector<vector<int>> graph(N);
	set<pair<int, int>> edge;
	for(int i=0; i<M; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		if(a>b) swap(a,b);
		if(edge.count({a, b})>0) continue;
		graph[a].push_back(b);
		graph[b].push_back(a);
		edge.insert({a,b});
	}

	int ans = 0;
	for(int i=0; i<N; i++){
		bool ok=true;
		for(int j: graph[i]){
			if(H[i]<=H[j]) ok = false;
		}
		if(ok) ans++;
	}
	cout << ans << endl;

	return 0;
}
