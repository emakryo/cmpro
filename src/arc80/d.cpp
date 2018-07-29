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
const int HWmax = 10000;
int H, W, N;
int A[HWmax];

int main(){
	cin >> H >> W >> N;
	for(int i=0; i<N; i++) cin >> A[i];

	vector<int> x(H*W);
	int k=0;
	for(int i=0; i<N; i++){
		for(int j=0; j<A[i]; j++) x[k++] = i+1;
	}
	vector<vector<int> > vec(100, vector<int>(100));
	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++){
			vec[i][i%2?j:(W-j-1)] = x[W*i+j];
		}
	}

	for(int i=0; i<H; i++){
		for(int j=0; j<W; j++) cout << vec[i][j] << (j<W-1?' ':'\n');
	}

	return 0;
}
