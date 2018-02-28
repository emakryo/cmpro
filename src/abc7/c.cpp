#include<iostream>
#include<queue>
using namespace std;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int x[100][100];

int main(){
	int r, c;
	pair<int, int> s, g;
	string a[50];

	cin >> r >> c;
	cin >> s.first >> s.second;
	cin >> g.first >> g.second;
	s.first--; s.second--;
	g.first--; g.second--;

	for(int i=0; i<r; i++) cin >> a[i];
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			x[i][j] = -1;
		}
	}

	queue<pair<int, int> > que;
	x[s.first][s.second] = 0;
	que.push(s);
	while(!que.empty()){
		pair<int, int> p = que.front();
		que.pop();
		for(int i=0; i<4; i++){
			int xn = p.first + dx[i];
			int yn = p.second + dy[i];
			if(0 <= xn && xn < r && 0 <= yn && yn < c && a[xn][yn] == '.' && x[xn][yn] < 0){
				x[xn][yn] = x[p.first][p.second] + 1;
				//cout << xn << " " << yn << " " << x[xn][yn] << endl;
				que.push(make_pair(xn, yn));
			}
		}
	}

	cout << x[g.first][g.second] << endl;;
	return 0;
}
