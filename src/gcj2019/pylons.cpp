#include<iostream>
#include<iomanip>
//#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<cassert>
using namespace std;
typedef long long ll;

bool rec(vector<vector<int> > &g, int x, int y, int n){
	g[x][y] = n;
	//cout << x << " " << y << " " << n << endl;
	if(n == g.size() * g[0].size()) return true;
	bool possible=false;
	for(int nx=0; nx<g.size(); nx++){
		if(nx==x) continue;
		for(int ny=0; ny<g[0].size(); ny++){
			if(ny==y || ny-nx==y-x || ny+nx==x+y || g[nx][ny] > 0) continue;
			possible = rec(g, nx, ny, n+1);
			if(possible) return true;
		}
	}
	g[x][y] = 0;
	return false;
}

void solve(int R, int C){
	vector<vector<int> > g(R, vector<int>(C));
	bool possible = false;
	for(int x=0; x<(R+1)/2; x++){
		for(int y=0; y<(C+1)/2; y++){
			possible = rec(g, x, y, 1);
			if(possible) break;
		}
		if(possible) break;
	}

	if(!possible){
		cout << "IMPOSSIBLE" << endl;
		return;
	}
	cout << "POSSIBLE" << endl;
	vector<pair<int, pair<int, int> > > ans;
	for(int x=0; x<R; x++){
		for(int y=0; y<C; y++){
			ans.push_back(make_pair(g[x][y], make_pair(x+1, y+1)));
		}
	}

	sort(ans.begin(), ans.end());
	for(int i=0; i<ans.size(); i++){
		cout << ans[i].second.first << " " << ans[i].second.second << endl;
	}
}

int main(){
	int T, R, C;
	cin >> T;
	for(int i=0; i<T; i++){
		cin >> R >> C;
		cout << "Case #" << i+1 << ": ";
		solve(R, C);
	}

	return 0;
}
