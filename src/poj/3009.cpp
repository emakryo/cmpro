#include<iostream>
#include<algorithm>
using namespace std;
const int Hmax = 20;
const int Wmax = 20;
const int INF = 1e6;
const int dx[] = {1,0,-1,0};
const int dy[] = {0,1,0,-1};
int X[Hmax][Wmax];
int H,W;

bool is_valid(int x, int y){
	return 0<=x && x<H && 0<=y && y<W;
}

int dfs(int x, int y, int d){
	if(d > 9) return INF;
	//cout << x << " " << y << " " << d << endl;
	int ans = INF;
	for(int i=0; i<4; i++){
		if(is_valid(x+dx[i], y+dy[i]) && X[x+dx[i]][y+dy[i]] != 1){
			int j=1;
			while(is_valid(x+j*dx[i], y+j*dy[i]) && X[x+j*dx[i]][y+j*dy[i]] == 0) j++;
			int nx = x+(j-1)*dx[i], ny = y+(j-1)*dy[i];
			int mx = x+j*dx[i], my = y+j*dy[i];
			if(!is_valid(mx, my)) continue;
			if(X[mx][my] == 3) return d+1;
			if(X[mx][my] == 1){
				X[mx][my] = 0;
				ans = min(ans, dfs(nx, ny, d+1));
				X[mx][my] = 1;
			}
		}
	}
	return ans;
}

int main(){
	while(true){
		cin >> W >> H;
		if(W == 0 && H == 0) break;
		for(int i=0; i<H; i++){
			for(int j=0; j<W; j++){
				cin >> X[i][j];
			}
		}

		for(int i=0; i<H; i++){
			for(int j=0; j<W; j++){
				if(X[i][j] == 2){
					X[i][j] = 0;
					int ans = dfs(i,j,0);
					cout << (ans==INF ? -1 : ans) << endl;
					break;
				}
			}
		}
	}

	return 0;
}
