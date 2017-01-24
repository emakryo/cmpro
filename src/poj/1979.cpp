#include<iostream>
#include<algorithm>
using namespace std;
const int Hmax = 20;
const int Wmax = 20;
const int dx[] = {1,0,-1,0};
const int dy[] = {0,1,0,-1};
char X[Hmax][Wmax+1];
int W,H;

int dfs(int x, int y){
	X[x][y] = '#';
	int ans=0;
	for(int i=0; i<4; i++){
		if(0<=x+dx[i] && x+dx[i]<H &&
			0<=y+dy[i] && y+dy[i]<W &&
			X[x+dx[i]][y+dy[i]] == '.'){
			ans+=dfs(x+dx[i],y+dy[i]);
		}
	}
	return ans+1;
}

int main(){
	while(true){
		cin >> W >> H;
		if(W == 0 && H == 0) break;
		for(int i=0; i<H; i++){
			cin >> X[i];
		}
		for(int i=0; i<H; i++){
			for(int j=0; j<W; j++){
				if(X[i][j] == '@')
					cout << dfs(i,j) << endl;
			}
		}
	}

	return 0;
}
