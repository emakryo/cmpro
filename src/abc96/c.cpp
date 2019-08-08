#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int H, W;
const int Hmax = 50;
string S[Hmax];

int main(){
	cin >> H >> W;
	for(int i=0; i<H; i++) cin >> S[i];

	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			if(S[i][j]=='.') continue;
			int dx[] = {1, -1, 0, 0};
			int dy[] = {0, 0, 1, -1};
			bool ok = false;
			for(int k=0; k<4; k++){
				int nx = i+dx[k];
				int ny = j+dy[k];
				if(0<=nx&&nx<H&&0<=ny&&ny<W&&S[nx][ny]=='#') ok = true;
			}
			if(!ok){
				cout << "No" << endl;
				return 0;
			}
		}
	}

	cout << "Yes" << endl;

	return 0;
}
