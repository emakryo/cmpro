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
	int n, m, t;
	cin >> n >> m >> t;
	vector<string> s(n);
	for(int i=0; i<n; i++) cin >> s[i];

	const int INF = 1e9;
	vector<vector<int>> x(n, vector<int>(m, INF));
	queue<pair<int, int>> que;
	int dx[]={-1, 0, 1, 0};
	int dy[]={0, -1, 0, 1};
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			bool u=false;
			for(int k=0; k<4; k++){
				int ni=i+dx[k];
				int nj=j+dy[k];
				if(ni<0||n<=ni||nj<0||m<=nj) continue;
				if(s[i][j]==s[ni][nj]) u=true;
			}
			if(u){
				x[i][j]=0;
				que.push({i, j});
			}
		}
	}

	while(!que.empty()){
		int i=que.front().first;
		int j=que.front().second;
		que.pop();
		for(int k=0; k<4; k++){
			int ni=i+dx[k];
			int nj=j+dy[k];
			if(ni<0||n<=ni||nj<0||m<=nj) continue;
			if(x[ni][nj]==INF){
				x[ni][nj] = x[i][j]+1;
				que.push({ni, nj});
			}
		}
	}

	for(int i=0; i<n; i++) dbg(x[i]);

	for(int q=0; q<t; q++){
		int i, j; cin >> i >> j;
		i--; j--;
		ll p; cin >> p;
		if(x[i][j]==INF){
			cout << s[i][j] << endl;
		} else {
			if(p<=x[i][j]){
				cout << s[i][j] << endl;
			} else {
				int c = s[i][j]-'0';
				cout << (c+p-x[i][j])%2 << endl;
			}
		}
	}

	return 0;
}
