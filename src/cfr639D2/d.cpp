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

void flip(vector<vector<bool>> &x){
	for(int i=0; i<x.size(); i++){
		for(int j=i+1; j<x.size(); j++){
			swap(x[i][j], x[j][i]);
		}
	}
}

void dfs(int x, int y, vector<vector<bool>> &a, vector<vector<bool>> &visit){
	if(x<0||a.size()<=x||y<0||a[0].size()<=y||!a[x][y]||visit[x][y]) return;
	visit[x][y] = true;
	int dx[]={0, -1, 0, 1};
	int dy[]={1, 0, -1, 0};
	for(int k=0; k<4; k++){
		dfs(x+dx[k], y+dy[k], a, visit);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	int n, m; cin >> n >> m;
	int l = max(n, m);
	vector<vector<bool>> a(l, vector<bool>(l));
	for(int i=0; i<n; i++){
		string s;
		cin >> s;
		for(int j=0; j<m; j++) if(s[j]=='#') a[i][j]=true;
	}

	int empty[2] = {0, 0};
	for(int p=0; p<2; p++){
		for(int i=0; i<n; i++){
			int x=0, y=0;
			if(a[i][0])x++;
			if(a[i][m-1]) y++;
			for(int j=0; j<m-1; j++){
				if(!a[i][j]&&a[i][j+1])x++;
				if(a[i][j]&&!a[i][j+1])y++;
			}
			if(x>1||y>1){
				cout << -1 << endl;
				return 0;
			}
			if(x==0) empty[p]++;
		}
		flip(a);
		swap(n, m);
	}
	if(empty[0]==0&&empty[1]>0||empty[0]>0&&empty[1]==0){
		cout << -1 << endl;
		return 0;
	}

	vector<vector<bool>> visit(l, vector<bool>(l));
	int ans = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(visit[i][j]||!a[i][j]) continue;
			dfs(i, j, a, visit);
			ans++;
		}
	}
	cout << ans << endl;

	return 0;
}
