#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<typename T>
ostream& operator<<(ostream &os, vector<T> &v){
	string sep = " ";
	if(v.size()) os << v[0];
	for(int i=1; i<v.size(); i++) os << sep << v[i];
	return os;
}

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

	int H, W; cin >> H >> W;
	vector<vector<ll>> A(H, vector<ll>(W));
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			cin >> A[i][j];
		}
	}

	ll ans = 1e18;
	for(int sx=0; sx<H; sx++) for(int sy=0; sy<W; sy++){
		int s = sx*W+sy;
		priority_queue<pair<ll, int>, vector<pair<ll, int>>,
			greater<pair<ll, int>>> que;
		vector<ll> dist(H*W, 1e18);
		que.push({0, s});
		while(!que.empty()){
			ll a = que.top().first;
			int n = que.top().second;
			int x = n/W;
			int y = n%W;
			que.pop();
			if(a>=dist[n]) continue;
			dist[n] = a;
			int dx[] = {0, -1, 0, 1};
			int dy[] = {-1, 0, 1, 0};
			for(int k=0; k<4; k++){
				int nx = x + dx[k];
				int ny = y + dy[k];
				if(0<=nx&&nx<H&&0<=ny&&ny<W){
					ll d = a + A[nx][ny];
					int u = nx*W+ny;
					if(d<dist[u]){
						que.push({d, u});
					}
				}
			}
		}
		dbg(sx, sy, dist[(H-1)*W],dist[W-1],dist[(H-1)*W+W-1]);

		ans = min(ans, A[sx][sy]+dist[(H-1)*W]+dist[W-1]+dist[(H-1)*W+W-1]);
	}
	cout << ans << endl;
	return 0;
}
