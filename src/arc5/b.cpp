#include<iostream>
#include<iomanip>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cmath>
using namespace std;
typedef long long ll;
int X, Y;
string W, C[9];

int main(){
	cin >> X >> Y >> W;
	X--;
	Y--;
	for(int i=0; i<9; i++){
		cin >> C[i];
	}

	int dx = 0, dy = 0;
	if(W.find("D") != W.npos) dy = 1;
	if(W.find("U") != W.npos) dy = -1;
	if(W.find("L") != W.npos) dx = -1;
	if(W.find("R") != W.npos) dx = 1;

	for(int i=0; i<4; i++){
		cout << C[Y][X];
		int nx = X+dx;
		int ny = Y+dy;
		if(nx < 0 || 9 <= nx){
			dx = -dx;
		}
		if(ny < 0 || 9 <= ny){
			dy = -dy;
		}
		X += dx;
		Y += dy;
	}

	cout << endl;

	return 0;
}
