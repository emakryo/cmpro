#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int H, W;
const int Hmax = 50;
string S[Hmax];

int main(){
	cin >> H >> W;
	for(int i=0; i<H; i++) cin >> S[i];

	queue<pair<int, int>> que;
	que.push({0, 0});
	vector<vector<int>> dist(H, vector<int>(W, 1e8));
	dist[0][0] = 0;
	while(!que.empty()){
		int x = que.front().first;
		int y = que.front().second;
		que.pop();
		int dx[] = {1, -1, 0, 0};
		int dy[] = {0, 0, 1, -1};
		for(int k=0; k<4; k++){
			int nx = x+dx[k];
			int ny = y+dy[k];
			if(nx<0||H<=nx||ny<0||W<=ny) continue;
			if(dist[nx][ny]<1e8 || S[nx][ny]=='#') continue;
			dist[nx][ny] = dist[x][y]+1;
			que.push({nx, ny});
		}
	}

	int nblack = 0;
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			if(S[i][j]=='#') nblack++;
		}
	}

	if(dist[H-1][W-1]==1e8) cout << -1 << endl;
	else cout << H*W-nblack-(dist[H-1][W-1]+1) << endl;

	return 0;
}
