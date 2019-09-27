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
	const int dx[] = {1, -1, 0, 0};
	const int dy[] = {0, 0, -1, 1};
	int R, C, K;
	cin >> R >> C >> K;
	vector<string> S(R);
	for(int i=0; i<R; i++){
		cin >> S[i];
	}

	int sx, sy, cx, cy, gx, gy;
	vector<int> ex, ey;
	for(int x=0; x<R; x++) for(int y=0; y<C; y++){
		if(S[x][y]=='S'){
			sx = x; sy = y;
		} else if(S[x][y]=='C'){
			cx = x; cy = y;
		} else if(S[x][y]=='G'){
			gx = x; gy = y;
		} else if(S[x][y]=='E'){
			ex.push_back(x);
			ey.push_back(y);
		}
	}

	int ans = 1e9;
	for(int px=0; px<R; px++) for(int py=0; py<C; py++){
		if(S[px][py] == 'T') continue;
		vector<vector<vector<int>>> dist(R, vector<vector<int>>(C, vector<int>(K+1, 1e9)));
		queue<pair<int, pair<int, int>>> que;
		que.push({0, {px, py}});
		dist[px][py][0] = 0;
		for(int k=0; k<=K; k++){
			while(!que.empty()){
				auto p = que.front();
				que.pop();
				int d = p.first;
				int x = p.second.first;
				int y = p.second.second;
				if(dist[x][y][k] < d) continue;
				debug(k, x, y, d);
				dist[x][y][k] = d;
				for(int j=0; j<4; j++){
					int nx = x+dx[j];
					int ny = y+dy[j];
					if(nx<0||R<=nx||ny<0||C<=ny) continue;
					if(S[nx][ny]=='T'||S[nx][ny]=='E'||dist[nx][ny][k] <= d+1) continue;
					que.push({d+1, {nx, ny}});
				}
			}
			if(k==K) break;
			for(int x=0; x<R; x++) for(int y=0; y<C; y++) {
				dist[x][y][k+1] = dist[x][y][k];
			}
			for(int i=0; i<ex.size(); i++){
				int x = ex[i];
				int y = ey[i];
				int d = 1e9;
				for(int j=0; j<4; j++){
					int nx=x+dx[j];
					int ny=y+dy[j];
					if(0<=nx&&nx<R&&0<=ny&&ny<C) d = min(d, dist[nx][ny][k]);
				}
				if(d<1e9) que.push({d+1, {x, y}});
			}
		}
		if(S[px][py] == 'E'){
			if(dist[sx][sy][K-2]<1e9&&dist[cx][cy][K-2]<1e9&&dist[gx][gy][K-2]<1e9)
				ans = min(dist[sx][sy][K-2]+2*dist[cx][cy][K-2]+dist[gx][gy][K-2], ans);
		} else {
			if(dist[sx][sy][K-1]<1e9&&dist[cx][cy][K-1]<1e9&&dist[gx][gy][K-1]<1e9)
				ans = min(dist[sx][sy][K-1]+2*dist[cx][cy][K-1]+dist[gx][gy][K-1], ans);
		}
		debug(px, py, dist[sx][sy][K], dist[cx][cy][K], dist[gx][gy][K]);
	}

	if(ans<1e9) cout << ans << endl;
	else cout << -1 << endl;

	return 0;
}
