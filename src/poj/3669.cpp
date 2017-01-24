#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
const int HWmax = 305;
const int Mmax = 50000;
const int INF = 1e8;
const int dx[] = {1,0,-1,0};
const int dy[] = {0,1,0,-1};
int M;
int X[Mmax], Y[Mmax], T[Mmax];
int m[HWmax][HWmax];
int dist[HWmax][HWmax];

int main(){
	scanf("%d\n", &M);
	for(int i=0; i<M; i++){
		int x, y, t;
		scanf("%d %d %d\n", &x, &y, &t);
		X[i] = x;
		Y[i] = y;
		T[i] = t;
	}

	//for(int i=0; i<M; i++) printf("%d %d %d\n", X[i], Y[i], T[i]);

	for(int i=0; i<HWmax; i++){
		for(int j=0; j<HWmax; j++){
			m[i][j] = INF;
			dist[i][j] = INF;
		}
	}

	for(int i=0; i<M; i++){
		m[X[i]][Y[i]] = min(T[i], m[X[i]][Y[i]]);
		for(int j=0; j<4; j++){
			int nx = X[i]+dx[j];
			int ny = Y[i]+dy[j];
			if(nx>=0 && ny>=0)
				m[nx][ny] = min(T[i], m[nx][ny]);
		}
	}

	if(m[0][0] == 0){
		printf("-1\n");
		return 0;
	}
	queue<pair<int, int> > que;
	que.push(make_pair(0, 0));
	dist[0][0] = 0;

	while(!que.empty()){
		int x = que.front().first;
		int y = que.front().second;
		int t = dist[x][y];
		//printf("%d %d %d\n", x, y, t);
		que.pop();

		if(m[x][y] == INF){
			printf("%d\n", t);
			return 0;
		}

		for(int i=0; i<4; i++){
			int nx = x+dx[i];
			int ny = y+dy[i];
			if(0<=nx && 0<=ny &&
				m[nx][ny] > t+1 &&
				dist[nx][ny] > t+1){
				dist[nx][ny] = t+1;
				que.push(make_pair(nx, ny));
			}
		}
	}

	printf("-1\n");

	return 0;
}
