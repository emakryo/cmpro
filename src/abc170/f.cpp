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

template<typename T>
istream& operator>>(istream &is, vector<T> &v){
	for(int i=0; i<v.size(); i++) is >> v[i];
	return is;
}

#ifdef DBG
void debug_(){ cout << endl; }
template<typename T, typename... Args>
void debug_(T&& x, Args&&... xs){
	cout << x << " "; debug_(forward<Args>(xs)...);
}
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	int h, w, k; cin >> h >> w >> k;
	int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
	vector<string> c(h); cin >> c;

	x1--; y1--; x2--; y2--;

	using piii = pair<int, pair<int, int>>;
	//priority_queue<piii, vector<piii>, greater<piii>> que;
	//que.push({0, {x1, y1}});
	vector<pair<int, int>> que;
	que.push_back({x1, y1});
	vector<vector<int>> dist(h, vector<int>(w, 1e9));
	dist[x1][y1] = 0;

	for(int d=0;; d++){
		set<pair<int, int>> next;
		for(auto p: que){
			int x = p.first;
			int y = p.second;
			dbg(x, y, d);

			int dx[] = {0, 1, 0, -1};
			int dy[] = {1, 0, -1, 0};
			for(int j=0; j<4; j++){
				for(int l=1; l<=k; l++){
					int nx = x+dx[j]*l;
					int ny = y+dy[j]*l;
					if(nx<0||h<=nx||ny<0||w<=ny||dist[nx][ny]<=d+1||c[nx][ny]=='@') break;
					next.insert({nx, ny});
				}
			}
		}

		que.clear();
		for(auto p: next){
			dist[p.first][p.second] = d+1;
			que.push_back(p);
		}

		if(que.size()==0) break;
	}

	if(dist[x2][y2]==1e9){
		cout << -1 << endl;
	} else{
		cout << dist[x2][y2] << endl;
	}

	return 0;
}
