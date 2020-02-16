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
	int H, W;
	cin >> H >> W;
	vector<string> S(H);
	for(int i=0; i<H; i++) cin >> S[i];

	vector<vector<ll>> adj(H*W, vector<ll>(H*W, 1e9));

	for(int x=0; x<H; x++) for(int y=0; y<W; y++){
		int dx[] = {0, 1};
		int dy[] = {1, 0};
		for(int i=0; i<2; i++){
			if(x+dx[i]<H&&y+dy[i]<W&&S[x][y]=='.' && S[x+dx[i]][y+dy[i]]=='.'){
				adj[x*W+y][(x+dx[i])*W+y+dy[i]]=1;
				adj[(x+dx[i])*W+y+dy[i]][x*W+y]=1;
			}
		}
	}

	for(int i=0; i<H*W; i++) debugv(adj[i]);

	vector<vector<ll>> dist(adj);

	for(int k=0; k<H*W; k++) for(int i=0; i<H*W; i++) for(int j=0; j<H*W; j++){
		dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
		if(i==0 && dist[i][j]==dist[i][k]+dist[k][j]) debug(i, j, k, dist[i][j], dist[i][k], dist[k][j]);
	}

	ll ans = 0;
	for(int i=0; i<H*W; i++) for(int j=0; j<H*W; j++){
		if(i==j || dist[i][j] >= 1e9) continue;
		debug(i, j, dist[i][j]);
		ans = max(ans, dist[i][j]);
	}
	cout << ans << endl;

	return 0;
}
