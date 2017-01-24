#include<iostream>
#include<algorithm>
using namespace std;
const int Hmax = 100, Wmax = 100;
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};
int W, H;
char X[Hmax][Wmax+1];

void dfs(int x, int y, char c){
	X[x][y] = '.';
	for(int i=0; i<4; i++){
		int nx = x+dx[i];
		int ny = y+dy[i];
		if(0<=nx && nx<H && 0<=ny && ny<W && X[nx][ny]==c)
			dfs(x+dx[i],y+dy[i],c);
	}
}

int main(){
	while(true){
		cin >> H >> W;
		if(H == 0 && W == 0) break;
		for(int i=0; i<H; i++) cin >> X[i];

		int ans = 0;
		for(int i=0; i<H; i++){
			for(int j=0; j<W; j++){
				if(X[i][j] != '.'){
					dfs(i,j,X[i][j]);
					ans++;
				}
			}
		}

		cout << ans << endl;
	}
	return 0;
}
