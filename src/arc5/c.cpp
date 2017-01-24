#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
const int HWmax = 500;
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};
int H, W;
string C[HWmax];
int par[HWmax*HWmax];
int rnk[HWmax*HWmax];

int root(int x){
	if(par[x] == x) return x;
	return par[x] = root(par[x]);
}

void unite(int x, int y){
	if(root(x) == root(y)) return;

	int rx = root(x);
	int ry = root(y);

	if(rnk[rx] >= rnk[ry]){
		par[ry] = rx;
	}
	else {
		par[rx] = ry;
	}
	if(rnk[rx] == rnk[ry]){
		rnk[rx]++;
	}
}


int main(){
	cin >> H >> W;
	for(int i=0; i<H; i++){
		cin >> C[i];
	}

	for(int i=0; i<HWmax*HWmax; i++) par[i] = i;

	int sx,sy,gx,gy;
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			if(C[i][j] == '#') continue;
			if(C[i][j] == 's'){
				sx = i; sy = j;
			}
			if(C[i][j] == 'g'){
				gx = i; gy = j;
			}
			for(int k=0; k<4; k++){
				int nx = i+dx[k];
				int ny = j+dy[k];
				if(nx < 0 || H <= nx || ny < 0 || W <= ny) continue;
				if(C[nx][ny] == '#') continue;
				unite(i*W+j, nx*W+ny);
			}
		}
	}


	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			if(C[i][j] != '#') continue;
			//bool breakable = false;
			for(int k=0; k<4; k++){
				int nx = i+dx[k];
				int ny = j+dy[k];
				if(nx < 0 || H <= nx || ny < 0 || W <= ny) continue;
				if(C[nx][ny] == '#') continue;
				if(root(nx*W+ny) == root(sx*W+sy) || root(nx*W+ny) == root(gx*W+gy)){
					C[i][j] = '.';
				}
			}
			/*
			if(!breakable) continue;
			for(int k=0; k<4; k++){
				int nx = i+dx[k];
				int ny = j+dy[k];
				if(nx < 0 || H <= nx || ny < 0 || W <= ny) continue;
				if(C[nx][ny] == '#') continue;
				unite(i*W+j, nx*W+ny);
			}
			*/
		}
	}

	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			if(C[i][j] == '#') continue;
			for(int k=0; k<4; k++){
				int nx = i+dx[k];
				int ny = j+dy[k];
				if(nx < 0 || H <= nx || ny < 0 || W <= ny) continue;
				if(C[nx][ny] == '#') continue;
				unite(i*W+j,nx*W+ny);
			}
		}
	}


	if(root(sx*W+sy) == root(gx*W+gy)){
		cout << "YES" << endl;
	}
	else{
		cout << "NO" << endl;
	}
	return 0;
}
