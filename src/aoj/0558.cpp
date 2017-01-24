#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int Hmax = 1000;
const int Wmax = 1000;
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};
int W,H,N;
char X[Hmax][Wmax+1];
bool visit[Hmax][Wmax+1];
int ax[10],ay[10];
typedef struct{
	int x,y,t;
} state;

int main(){
	cin >> H >> W >> N;
	for(int i=0; i<H; i++) cin >> X[i];
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			if(X[i][j] == 'S'){
				ax[0] = i;
				ay[0] = j;
			}
			else if('1'<=X[i][j] && X[i][j]<='9'){
				ax[X[i][j]-'0'] = i;
				ay[X[i][j]-'0'] = j;
			}
		}
	}

	int ans = 0;
	for(int i=0; i<N; i++){
		queue<state> que;
		state s = {ax[i],ay[i],ans};
		que.push(s);
		while(!que.empty()){
			s = que.front();
			que.pop();
			//cout << s.x << " " << s.y << " " << s.t << endl;
			if(s.x == ax[i+1] && s.y == ay[i+1]){
				ans = s.t;
				//cout << i << " " << ans << endl;
				break;
			}
			if(visit[s.x][s.y]) continue;
			visit[s.x][s.y] = 1;
			for(int j=0; j<4; j++){
				int nx = s.x+dx[j];
				int ny = s.y+dy[j];
				if(nx<0 || H<=nx || ny<0 || W<=ny ||
					X[nx][ny] == 'X' || visit[nx][ny]) continue;
				state t = {nx, ny, s.t+1};
				que.push(t);
			}
		}
		for(int j=0; j<H; j++){
			for(int k=0; k<W; k++){
				visit[j][k] = 0;
			}
		}
		//cout << endl;
	}

	cout << ans << endl;

	return 0;
}
