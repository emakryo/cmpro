#include<bits/stdc++.h>
#include<boost/variant.hpp>
using namespace std;
typedef long long ll;
typedef vector<boost::variant<bool, ll, int, string, double, char*, const char*>> any;
template<typename T> inline void pr(const vector<T> &xs){
	for(int i=0; i<xs.size()-1; i++) cout<<xs[i]<<" ";
	(xs.empty()?cout:(cout<<xs[xs.size()-1]))<<endl;
}
template<typename T> inline void debug(const vector<T> &xs){
#ifdef DEBUG
	pr(xs);
#endif
}

int main(){
	int H, W, K;
	cin >> H >> W >> K;
	vector<string> A(H);
	for(int i=0; i<H; i++) cin >> A[i];

	int sx, sy;
	for(int i=0; i<H; i++) for(int j=0; j<W; j++){
		if(A[i][j]=='S'){
			sx = i;
			sy = j;
		}
	}

	vector<vector<int>> dist(H, vector<int>(W, 1e9));
	queue<pair<pair<int, int>, int>> que;
	que.push({{sx, sy}, 0});
	int mdiff = 1e9;
	while(!que.empty()){
		int x = que.front().first.first;
		int y = que.front().first.second;
		int d = que.front().second;
		que.pop();
		if(d>K) continue;
		if(dist[x][y]<=d) continue;
		dist[x][y] = d;
		debug(any{x, y, d});

		mdiff = min(mdiff, min(min(x, y), min(H-x-1, W-y-1)));
		int dx[] = {1, -1, 0, 0};
		int dy[] = {0, 0, 1, -1};
		for(int n=0; n<4; n++){
			int nx = x+dx[n];
			int ny = y+dy[n];
			if(nx<0||H<=nx||ny<0||W<=ny) continue;
			if(A[nx][ny]!='.') continue;
			que.push({{nx, ny}, d+1});
		}
	}

	cout << 1+(mdiff+K-1)/K << endl;

	return 0;
}
