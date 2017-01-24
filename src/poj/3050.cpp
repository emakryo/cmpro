#include<cstdio>
// #include<iostream>
// #include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
vector<int> vec[5][5][6];

int main(){
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			int x;
			scanf("%d", &x);
			vec[i][j][0].push_back(x);
		}
	}

	for(int i=0; i<5; i++){
		for(int x=0; x<5; x++){
			for(int y=0; y<5; y++){
				for(int j=0; j<4; j++){
					int nx = x+dx[j];
					int ny = y+dy[j];
					if(0 <= nx && nx < 5 && 0<=ny && ny < 5){
						for(int k=0; k<vec[x][y][i].size(); k++){
							vec[nx][ny][i+1].push_back(
									vec[x][y][i][k]*10+vec[nx][ny][0][0]);
						}
					}
				}
			}
		}
	}

	vector<int> v;
	for(int x=0; x<5; x++){
		for(int y=0; y<5; y++){
			for(int i=0; i<vec[x][y][5].size(); i++)
				v.push_back(vec[x][y][5][i]);
		}
	}

	sort(v.begin(), v.end());
	vector<int>::iterator it = unique(v.begin(), v.end());
	printf("%d\n", (int)(it-v.begin()));

	return 0;
}
