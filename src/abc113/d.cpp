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
int H, W, K;
ll dpw[10];
ll dpx[110][10];
const ll P = 1e9+7;

int main(){
	cin >> H >> W >> K;

	dpw[0] = 1;
	dpw[1] = 2;
	for(int i=2; i<=W; i++) dpw[i] = dpw[i-2]+dpw[i-1];
	//for(int i=0; i<=W; i++) cout << dpw[i] << endl;
	//
	
	dpx[0][0] = 1;
	for(int h=1; h<=H; h++){
		for(int k=0; k<W; k++){
			dpx[h][k] += dpx[h-1][k] * (k-1>=0?dpw[k-1]:1) * (W-k-2>=0?dpw[W-k-2]:1);
			if(k>0) dpx[h][k] += dpx[h-1][k-1] * (k-2>=0?dpw[k-2]:1) * (W-k-2>=0?dpw[W-k-2]:1);
			if(k<W-1) dpx[h][k] += dpx[h-1][k+1] * (k-1>=0?dpw[k-1]:1) * (W-k-3>=0?dpw[W-k-3]:1);
			dpx[h][k] %= P;
			//cout << h << " " << k << " " << dpx[h][k] << endl;
		}
	}

	cout << dpx[H][K-1] << endl;

	return 0;
}
