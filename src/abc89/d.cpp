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
const int Hmax=300;
int H, W, D, A[Hmax][Hmax], Q;

int main(){
	cin >> H >> W >> D;
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++) cin >> A[i][j];
	}

	vector<pair<int, int>> pos(H*W+1);
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++) pos[A[i][j]] = {i, j};
	}

	vector<int> cost(H*W+1);
	for(int i=D+1; i<=H*W; i++){
		cost[i] = cost[i-D]
				+ abs(pos[i].first-pos[i-D].first)
				+ abs(pos[i].second-pos[i-D].second);
	}

	cin >> Q;

	for(int i=0; i<Q; i++){
		int L, R;
		cin >> L >> R;
		cout << cost[R]-cost[L] << endl;
	}

	return 0;
}
