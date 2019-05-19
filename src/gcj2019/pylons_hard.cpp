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

void solve(int R, int C){
	bool possible = false;
	vector<vector<int> > g(R, vector<int>(C));
	for(int dx=1; dx<R; dx++){
		for(int dy=1; dy<C; dy++){
			if(dx==dy) continue;
			for(int x=0; x<R; x++){
				for(int y=0; y<C; y++){
					g[x][y] = 0;
				}
			}
			int x=0, y=0;
			g[x][y] = 1;
			for(int i=2; i<=R*C; i++){
				int nx = (x+dx) % R;
				int ny = (y+dy) % C;
				if(g[nx][ny]>0 || x==nx || y==ny || x-y==nx-ny || x+y==nx+ny) break;
				x = nx;
				y = ny;
				cout << x << " " << y << " " << dx << " " << dy << endl;
				g[x][y] = i;
				if(i==R*C) possible = true;
			}
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
