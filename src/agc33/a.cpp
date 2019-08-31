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
int H, W;
const int Hmax = 1000;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
string A[Hmax];

int main(){
	int H, W;
	cin >> H >> W;
	for(int i=0; i<H; i++) cin >> A[i];

	vector<pair<int, int> > v;
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			if(A[i][j]=='#') v.push_back({i, j});
		}
	}

	int ans = 0;
	while(!v.empty()){
		vector<pair<int, int>> v2;
		for(auto p: v){
			for(int k=0; k<4; k++){
				int x = p.first + dx[k];
				int y = p.second + dy[k];
				if(0<=x&&x<H&&0<=y&&y<W&&A[x][y]=='.'){
					//cout << x << " " << y << endl;
					v2.push_back({x, y});
					A[x][y] = '#';
				}
			}
		}
		v = v2;
		ans++;
	}

	cout << ans-1 << endl;

	return 0;
}
