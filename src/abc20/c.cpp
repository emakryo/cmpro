#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int HWmax = 10;
const ll INF = 1e15;
const int dx[] = {1,-1,0,0};
const int dy[] = {0,0,1,-1};
int H,W;
ll T;
char S[HWmax][HWmax+1];
ll d[HWmax][HWmax];

bool reachable(ll r){
	int sx,sy,gx,gy;
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			d[i][j] = INF;
			if(S[i][j] == 'S'){
				sx=i;
				sy=j;
				d[i][j] = 0;
			}
			if(S[i][j] == 'G'){
				gx=i;
				gy=j;
			}
		}
	}

	priority_queue<pair<ll, pair<int, int> >,
		vector<pair<ll, pair<int, int> > >, greater<pair<ll, pair<int, int> > > > que;
	que.push(make_pair(0, make_pair(sx,sy)));
	while(!que.empty()){
		int t = que.top().first;
		int x = que.top().second.first;
		int y = que.top().second.second;
		que.pop();
		for(int i=0; i<4; i++){
			int nx = x+dx[i];
			int ny = y+dy[i];
			if(nx<0 || H<=nx || ny<0 || W<=ny) continue;
			int nt = t+(S[nx][ny] == '#' ? r : 1);
			if(nt > T) continue;
			if(nt < d[nx][ny]){
				d[nx][ny] = nt;
				que.push(make_pair(nt, make_pair(nx,ny)));
			}
		}
	}

	return d[gx][gy] <= T;
}

int main(){
	cin >> H >> W >> T;
	for(int i=0; i<H; i++) cin >> S[i];

	ll p=1,q=T;
	while(p<q-1){
		//cout << p << " " << q << endl;
		if(reachable((p+q)/2)){
			p = (p+q)/2;
		}
		else{
			q = (p+q)/2;
		}
	}

	cout << p << endl;

	return 0;
}
