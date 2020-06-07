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
#define dbg(...) debug_(__VA_ARGS__)
#else
#define dbg(...)
#endif

int main() {
	ios_base::sync_with_stdio(false);
	cout << setprecision(20) << fixed;

	int n; cin >> n;
	vector<int> p(n*n);
	for(int i=0; i<n*n; i++){
		cin >> p[i];
		p[i]--;
	}

	vector<vector<int>> s(n, vector<int>(n));
	vector<vector<bool>> done(n, vector<bool>(n));
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			s[i][j] = min(min(i, n-1-i), min(j, n-1-j));
		}
	}

	vector<pair<int, int>> q(n*n);
	for(int i=0; i<n*n; i++){
		q[i] = {p[i]/n, p[i]%n};
	}

	ll ans = 0;
	int dx[] = {0, -1, 0, 1};
	int dy[] = {-1, 0, 1, 0};
	for(int i=0; i<n*n; i++){
		int x = q[i].first;
		int y = q[i].second;
		dbg(x, y, s[x][y]);
		ans += s[x][y];
		done[x][y] = true;
		queue<pair<int, pair<int, int>>> que;
		for(int k=0; k<4; k++){
			int nx = x+dx[k];
			int ny = y+dy[k];
			if(0<=nx&&nx<n&&0<=ny&&ny<n&&s[x][y]<s[nx][ny]) que.push({s[x][y], {nx, ny}});
		}

		while(!que.empty()){
			int r = que.front().first;
			int x = que.front().second.first;
			int y = que.front().second.second;
			que.pop();
			if(r>=s[x][y]) continue;
			dbg("-", x, y, r);
			s[x][y] = r;
			for(int k=0; k<4; k++){
				int nx = x+dx[k];
				int ny = y+dy[k];
				if(0<=nx&&nx<n&&0<=ny&&ny<n){
					int u = r;
					if(!done[x][y]) u++;
					if(u<s[nx][ny]) que.push({u, {nx, ny}});
				}
			}
		}
	}

	cout << ans << endl;

	return 0;
}
